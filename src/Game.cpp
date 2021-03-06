#include "Game.h"

#include "goal.h"
#include "Entity/Entity.h"
#include "CollisionHandler.h"
#include "treasureevent.h"
#include "treasurefound.h"
#include "CaptainFoundPlayer.h"
#include "SaveMatrix.h"
#include "observation.h"
#include "concretemapinfo.h"
#include "matrixprinter.h"
#include "appendmatrixprovider.h"
#include "matrixloader.h"
#include "operationVector.h"
#include "mappositiontile.h"
#include "positionmatrix.h"
#include "callbackmatrixprovider.h"
#include "bw.h"
#include "callbackevent.h"
#include "ListeNode.h"
#include "NodeFinding.h"
#include "initnodefinding.h"
#include "distanceaccumulator.h"
#include "distancepersistor.h"
#include "rprinter.h"

#include <iostream>
#include <thread>

using namespace std;
using boost::numeric::ublas::matrix;

Game::Game() : window(sf::VideoMode {64 * 16, 64 * 8}, "Game"), map {make_shared<Map>()}, collisionHandler {make_shared<CollisionHandler>()} {
	collisionHandler->setMap(map);
	map->setHeight(64 * 8);
	map->setWidth(64 * 16);
}

void Game::init()
{
	map->generateTileset();
	auto player1 = make_shared<Entity>();
	auto player2 = make_shared<Entity>();
	player1->setStartPosition( {8, 0});
	player2->setStartPosition( {8, 7});
	
	auto texture1 = make_shared<sf::Texture>();
	auto texture2 = make_shared<sf::Texture>();
	texture1->loadFromFile("res/matelot.png");
	texture2->loadFromFile("res/capitain.png");
	player1->setTexture(texture1);
	player2->setTexture(texture2);

	setArrowControlled(player1);
	setWasdControlled(player2);

	auto treasureEvent = make_shared<TreasureEvent>();
	treasureEvent->setMap(map);
	treasureEvent->setSubject(arrowControlled);
	treasureEvent->setTreasureType(map->getTileSet()[2]);
	treasureEvent->setTreasureCheckedType(map->getTileSet()[3]);

	treasureFound = make_shared<TreasureFound>();
	treasureFound->setMap(map);
	treasureFound->setTreasureType(map->getTileSet()[3]);

	auto captainFoundPlayer = make_shared<CaptainFoundPlayer>();
	captainFoundPlayer->setCaptain(player2);
	captainFoundPlayer->setMatelot(player1);

	observation = make_shared<Observation>();
	observation->setMap(map);
	observation->setSubject(wasdControlled);
	observation->setObserve(arrowControlled);

	auto matrixLoader = make_shared<MatrixLoader>("data/observations.json", "observations");
	completeMatrixProvider = make_shared<AppendMatrixProvider>(matrixLoader);

	auto saveMatrix = make_shared<SaveMatrix>("data/observations.json", "observations");
	saveMatrix->setMatrix(observation);
	auto saveProbs = make_shared<SaveMatrix>("data/probabilities.json", "probabilities");
	
	mapPositionTile = make_shared<MapPositionTile>(map);
	positionMatrix = make_shared<PositionMatrix>(observation, mapPositionTile);
	
	saveProbs->setMatrix(positionMatrix);
	listeNode = make_shared<ListeNode>(map, mapPositionTile);
	nodeFinding = make_shared<NodeFinding>(listeNode);
	auto initNodeFinding = make_shared<InitNodeFinding>(positionMatrix, nodeFinding);
	initNodeFinding->setControlledEntity(player2);
	
	turn.addRequiredEntity(arrowControlled);
	turn.addEndTurnEvent(captainFoundPlayer);
	turn.addEndTurnEvent(treasureEvent);
	turn.addPreApplyEvent(observation);
	turn.addApplyEvent(initNodeFinding);
	
	auto distanceAccumulator = make_shared<DistanceAccumulator>(player1, nodeFinding, observation);
	auto distancePersistor = make_shared<DistancePersistor>(distanceAccumulator);
	
	window.setKeyRepeatEnabled(false);
	
 	turn.addApplyEvent(make_shared<CallbackEvent>([=](){
// // 		positionMatrix->makeMatrix();
// //  		cout << positionMatrix->getPosition().y+1 << ", " << positionMatrix->getPosition().x+1 << endl;
		showMat(ligne(positionMatrix->getProbability(), positionMatrix->getProbability().size1() -1));
 		showMat(ligne(observation->getMatrix(), observation->getMatrix().size1() -1));
	}));
	
	auto printR = make_shared<RPrinter>(positionMatrix, player1, player2, observation, completeMatrixProvider, map, mapPositionTile);
	
	turn.addEndTurnEvent(distanceAccumulator);
	turn.addPreApplyEvent(printR);
	
	setLostGoal(captainFoundPlayer);
	setWinGoal(treasureFound);
	
	addEndGameEvent(saveMatrix);
	addEndGameEvent(saveProbs);
	addEndGameEvent(distancePersistor);
	
	reset();
}

void Game::addEntity(shared_ptr<Entity> entity)
{
	entity->setCollisionHandler(collisionHandler);
	entities.push_back(entity);
}

void Game::setArrowControlled(shared_ptr<Entity> entity)
{
	arrowControlled = entity;
	addEntity(entity);
}

void Game::setWasdControlled(shared_ptr<Entity> entity)
{
	wasdControlled = entity;
	addEntity(entity);
}

void Game::mainLoop()
{
	while (window.isOpen()) {
		handleEvent();
		if (turn.shouldApply()) {
			turn.apply();
		}
		render();
	}
	close();
}

void Game::handleEvent()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		
		if (event.type == sf::Event::KeyPressed) {
			keyPressed[event.key.code] = true;
		} else if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			} else if (event.key.code == sf::Keyboard::F) {
				fogEnabled = !fogEnabled;
			} else if (event.key.code == sf::Keyboard::P) {
				probsEnabled = !probsEnabled;
			} else {
				keyPressed[event.key.code] = false;
			}
		}
	}
	
	keyChanged();

	for (auto event : frameEvents) {
		event->trigger();
	}
}

void Game::keyChanged()
{
	sf::Vector2i movementArrow;
	
	if (keyPressed[sf::Keyboard::Left]) {
		movementArrow += sf::Vector2i{-1, 0};
	}
	
	if (keyPressed[sf::Keyboard::Right]) {
		movementArrow += sf::Vector2i{1, 0};
	}
	
	if (keyPressed[sf::Keyboard::Up]) {
		movementArrow += sf::Vector2i{0, -1};
	}
	
	if (keyPressed[sf::Keyboard::Down]) {
		movementArrow += sf::Vector2i{0, 1};
	}
	
	if (abs(movementArrow.x) + abs(movementArrow.y) > 1) {
		movementArrow = sf::Vector2i{0, 0};
	}
	
	sf::Vector2i movementWasd;
	if (keyPressed[sf::Keyboard::A]) {
		movementWasd += sf::Vector2i{-1, 0};
	}
	
	if (keyPressed[sf::Keyboard::D]) {
		movementWasd += sf::Vector2i{1, 0};
	}
	
	if (keyPressed[sf::Keyboard::W]) {
		movementWasd += sf::Vector2i{0, -1};
	}
	
	if (keyPressed[sf::Keyboard::S]) {
		movementWasd += sf::Vector2i{0, 1};
	}
	
	if (abs(movementWasd.x) + abs(movementWasd.y) > 1) {
		movementWasd = sf::Vector2i{0, 0};
	}
	
	if (movementArrow == sf::Vector2i{0, 0} && !keyPressed[sf::Keyboard::Space]) {
		turn.removeMovement(arrowControlled);
	} else if (keyPressed[sf::Keyboard::Space]) {
		turn.addMovement(arrowControlled, sf::Vector2i{0, 0});
	} else {
		turn.addMovement(arrowControlled, movementArrow);
	}
	
	if (movementWasd == sf::Vector2i{0, 0}) {
		turn.removeMovement(wasdControlled);
	} else {
		turn.addMovement(wasdControlled, movementWasd);
	}
}

shared_ptr<Goal> Game::getLostGoal() const
{
	return lostGoal;
}

shared_ptr<Goal> Game::getWinGoal() const
{
	return winGoal;
}

void Game::setLostGoal(shared_ptr<Goal> lostGoal)
{
	addFrameEvent(lostGoal);
	lostGoal->setCallback([this] {
		lost();
	});
	this->lostGoal = lostGoal;
}

void Game::setWinGoal(shared_ptr<Goal> winGoal)
{
	addFrameEvent(winGoal);
	winGoal->setCallback([this] {
		win();
	});
	this->winGoal = winGoal;
}

void Game::end()
{
// 	showMat(observation->getMatrix());
	
	for (auto event : endGameEvent) {
		event->trigger();
	}
}

void Game::lost()
{
	vector<double> last;

	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			last.push_back(arrowControlled->getPosition() == tile->getPosition());
		}
	}
	
	observation->replaceLast(last);
	end();
	render();
	textureLost.loadFromFile("res/lost.png");
	sf::RectangleShape rect(sf::Vector2f{256.f, 512.f});
	rect.setPosition(sf::Vector2f{sf::Vector2u{64 * 16 / 2, 64 * 8 / 2} - sf::Vector2u{128, 256}});
	rect.setTexture(&textureLost);
	window.draw(rect);
	window.display();
	this_thread::sleep_for(chrono::seconds(1));
	reset();
}

void Game::close()
{
	
}

void Game::reset()
{
	mappedTiles.clear();
	
	fogEnabled = true;
	for (auto entity : entities) {
		entity->resetPosition();
	}
	map->generateMap();
	mapPositionTile->makeMap();

	vector<double> pie;

	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			pie.push_back(arrowControlled->getPosition() == tile->getPosition());
			mappedTiles.push_back(tile);
		}
	}

	auto tiles = map->getTiles();

	matrix<double> mIni{mappedTiles.size(), mappedTiles.size()};
	fill(mIni, [&](int m, int n) {
		int nearbyTiles = 1;
		auto current = mappedTiles[m];
		auto next = mappedTiles[n];

		bool isNearby = current == next;


		auto left = map->getTileAtPosition(current->getPosition() - sf::Vector2i {-1, 0});
		auto right = map->getTileAtPosition(current->getPosition() - sf::Vector2i {1, 0});
		auto up = map->getTileAtPosition(current->getPosition() - sf::Vector2i {0, -1});
		auto down = map->getTileAtPosition(current->getPosition() - sf::Vector2i {0, 1});

		if (left && left->getTileType()->isWalkable()) {
			nearbyTiles++;
			isNearby = left == next || isNearby;
		}
		if (right && right->getTileType()->isWalkable()) {
			nearbyTiles++;
			isNearby = right == next || isNearby;
		}
		if (up && up->getTileType()->isWalkable()) {
			nearbyTiles++;
			isNearby = up == next || isNearby;
		}
		if (down && down->getTileType()->isWalkable()) {
			nearbyTiles++;
			isNearby = down == next || isNearby;
		}

		return isNearby ? (1.f / nearbyTiles) : 0;
	});
	
	matrix<double> transition;
	
	if (history.size1() == 0) {
		auto historyMatrixLoader = make_shared<MatrixLoader>("data/history.json", "observations");
		auto matProv = make_shared<AppendMatrixProvider>(historyMatrixLoader);
		history = BW(matProv->getObservation(), mIni, pie, 30);
	}
	
	transition = BW(completeMatrixProvider->getLast(10), mIni, pie, 20);
			cout << "Nb de Parties :" << completeMatrixProvider->getObservation().size() << endl;

	positionMatrix->setPie(pie);
	
	if (history.size1() > 0) {
			positionMatrix->setTransition( history * 0.9995 + mIni * 0.0005);
// 			positionMatrix->setTransition( mIni );
// 		if (completeMatrixProvider->getObservation().size() == 00 ) {
// 			positionMatrix->setTransition( history * 0.9995 + mIni * 0.0005);
// 		} else if (completeMatrixProvider->getObservation().size() < 10 ){
// 					positionMatrix->setTransition(transition * 0.08 * completeMatrixProvider->getObservation().size() + history * (1-  0.08 * completeMatrixProvider->getObservation().size() - 0.0005) + mIni * 0.0005);
// 		} else {
// 			positionMatrix->setTransition(transition * 0.7995 + history * 0.20 + mIni * 0.0005);
// 		}
	} else {
		positionMatrix->setTransition(transition * 0.95 + mIni * 0.05);
	}
	

	listeNode->makeListNode();
	
	turn.reset();
	observation->addEyeType(map->getTileSet()[4]);
	observation->addEyeType(map->getTileSet()[3]);
	observation->reset();
	observation->trigger();
	positionMatrix->makeMatrix();
}

void Game::win()
{
	vector<double> last;

	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			last.push_back(arrowControlled->getPosition() == tile->getPosition());
		}
	}
	
	observation->replaceFive(last);
	end();
	fogEnabled = false;
	render();
	textureWin.loadFromFile("res/win.png");
	sf::RectangleShape rect(sf::Vector2f{256.f, 512.f});
	rect.setPosition(sf::Vector2f{sf::Vector2u{64 * 16 / 2, 64 * 8 / 2} - sf::Vector2u{128, 256}});
	rect.setTexture(&textureWin);
	window.draw(rect);
	window.display();
	this_thread::sleep_for(chrono::seconds(1));
	reset();
}

shared_ptr<Map> Game::getMap()
{
	return map;
}

void Game::render()
{
	double vision = 3;
	auto mapInfo = unique_ptr<ConcreteMapInfo>(new ConcreteMapInfo(map));

	window.clear(sf::Color::Black);

	for (auto tile : map->getTiles()) {
		tile->draw(window, mapInfo.get());
	}

	for (auto entity : entities) {
		auto distance = entity->getPosition() - arrowControlled->getPosition();
		if (!fogEnabled || sqrt(distance.x*distance.x + distance.y*distance.y) < vision) {
			entity->draw(window, mapInfo.get());
		}
	}
	
	if (fogEnabled) {
		for (auto tile : map->getTiles()) {
			auto relative= tile->getPosition() - arrowControlled->getPosition();
			auto distance = sqrt(relative.x*relative.x + relative.y*relative.y);
			sf::RectangleShape fogRectangle(sf::Vector2f {static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
			fogRectangle.setFillColor(sf::Color{0, 0, 0, static_cast<u_char>((255.0/vision)*(max(vision*2/4, min(vision, distance))-(vision*2/4)))});
			fogRectangle.setPosition(tile->getPosition().x * mapInfo->getTileWidth(), tile->getPosition().y * mapInfo->getTileHeight());
			window.draw(fogRectangle);
		}
	}
	
	if (probsEnabled) {
		auto probs = ligne(positionMatrix->getProbability(), positionMatrix->getProbability().size1() -1);
		if (probs.size2() == 0) {
			positionMatrix->makeMatrix();
			probs = ligne(positionMatrix->getProbability(), positionMatrix->getProbability().size1() -1);
		}
		for (auto tile : map->getTiles()) {
			if (tile->getTileType()->isWalkable()) {
				auto prob = probs(0, mapPositionTile->getArg(tile));
				
				sf::RectangleShape probRectangle(sf::Vector2f {static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
				probRectangle.setFillColor(sf::Color{
					static_cast<u_char>(191*sqrt(prob) + 64),
					static_cast<u_char>(255*sqrt(prob)),
					static_cast<u_char>(255/(sqrt(prob)+1)),
					static_cast<u_char>(128+32*sqrt(prob))
				});
				
				probRectangle.setPosition(tile->getPosition().x * mapInfo->getTileWidth(), tile->getPosition().y * mapInfo->getTileHeight());
				window.draw(probRectangle);
				
			}
		}
	}

	window.display();
}

void Game::addFrameEvent(shared_ptr<Event> event)
{
	frameEvents.emplace(event);
}

void Game::addEndGameEvent(shared_ptr<Event> event)
{
	endGameEvent.emplace(event);
}

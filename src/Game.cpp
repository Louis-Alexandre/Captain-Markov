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
#include "Entity/Player.h"
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
	auto player1 = make_shared<Player>();
	auto player2 = make_shared<Player>();
	player1->setStartPosition( {8, 0});
	player2->setStartPosition( {8, 7});

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

	auto matrixLoader = make_shared<MatrixLoader>();
	completeMatrixProvider = make_shared<AppendMatrixProvider>(matrixLoader, observation);

	auto saveMatrix = make_shared<SaveMatrix>();
	saveMatrix->setObservation(observation);

	
	auto mapPositionTile = make_shared<MapPositionTile>(map);
	auto positionmatrix = make_shared<PositionMatrix>(observation, mapPositionTile);
	
	auto listeNode = make_shared<ListeNode>(map);
	listeNode->makeListNode();
	auto nodeFinding = make_shared<NodeFinding>(listeNode);
	auto initNodeFinding = make_shared<InitNodeFinding>(positionmatrix, listeNode);
	
	turn.addEndTurnEvent(captainFoundPlayer);
	turn.addEndTurnEvent(treasureEvent);
	turn.addPreApplyEvent(observation);
	turn.addApplyEvent(initNodeFinding);

	setLostGoal(captainFoundPlayer);
	setWinGoal(treasureFound);
	

// 	addEndGameEvent(saveMatrix);
	

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
	end();
}

void Game::handleEvent()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				turn.addMovement(arrowControlled, { -1, 0});
			} else if (event.key.code == sf::Keyboard::Right) {
				turn.addMovement(arrowControlled, {1, 0});
			} else if (event.key.code == sf::Keyboard::Up) {
				turn.addMovement(arrowControlled, {0, -1});
			} else if (event.key.code == sf::Keyboard::Down) {
				turn.addMovement(arrowControlled, {0, 1});
			} else if (event.key.code == sf::Keyboard::A) {
				turn.addMovement(wasdControlled, { -1, 0});
			} else if (event.key.code == sf::Keyboard::D) {
				turn.addMovement(wasdControlled, {1, 0});
			} else if (event.key.code == sf::Keyboard::W) {
				turn.addMovement(wasdControlled, {0, -1});
			} else if (event.key.code == sf::Keyboard::S) {
				turn.addMovement(wasdControlled, {0, 1});
			} else if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
	}

	for (auto event : frameEvents) {
		event->trigger();
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
	vector<double> last;

	for (auto tile : map->getTiles()) {
		if (tile->getTileType()->isWalkable()) {
			last.push_back(arrowControlled->getPosition() == tile->getPosition());
		}
	}
	
	observation->replaceLast(last);
// 	showMat(observation->getMatrix());
	
	for (auto event : endGameEvent) {
		event->trigger();
	}
}

void Game::lost()
{
	end();
	cout << "You lost!" << endl;
	render();
	this_thread::sleep_for(chrono::seconds(1));
	reset();
}

void Game::reset()
{
	for (auto entity : entities) {
		entity->resetPosition();
	}
	map->generateMap();

	vector<double> pie;

	vector<shared_ptr<Tile>> mappedTiles;
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
	
	
	auto transition = BW(completeMatrixProvider->getObservation(), mIni, pie, 1);
	positionmatrix->setPie(pie);
	positionmatrix->setTransition(transition);
// 	showMat(transition);
	
// 	turn.addApplyEvent(matrixPrinter);
	turn.addApplyEvent(make_shared<CallbackEvent>([=](){
		positionmatrix->makeMatrix();
		cout << positionmatrix->getPosition().x << ", " << positionmatrix->getPosition().y << endl;
		showMat(ligne(positionmatrix->getProbability(), positionmatrix->getProbability().size1() -1));
		
	}));
	turn.reset();
	observation->reset();
}

void Game::win()
{
	end();
	cout << "You win!" << endl;
	render();
	this_thread::sleep_for(chrono::seconds(1));
	reset();
}

shared_ptr<Map> Game::getMap()
{
	return map;
}

void Game::render()
{
	auto mapInfo = unique_ptr<ConcreteMapInfo>(new ConcreteMapInfo(map));

	window.clear(sf::Color::Black);

	for (auto i : map->getTiles()) {
		sf::RectangleShape tileRectangle(sf::Vector2f {static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
		tileRectangle.setFillColor(i->getTileType()->getColor());
		tileRectangle.setPosition(i->getPosition().x * mapInfo->getTileWidth(), i->getPosition().y * mapInfo->getTileHeight());
		window.draw(tileRectangle);
	}

	for (auto entity : entities) {
		entity->draw(window, mapInfo.get());
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

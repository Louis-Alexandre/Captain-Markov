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

#include <iostream>
#include <thread>

using namespace std;

Game::Game() : window(sf::VideoMode{64 * 16, 64 * 8}, "Game"), map{make_shared<Map>()}, collisionHandler{make_shared<CollisionHandler>()}
{
	collisionHandler->setMap(map);
	map->setHeight(64 * 8);
	map->setWidth(64 * 16);
}

void Game::init()
{
	map->generateTileset();
	auto player1 = make_shared<Player>();
	auto player2 = make_shared<Player>();
	player1->setStartPosition({8, 0});
	player2->setStartPosition({8, 7});
	
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

	auto observation = make_shared<Observation>();
	observation->setMap(map);
	observation->setSubject(wasdControlled);
	
	auto matrixLoader = make_shared<MatrixLoader>();
	auto completeMatrixProvider = make_shared<AppendMatrixProvider>(matrixLoader, observation);

	auto matrixPrinter = make_shared<MatrixPrinter>();
	matrixPrinter->setObservation(completeMatrixProvider);
	
	auto saveMatrix = make_shared<SaveMatrix>();
	saveMatrix->setObservation(observation);
	
	turn.addEndTurnEvent(captainFoundPlayer);
	turn.addEndTurnEvent(treasureEvent);
	turn.addEndTurnEvent(observation);
	
	setLostGoal(captainFoundPlayer);
	setWinGoal(treasureFound);
	
	addEndGameEvent(saveMatrix);
	addEndGameEvent(matrixPrinter);
	
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
	lostGoal->setCallback([this]{
		lost();
	});
	this->lostGoal = lostGoal;
}

void Game::setWinGoal(shared_ptr<Goal> winGoal)
{
	addFrameEvent(winGoal);
	winGoal->setCallback([this]{
		win();
	});
	this->winGoal = winGoal;
}

void Game::end()
{
	for (auto event : endGameEvent) {
		event->trigger();
	}
}

void Game::lost()
{
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
	turn.reset();
}

void Game::win()
{
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
		sf::RectangleShape tileRectangle(sf::Vector2f{static_cast<float>(mapInfo->getTileWidth()), static_cast<float>(mapInfo->getTileHeight())});
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

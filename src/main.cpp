#include "Map.h"
#include "Entity/Player.h"
#include "CollisionHandler.h"
#include "Turn.h"
#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "VectorOfTurn.h"
using namespace std;

int main()
{
	auto map = make_shared<Map>();
	auto collisionHandler = make_shared<CollisionHandler>();
	collisionHandler->setMap(map);
	Turn turn;
	map->generateTileset();
	map->generateMap();
	map->setWindowsHeight(448);
	map->setWindowsWidth(704);
	int tileWidth = map->getWindowsWidth() / 11;
	int tileHeight = map->getWindowsHeight() / 7;
	sf::RenderWindow window(sf::VideoMode(map->getWindowsWidth(), map->getWindowsHeight()), "Game");
	VectorOfTurn turns;
	auto player1 = make_shared<Player>();
	auto player2 = make_shared<Player>();
	player1->setPosition( {5, 0});
	player1->setCollisionHandler(collisionHandler);
	player2->setPosition( {5, 6});
	player2->setCollisionHandler(collisionHandler);
	turn.reset();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					turn.addMovement(player1, { -1, 0});
				} else if (event.key.code == sf::Keyboard::Right) {
					turn.addMovement(player1, {1, 0});
				} else if (event.key.code == sf::Keyboard::Up) {
					turn.addMovement(player1, {0, -1});
				} else if (event.key.code == sf::Keyboard::Down) {
					turn.addMovement(player1, {0, 1});
				}

				if (event.key.code == sf::Keyboard::A) {
					turn.addMovement(player2, { -1, 0});
				} else if (event.key.code == sf::Keyboard::D) {
					turn.addMovement(player2, {1, 0});
				} else if (event.key.code == sf::Keyboard::W) {
					turn.addMovement(player2, {0, -1});
				} else if (event.key.code == sf::Keyboard::S) {
					turn.addMovement(player2, {0, 1});
				}
			}
		}
		if (turn.shouldApply()) {
			turn.apply();
			vector<int> tour;
			for (auto tile : map->getTiles()) {
				if (tile->getTileType()->isWalkable()) {
					auto distance = tile->getPosition() - player2->getPosition();
					if (abs(distance.x) <= 1 && abs(distance.y) <= 1) {
						tour.push_back(0);
					} else {
						tour.push_back(1);
					}
				} else {
				}
			}
			turns.addTurn(tour);
 			for (int prob : tour) {
 				cout << prob << ", ";
 			}
 			cout << endl;
		}



		     window.clear(sf::Color::Black);

		for (auto i : map->getTiles()) {
			sf::RectangleShape tileRectangle(sf::Vector2f(tileWidth, tileHeight));
			tileRectangle.setFillColor(i->getTileType()->getColor());
			tileRectangle.setPosition(i->getPosition().x * tileWidth, i->getPosition().y * tileHeight);
			window.draw(tileRectangle);
		}
		sf::RectangleShape playerRect(sf::Vector2f(tileWidth, tileHeight));
		playerRect.setFillColor(sf::Color::White);
		playerRect.setPosition(player1->getPosition().x * tileWidth, player1->getPosition().y * tileHeight);
		window.draw(playerRect);

		sf::RectangleShape playerRect2(sf::Vector2f(tileWidth, tileHeight));
		playerRect2.setFillColor(sf::Color::Blue);
		playerRect2.setPosition(player2->getPosition().x * tileWidth, player2->getPosition().y * tileHeight);
		window.draw(playerRect2);
		window.display();
	}
	return 0;
}

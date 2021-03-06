#pragma once

#include <vector>
#include "Turn.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include <boost/numeric/ublas/matrix.hpp>

class Goal;
class Map;
class Entity;
class CollisionHandler;
class MapPositionTile;
class Event;
class TreasureFound;
class Observation;
class AppendMatrixProvider;
class NodeFinding;
class ListeNode;
class PositionMatrix;
class Tile;

class Game
{
public:
	Game();
	void addEntity(std::shared_ptr<Entity> entity);
	void setWasdControlled(std::shared_ptr<Entity> entity);
	void setArrowControlled(std::shared_ptr<Entity> entity);
	void setWinGoal(std::shared_ptr<Goal> winGoal);
	void setLostGoal(std::shared_ptr<Goal> lostGoal);
	
	void init();
	void mainLoop();
	void reset();
	void lost();
	void win();
	void end();
	void close();
	void render();
	void handleEvent();
	
	std::shared_ptr<Goal> getWinGoal() const;
	std::shared_ptr<Goal> getLostGoal() const;
	std::shared_ptr<Map> getMap();
	
	void addFrameEvent(std::shared_ptr<Event> event);
	void addEndGameEvent(std::shared_ptr<Event> event);
	
private:
	std::vector<std::shared_ptr<Tile>> mappedTiles;
	sf::Texture textureWin;
	sf::Texture textureLost;
	bool fogEnabled = true;
	bool probsEnabled = false;
	void keyChanged();
	std::shared_ptr<AppendMatrixProvider> completeMatrixProvider;
	std::shared_ptr<Observation> observation;
	sf::RenderWindow window;
	Turn turn;
	std::vector<std::shared_ptr<Entity>> entities;
	std::set<std::shared_ptr<Event>> frameEvents;
	std::set<std::shared_ptr<Event>> endGameEvent;
	
	boost::numeric::ublas::matrix<double> history;
	
	std::shared_ptr<MapPositionTile> mapPositionTile;
	std::shared_ptr<CollisionHandler> collisionHandler;
	std::shared_ptr<Map> map;
	std::shared_ptr<Entity> wasdControlled;
	std::shared_ptr<Entity> arrowControlled;
	std::shared_ptr<Goal> winGoal;
	std::shared_ptr<TreasureFound> treasureFound;
	std::shared_ptr<Goal> lostGoal;
	std::shared_ptr<NodeFinding> nodeFinding;
	std::shared_ptr<ListeNode> listeNode;
	std::shared_ptr<PositionMatrix> positionMatrix;
	std::map<sf::Keyboard::Key, bool> keyPressed;
};

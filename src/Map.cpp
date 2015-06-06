#include "Map.h"

using namespace std;

Map::Map()
{

}

void Map::generateMap()
{
	tiles.clear();
	std::vector<int> map {
		0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 15, 5 , 5 , 5 , 20,
		14, 16, 0 , 15, 5 , 5 , 5 , 16 , 0, 0 , 0 , 4 , 0 , 0 , 0 , 6 ,
		6 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 15, 5 , 5 , 16, 0 , 7 ,
		6 , 0 , 15, 5 , 5 , 16, 0 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 2 ,
		7 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 15, 5 , 5 , 16, 0 , 0 ,
		2 , 0 , 13, 12, 0 , 8 , 0 , 8 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 8 ,
		0 , 0 , 10, 11, 0 , 7 , 0 , 19, 5 , 16, 0 , 0 , 0 , 0 , 13, 18,
		0 , 0 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 10, 11
	};

	int width = 16;
	int height = 8;
	sf::Vector2i position;

	for (int t : map) {
		auto tile = make_shared<Tile>();
		tile->setTileType(tileSet[t]);
		tile->setPosition(position);
		tiles.push_back(tile);
		position.x ++;
		if (position.x >= width) {
			position.x = 0;
			position.y ++;
		}


	}


}

void Map::generateTileset()
{
	
	auto texture1 = make_shared<sf::Texture>();
	auto texture2 = make_shared<sf::Texture>();
	auto texture3 = make_shared<sf::Texture>();
	auto texture4 = make_shared<sf::Texture>();
	auto texture5 = make_shared<sf::Texture>();
	auto texture6 = make_shared<sf::Texture>();
	auto texture7 = make_shared<sf::Texture>();
	auto texture8 = make_shared<sf::Texture>();
	auto texture9 = make_shared<sf::Texture>();
	auto texture10 = make_shared<sf::Texture>();
	auto texture11 = make_shared<sf::Texture>();
	auto texture12 = make_shared<sf::Texture>();
	auto texture13 = make_shared<sf::Texture>();
	auto texture14 = make_shared<sf::Texture>();
	auto texture15 = make_shared<sf::Texture>();
	auto texture16 = make_shared<sf::Texture>();
	auto texture17 = make_shared<sf::Texture>();
	auto texture18 = make_shared<sf::Texture>();
	auto texture19 = make_shared<sf::Texture>();
	auto texture20 = make_shared<sf::Texture>();
	auto texture21 = make_shared<sf::Texture>();
	texture1->loadFromFile("res/tileset.png", sf::IntRect{0, 0, 16, 16});
	texture2->loadFromFile("res/tileset.png", sf::IntRect{16, 0, 16, 16});
	texture3->loadFromFile("res/tileset.png", sf::IntRect{32, 0, 16, 16});
	texture4->loadFromFile("res/tileset.png", sf::IntRect{48, 0, 16, 16});
	texture5->loadFromFile("res/tileset.png", sf::IntRect{64, 0, 16, 16});
	texture6->loadFromFile("res/tileset.png", sf::IntRect{80, 0, 16, 16});
	texture7->loadFromFile("res/tileset.png", sf::IntRect{96, 0, 16, 16});
	texture8->loadFromFile("res/tileset.png", sf::IntRect{112, 0, 16, 16});
	texture9->loadFromFile("res/tileset.png", sf::IntRect{128, 0, 16, 16});
	texture10->loadFromFile("res/tileset.png", sf::IntRect{144, 0, 16, 16});
	texture11->loadFromFile("res/tileset.png", sf::IntRect{160, 0, 16, 16});
	texture12->loadFromFile("res/tileset.png", sf::IntRect{176, 0, 16, 16});
	texture13->loadFromFile("res/tileset.png", sf::IntRect{192, 0, 16, 16});
	texture14->loadFromFile("res/tileset.png", sf::IntRect{208, 0, 16, 16});
	texture15->loadFromFile("res/tileset.png", sf::IntRect{224, 0, 16, 16});
	texture16->loadFromFile("res/tileset.png", sf::IntRect{240, 0, 16, 16});
	texture17->loadFromFile("res/tileset.png", sf::IntRect{256, 0, 16, 16});
	texture18->loadFromFile("res/tileset.png", sf::IntRect{272, 0, 16, 16});
	texture19->loadFromFile("res/tileset.png", sf::IntRect{288, 0, 16, 16});
	texture20->loadFromFile("res/tileset.png", sf::IntRect{304, 0, 16, 16});
	texture21->loadFromFile("res/tileset.png", sf::IntRect{320, 0, 16, 16});
	auto tileMurLac = make_shared<TileType>();
	auto tileMurHori = make_shared<TileType>();
	auto tileMurVerti = make_shared<TileType>();
	auto tileMurVertiEndDown = make_shared<TileType>();
	auto tileMurVertiEndUp = make_shared<TileType>();
	auto tileMurCornerDR = make_shared<TileType>();
	auto tileMurBigLacDL = make_shared<TileType>();
	auto tileMurBigLacDR = make_shared<TileType>();
	auto tileMurBigLacUR = make_shared<TileType>();
	auto tileMurBigLacUL = make_shared<TileType>();
	auto tileMurCornerUR = make_shared<TileType>();
	auto tileMurCornerHoriEndLeft = make_shared<TileType>();
	auto tileMurCornerHoriEndRight = make_shared<TileType>();
	auto tileMurAllWater = make_shared<TileType>();
	auto tileMurCoterRight = make_shared<TileType>();
	auto tileMurCornerDL = make_shared<TileType>();
	auto tileMurCornerUL = make_shared<TileType>();
	auto tileDefault = make_shared<TileType>();
	auto tileGoal = make_shared<TileType>();
	auto tileGoalChecked = make_shared<TileType>();
	auto tileParrot = make_shared<TileType>();
	tileDefault->setTexture(texture1);
	tileDefault->setWalkable(true);
	tileParrot->setTexture(texture15);
	tileParrot->setWalkable(true);
	tileMurLac->setTexture(texture2);
	tileMurLac->setWalkable(false);
	tileMurHori->setTexture(texture3);
	tileMurHori->setWalkable(false);
	tileMurVerti->setTexture(texture4);
	tileMurVerti->setWalkable(false);
	tileMurVertiEndDown->setTexture(texture5);
	tileMurVertiEndDown->setWalkable(false);
	tileMurVertiEndUp->setTexture(texture6);
	tileMurVertiEndUp->setWalkable(false);
	tileMurCornerDR->setTexture(texture7);
	tileMurCornerDR->setWalkable(false);
	tileMurBigLacDL->setTexture(texture8);
	tileMurBigLacDL->setWalkable(false);
	tileMurBigLacDR->setTexture(texture9);
	tileMurBigLacDR->setWalkable(false);
	tileMurBigLacUR->setTexture(texture10);
	tileMurBigLacUR->setWalkable(false);
	tileMurBigLacUL->setTexture(texture11);
	tileMurBigLacUL->setWalkable(false);
	tileMurCornerUR->setTexture(texture12);
	tileMurCornerUR->setWalkable(false);
	tileMurCornerHoriEndLeft->setTexture(texture16);
	tileMurCornerHoriEndLeft->setWalkable(false);
	tileMurCornerHoriEndRight->setTexture(texture17);
	tileMurCornerHoriEndRight->setWalkable(false);
	tileMurAllWater->setTexture(texture18);
	tileMurAllWater->setWalkable(false);
	tileMurCoterRight->setTexture(texture19);
	tileMurCoterRight->setWalkable(false);
	tileMurCornerDL->setTexture(texture20);
	tileMurCornerDL->setWalkable(false);
	tileMurCornerUL->setTexture(texture21);
	tileMurCornerUL->setWalkable(false);
	tileGoal->setTexture(texture13);
	tileGoal->setWalkable(true);
	tileGoalChecked->setTexture(texture14);
	tileGoalChecked->setWalkable(true);
	tileSet.push_back(tileDefault); //0
	tileSet.push_back(tileMurLac); //1
	tileSet.push_back(tileGoal); //2
	tileSet.push_back(tileGoalChecked); //3
	tileSet.push_back(tileParrot); //4
	tileSet.push_back(tileMurHori); //5
	tileSet.push_back(tileMurVerti); //6
	tileSet.push_back(tileMurVertiEndDown); //7
	tileSet.push_back(tileMurVertiEndUp); //8
	tileSet.push_back(tileMurCornerDR); //9
	tileSet.push_back(tileMurBigLacDL); //10
	tileSet.push_back(tileMurBigLacDR); //11
	tileSet.push_back(tileMurBigLacUR); //12
	tileSet.push_back(tileMurBigLacUL); //13
	tileSet.push_back(tileMurCornerUR); //14
	tileSet.push_back(tileMurCornerHoriEndLeft); //15
	tileSet.push_back(tileMurCornerHoriEndRight); //16
	tileSet.push_back(tileMurAllWater); //17
	tileSet.push_back(tileMurCoterRight); //18
	tileSet.push_back(tileMurCornerDL); //19
	tileSet.push_back(tileMurCornerUL); //20
	

}

vector<shared_ptr<Tile>> Map::getTiles()
{
	return tiles;
}

vector<shared_ptr<TileType>> Map::getTileSet()
{
	return tileSet;
}

shared_ptr<Tile> Map::getTileAtPosition(sf::Vector2i position)
{
	for (auto i : this->getTiles()) {
		if (i->getPosition() == position) {
			return i;
		}
	}
	return nullptr;
}

uint Map::getHeight()
{
	return height;
}

uint Map::getTileHeight()
{
	return width / 16;
}

uint Map::getTileWidth()
{
	return height / 8;
}

uint Map::getWidth()
{
	return width;
}

void Map::setHeight(uint height)
{
	this->height = height;
}

void Map::setWidth(uint width)
{
	this->width = width;
}

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "maths.h"

#define ls LevelSystem

class LevelSystem {
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

	//static sf::Texture texture;
	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void Render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static sf::IntRect getRect(TILE t);
	static void setColor(TILE t, sf::Color c);
	static void setRect(TILE t, sf::IntRect);
	//get tile at coordinate
	static TILE getTile(sf::Vector2ul);
	//get screenspace coords of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	//get tile at screen space pos
	static TILE getTileAt(sf::Vector2f);
	static std::vector<sf::Vector2f> findTiles(TILE t);
	const static size_t getHeight() {return _height;}
	const static size_t getWidth() {return _width;}
	static sf::Vector2f getStart();
//	static void setTexture(sf::Texture a) { texture = a; }
protected:

	static std::unique_ptr<TILE[]> _tiles;
	static size_t _width;
	static size_t _height;
	static float _tileSize;
	static sf::Vector2f _offset;
	static std::map<TILE, sf::Color> _colours;
	static std::map<TILE, sf::IntRect> _rects;
	static std::vector< std::unique_ptr < sf::Sprite>> _sprites;

	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};
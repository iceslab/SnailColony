/*
 * Map.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include "../headers/Map.h"
#include <utility>

Map::Map()
{
	height = 0;
	width = 0;
	mapWindow = nullptr;
}

Map::Map(int height, int width, int xPos, int yPos) : Map()
{
	this->height = height;
	this->width = width;
	mapWindow = newwin(height, width, yPos, xPos);
	wborder(mapWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	wrefresh(mapWindow);

	tiles.resize(this->height - 2);
	for(auto& tilesRow : tiles)
	{
		tilesRow.resize(this->width - 2);
		for(auto& tile : tilesRow )
		{
			tile.setValue(rand() % 10);
		}
	}

//	refresh();
	printTiles();
//	mvprintw(1, 1, "%d, %d", this->height, this->width);
}

Map::Map(Map&& map)
{
	height = map.height;
	width = map.width;
	mapWindow = map.mapWindow;
	tiles = move(map.tiles);
	snails = move(map.snails);

	map.height = 0;
	map.width = 0;
	map.mapWindow = nullptr;
}

Map& Map::operator= (Map&& map)
{
	height = map.height;
	width = map.width;
	mapWindow = map.mapWindow;
	tiles = move(map.tiles);
	snails = move(map.snails);

	map.height = 0;
	map.width = 0;
	map.mapWindow = nullptr;

	return *this;
}

Map::~Map()
{
	if(nullptr != mapWindow)
	{
		delwin(mapWindow);
		mapWindow = nullptr;
	}
}

int Map::getHeight() const
{
	return height;
}

int Map::getWidth() const
{
	return width;
}

void Map::growMap()
{
	for(auto& tilesRow : tiles)
	{
		for(auto& tile : tilesRow)
		{
			tile.grow();
		}
	}
	printTiles();
}

void Map::printTiles()
{
	for(int row = 1; row < height - 1; row++)
	{
		for(int column = 1; column < width - 1; column++ )
		{
			ColorPair color;
			char value = tiles[row - 1][column - 1].getValue(color);
			wattron(mapWindow, COLOR_PAIR(1));
			mvwprintw(mapWindow, row, column, "%c", value);
			wattroff(mapWindow, COLOR_PAIR(1));
		}
	}
	wrefresh(mapWindow);
	refresh();
}


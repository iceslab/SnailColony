/*
 * Map.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include "../headers/Map.h"

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

	refresh();
	printTiles();
//	mvprintw(1, 1, "%d, %d", this->height, this->width);
}

Map::~Map()
{
	if(nullptr != mapWindow)
	{
		delwin(mapWindow);
		mapWindow = nullptr;
	}
}

void Map::printTiles()
{
	unsigned snailsNumber = snails.size();
	vector<bool> printed(snailsNumber, false);

	for(int row = 1; row < height - 1; row++)
	{
		for(int column = 1; column < width - 1; column++ )
		{
			ColorPair color;
			char value = tiles[row - 1][column - 1].getValue(color);
			attron(COLOR_PAIR(color));
			mvwprintw(mapWindow, row, column, "%c", value);
			attroff(COLOR_PAIR(color));
		}
	}

	wrefresh(mapWindow);
	refresh();
}


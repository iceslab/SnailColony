/*
 * Map.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include "../headers/Map.h"

Map::Map() : colony(0)
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
//	grass = Grass(height - 2, width - 2);
//	colony.setGrass(&grass);

	wborder(mapWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	wrefresh(mapWindow);



//	refresh();
//	printGrass();
//	mvprintw(1, 1, "%d, %d", this->height, this->width);
}

Map::Map(Map&& map)
{
	height = map.height;
	width = map.width;
	mapWindow = map.mapWindow;
	grass = move(map.grass);
	colony = move(colony);
//	colony.setGrass(&grass);

	map.height = 0;
	map.width = 0;
	map.mapWindow = nullptr;
}

Map& Map::operator= (Map&& map)
{
	height = map.height;
	width = map.width;
	mapWindow = map.mapWindow;
	grass = move(map.grass);
	colony = move(map.colony);
//	colony.setGrass(&grass);

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

SnailColony* Map::getColony()
{
	return colony;
}

void Map::setColony(SnailColony* colony)
{
	this->colony = colony;
}

void Map::setGrass(Grass* grass)
{
	this->grass = grass;
}

void Map::growMap()
{
	grass->growGrass();

//	printGrass();
//	printColony();
}

void Map::reprint()
{
	printGrass();
	printColony();
	wrefresh(mapWindow);
	refresh();
}

void Map::printGrass()
{
	int grassHeight = grass->getHeight();
	int grassWidth = grass->getWidth();
	for(int row = 0; row < grassHeight; row++)
	{
		for(int column = 0; column < grassWidth; column++ )
		{
			ColorPair color;
			try
			{
				char value = grass->getTile(column, row).getValueAsChar(color);
				wattron(mapWindow, COLOR_PAIR(color));
				mvwprintw(mapWindow, row + 1, column + 1, "%c", value);
				wattroff(mapWindow, COLOR_PAIR(color));
			}
			catch(invalid_argument &e)
			{
				cout<< "row: " << row <<" / "<< grassHeight << ", column: "<< column << " / "<< grassWidth << endl;
				cout << e.what() << endl;
				getchar();
			}
		}
	}
//	refreshMap();
//	wrefresh(mapWindow);
//	refresh();
}

void Map::printColony()
{
	unsigned snailsNumber = colony->getColonySize();

	for(unsigned i = 0; i < snailsNumber; i++)
	{
		ColorPair color = colony->getSnail(i)->getColor();
		wattron(mapWindow, COLOR_PAIR(color));
		int x = 0, y = 0;
		colony->getSnail(i)->getPos(x, y);
		mvwprintw(mapWindow,
				  y + 1,
				  x + 1,
				  "X");
		wattroff(mapWindow, COLOR_PAIR(color));
	}

//	refreshMap();
//	wrefresh(mapWindow);
//	refresh();
}
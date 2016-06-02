/*
 * Map.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include "../headers/Map.h"

const double Map::dropFallChance = 3.0;

Map::Map() : colony(0), rd(), mt(rd()), dist(0.0, 100.0)
{
	height = 0;
	width = 0;
	mapWindow = nullptr;
	pthread_mutex_init(&mapMutex, nullptr);
}

Map::Map(int height, int width, int xPos, int yPos) : Map()
{
	this->height = height;
	this->width = width;
	mapWindow = newwin(height, width, yPos, xPos);

	wborder(mapWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	wrefresh(mapWindow);
}

Map::~Map()
{
	pthread_mutex_lock(&mapMutex);
	if(nullptr != mapWindow)
	{
		delwin(mapWindow);
		mapWindow = nullptr;
	}
	pthread_mutex_unlock(&mapMutex);
	pthread_mutex_destroy(&mapMutex);
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
}

void Map::resize(int width, int height)
{
	pthread_mutex_lock(&mapMutex);
	if(nullptr != mapWindow)
	{
		delwin(mapWindow);
		mapWindow = nullptr;
	}
	this->width = width;
	this->height = height;
	grass->resize(width - 2, height - 2);
	mapWindow = newwin(height, width, 1, 1);
	wborder(mapWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	pthread_mutex_unlock(&mapMutex);
}

void Map::reprint()
{
	pthread_mutex_lock(&mapMutex);
	printGrass();
	printColony();
	printRain();
	wborder(mapWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	wrefresh(mapWindow);
	pthread_mutex_unlock(&mapMutex);
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
			ColorPair color = ColorPair::BLUE;
			try
			{
				char value = ' ';
				if(!(grass->isRaining() && dist(mt) < dropFallChance))
				{
					value = grass->getTile(column, row).getValueAsChar(color);
				}

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

		ColorPair color = ColorPair::BLACK;
		int x = 0, y = 0;
		colony->getSnailColorAndPosition(i, color, x, y);
		wattron(mapWindow, COLOR_PAIR(color));
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

void Map::printRain()
{
}

/*
 * Map.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#include "../headers/Map.h"

Map::Map(int height, int width, int xPos, int yPos)
{
	this->height = height;
	this->width = width;
	mapWindow = newwin(height, width, yPos, xPos);
	wborder(mapWindow, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(mapWindow);
}

Map::~Map()
{
	delwin(mapWindow);
	mapWindow = nullptr;
}


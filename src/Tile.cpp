/*
 * Tile.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Tile.h"

Tile::Tile(int value)
{
	if(value < 10 && value > 0)
	{
		this->value = value;
	}
	else
	{
		this->value = 0;
	}
}

Tile::~Tile()
{

}

void Tile::grow()
{
	if(value < 9 && value >= 0)
	{
		++value;
	}
	else if (value < 0)
	{
		value = 0;
	}
	else if (value > 9)
	{
		value = 9;
	}
}

void Tile::shrink()
{
	if(value <= 9 && value > 0)
	{
		--value;
	}
	else if (value < 0)
	{
		value = 0;
	}
	else if (value > 9)
	{
		value = 9;
	}
}

char Tile::getValue(ColorPair &color)
{
	char retVal = ' ';
	color = GREEN;
	if(value == 0)
		color = BROWN;
	retVal = value + '0';

	return retVal;
}

void Tile::setValue(int value)
{
	if(value <= 9 && value >= 0)
	{
		this->value = value;
	}
	else
	{
		this->value = 0;
	}
}


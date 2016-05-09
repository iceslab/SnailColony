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
	else
	{
		value = 0;
	}
}

void Tile::shrink()
{
	if(value <= 9 && value > 0)
	{
		--value;
	}
	else
	{
		value = 0;
	}
}

char Tile::getValue(ColorPair &color)
{
	char retVal = 'X';
	if(snails.empty())
	{
		color = GREEN;
		retVal = value + '0';
	}
	else
	{
		color = snails.back()->getColor();
	}

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

void Tile::addSnail(Snail* snail)
{
	snails.push_back(snail);
}

void Tile::removeSnail(Snail* snail)
{
	auto it = find(snails.begin(), snails.end(), snail);
	if(it != snails.end())
	{
		snails.erase(it);
	}
}

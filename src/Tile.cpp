/*
 * Tile.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Tile.h"

const int Tile::minTileValue = 0;
const int Tile::maxTileValue = 9;

Tile::Tile(int value)
{
	if(value <= maxTileValue && value > 0)
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

unsigned Tile::grow(unsigned amount)
{
	if(value < maxTileValue)
	{
		if(amount > maxTileValue - value)
		{
			value = maxTileValue;
			amount = static_cast<unsigned>(maxTileValue - value);
		}
		else
		{
			value += amount;
		}
	}

	return amount;
}

unsigned Tile::shrink(unsigned amount)
{
	if(value > minTileValue)
	{
		if(amount > minTileValue + value)
		{
			value = minTileValue;
			amount = static_cast<unsigned>(value - minTileValue);
		}
		else
		{
			value -= amount;
		}
	}
	else
	{
		amount = 0;
	}

	return amount;
}

int Tile::getValue() const
{
	return value;
}

char Tile::getValueAsChar(ColorPair &color) const
{
	color = GREEN;
	if(value == 0)
		color = BROWN;
	return static_cast<char>(value + '0');
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


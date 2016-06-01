/*
 * Tile.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Tile.h"

const int Tile::minTileValue = 0;
const int Tile::maxTileValue = 9;

Tile::Tile(int value) : value(0)
{
	pthread_mutex_init(&tileMutex, nullptr);
	setValue(value);
}

Tile::~Tile()
{
	pthread_mutex_destroy(&tileMutex);
}

unsigned Tile::grow(unsigned amount)
{
	pthread_mutex_lock(&tileMutex);
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
	pthread_mutex_unlock(&tileMutex);
	return amount;
}

unsigned Tile::shrink(unsigned amount)
{
	pthread_mutex_lock(&tileMutex);
	if(value > minTileValue)
	{
		if(amount > minTileValue + value)
		{
			amount = static_cast<unsigned>(value - minTileValue);
			value = minTileValue;
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
	pthread_mutex_unlock(&tileMutex);
	return amount;
}

int Tile::getValue() const
{
	pthread_mutex_lock(&tileMutex);
	int retVal = value;
	pthread_mutex_unlock(&tileMutex);
	return retVal;
}

char Tile::getValueAsChar(ColorPair &color) const
{
	pthread_mutex_lock(&tileMutex);
	int retVal = value;
	color = GREEN;
	if(value == 0)
		color = BROWN;
	pthread_mutex_unlock(&tileMutex);
	return static_cast<char>(retVal + '0');
}

void Tile::setValue(int value)
{
	pthread_mutex_lock(&tileMutex);
	if(value <= 9 && value >= 0)
	{
		this->value = value;
	}
	else
	{
		this->value = 0;
	}
	pthread_mutex_unlock(&tileMutex);
}


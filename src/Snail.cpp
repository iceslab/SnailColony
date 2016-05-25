/*
 * Snail.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include <fstream>
#include <sstream>
#include "../headers/Snail.h"

const int Snail::minHunger = 0;
const int Snail::maxHunger = 10;

Snail::Snail(ColorPair color, Grass* grass, int x, int y) :
		color(color), hunger(minHunger), state(ALIVE), grass(grass)
{
	pthread_mutex_init(&snailMutex, nullptr);
	posX = (x % grass->getWidth());
	posY = (y % grass->getHeight());

}

Snail::~Snail()
{
	setState(DEAD);
}

void Snail::setPos(int x, int y)
{
	pthread_mutex_lock(&snailMutex);
	posX = x;
	posY = y;
	pthread_mutex_unlock(&snailMutex);
}

void Snail::changePos(int dx, int dy)
{
	pthread_mutex_lock(&snailMutex);
	posX += dx;
	posY += dy;
	pthread_mutex_unlock(&snailMutex);
}

void Snail::getPos(int &x, int &y) const
{
	pthread_mutex_lock(&snailMutex);
	x = posX;
	y = posY;
	pthread_mutex_unlock(&snailMutex);
}

void Snail::setState(SnailState state)
{
	pthread_mutex_lock(&snailMutex);
	this->state = state;
	pthread_mutex_unlock(&snailMutex);
}

SnailState Snail::getState() const
{
	pthread_mutex_lock(&snailMutex);
	SnailState retVal = state;
	pthread_mutex_unlock(&snailMutex);
	return retVal;
}

void Snail::setGrass(Grass* grass)
{
	this->grass = grass;
}

ColorPair Snail::getColor() const
{
	return color;
}

void Snail::setColor(ColorPair color)
{
	this->color = color;
}

void Snail::eat()
{
	hunger -= grass->getTile(posX, posY).shrink(hunger);
}

bool Snail::makeRandomMove()
{
	bool retVal = false;
	if(state == ALIVE)
	{
		if (increaseHunger() > 0)
		{
			int deltaX = 0;
			int deltaY = 0;
			drawMove(deltaX, deltaY);
			changePos(deltaX, deltaY);
			eat();
			retVal = true;
		}
		else
		{
			setState(DEAD);
		}
	}
	return retVal;
}

void Snail::start()
{
	pthread_create(&snailThread, NULL, Snail::snailThreadFn, this);
}

unsigned Snail::increaseHunger(unsigned amount)
{
	if(hunger < maxHunger)
	{
		if(amount > maxHunger - hunger)
		{
			hunger = maxHunger;
			amount = static_cast<unsigned>(maxHunger - hunger);
		}
		else
		{
			hunger += amount;
		}
	}
	else
	{
		amount = 0;
	}

	return amount;
}

void Snail::drawMove(int& deltaX, int& deltaY)
{
	SnailMove move = static_cast<SnailMove>(rand() % 3);

	switch(move)
	{
		case ONLY_X:
			deltaX = 1 * pow(-1, (rand() % 2));
			deltaY = 0;
			break;
		case ONLY_Y:
			deltaX = 0;
			deltaY = 1 * pow(-1, (rand() % 2));
			break;
		case BOTH_XY:
			deltaX = 1 * pow(-1, (rand() % 2));
			deltaY = 1 * pow(-1, (rand() % 2));
			break;
		default:
			break;
	}

	auto width = grass->getWidth();
	auto height = grass->getHeight();

	if(posX == 0 && deltaX < 0)
	{
		deltaX = 1;
	}
	if(posX == (grass->getWidth() - 1) && deltaX > 0)
	{
		deltaX = -1;
	}
	if(posY == 0 && deltaY < 0)
	{
		deltaY = 1;
	}
	if(posY == (grass->getHeight() - 1) && deltaY > 0)
	{
		deltaY = -1;
	}
}

void* Snail::snailThreadFn(void* snail)
{
	while(true)
	{
		if(!static_cast<Snail*>(snail)->makeRandomMove())
			break;
		usleep(100000);
	}
}

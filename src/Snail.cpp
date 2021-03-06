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
const int Snail::maxHunger = 100;

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
	posX %= grass->getWidth();
	posY %= grass->getHeight();
	pthread_mutex_unlock(&snailMutex);
}

void Snail::changePos(int dx, int dy)
{
	pthread_mutex_lock(&snailMutex);
	posX += dx;
	posY += dy;
	posX %= grass->getWidth();
	posY %= grass->getHeight();
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

int Snail::getHunger() const
{
	pthread_mutex_lock(&snailMutex);
	int retVal = hunger;
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
	int hungerDecrease = grass->getTile(posX, posY).shrink(hunger);
	pthread_mutex_lock(&snailMutex);
	hunger -= hungerDecrease;
	pthread_mutex_unlock(&snailMutex);
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
	pthread_mutex_lock(&snailMutex);
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
	pthread_mutex_unlock(&snailMutex);
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
	Snail* snailPtr = static_cast<Snail*>(snail);
	while(true)
	{
		pthread_mutex_lock(&snailPtr->grass->rainMutex);
		while(snailPtr->grass->isRaining())
		{
			snailPtr->setState(SnailState::HIDDEN);
			pthread_cond_wait(&snailPtr->grass->rainVariable, &snailPtr->grass->rainMutex);
			snailPtr->setState(SnailState::ALIVE);
		}
		pthread_mutex_unlock(&snailPtr->grass->rainMutex);

		if(!snailPtr->makeRandomMove())
			break;
		usleep(100000);
	}
	return snail;
}

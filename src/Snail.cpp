/*
 * Snail.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Snail.h"

const int Snail::minHunger = 0;
const int Snail::maxHunger = 10;

Snail::Snail(ColorPair color, Grass* grass, int x, int y) :
		posX(x), posY(y), color(color), hunger(minHunger), state(ALIVE), grass(grass)
{
	pthread_create(&snailThread, NULL, Snail::snailThreadFn, this);


}

Snail::~Snail()
{

}

int Snail::getPosX() const
{
	return posX;
}

void Snail::setPosX(int posX)
{
	this->posX = posX;
}

int Snail::getPosY() const
{
	return posY;
}

void Snail::setPosY(int posY)
{
	this->posY = posY;
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
			posX += deltaX;
			posY += deltaY;
			eat();
			retVal = true;
		}
		else
		{
			state = DEAD;
		}
	}
	return retVal;
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
	if(posX == grass->getWidth() && deltaX > 0)
	{
		deltaX = -1;
	}
	if(posY == 0 && deltaY < 0)
	{
		deltaY = 1;
	}
	if(posY == grass->getWidth() && deltaY > 0)
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

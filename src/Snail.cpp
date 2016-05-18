/*
 * Snail.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Snail.h"

const int Snail::minHunger = 0;
const int Snail::maxHunger = 10;

Snail::Snail(ColorPair color, Grass* grass) :
		posX(0), posY(0), color(color), hunger(0), state(ALIVE), grass(grass)
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

void Snail::makeRandomMove()
{
	if(state == ALIVE)
	{
		if (decreaseHunger() > 0)
		{
			int deltaX = 0;
			int deltaY = 0;
			drawMove(deltaX, deltaY);
			posX += deltaX;
			posY += deltaY;
			eat();
		}
		else
		{
			state = DEAD;
		}
	}
}

unsigned Snail::decreaseHunger(unsigned amount)
{
	if(hunger > minHunger)
	{
		if(amount > minHunger + hunger)
		{
			hunger = minHunger;
			amount = static_cast<unsigned>(hunger - minHunger);
		}
		else
		{
			hunger -= amount;
		}
	}

	return amount;
}

void Snail::drawMove(int& deltaX, int& deltaY)
{
	SnailMove move = static_cast<SnailMove>(rand() % 3);

	switch(move)
	{
		case ONLY_X:
			deltaX = 1 * ((-1) * (rand() % 2));
			break;
		case ONLY_Y:
			deltaY = 1 * ((-1) * (rand() % 2));
			break;
		case BOTH_XY:
			deltaX = 1 * ((-1) * (rand() % 2));
			deltaY = 1 * ((-1) * (rand() % 2));
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
		deltaX = 1;
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
		static_cast<Snail*>(snail)->makeRandomMove();
	}
}

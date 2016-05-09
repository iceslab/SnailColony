/*
 * Snail.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Snail.h"


Snail::Snail()
{
	posX = 0;
	posY = 0;
	color = BLUE;
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

ColorPair Snail::getColor() const
{
	return color;
}

void Snail::setColor(ColorPair color)
{
	this->color = color;
}

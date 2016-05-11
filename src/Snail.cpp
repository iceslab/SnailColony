/*
 * Snail.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/Snail.h"


Snail::Snail(ColorPair color)
{
	posX = 0;
	posY = 0;
	this->color = color;
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

void Snail::setMap(Map& map)
{
	this->map = &map;
}

ColorPair Snail::getColor() const
{
	return color;
}

void Snail::setColor(ColorPair color)
{
	this->color = color;
}

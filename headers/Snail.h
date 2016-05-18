/*
 * Snail.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_SNAIL_H_
#define HEADERS_SNAIL_H_

#include "../headers/includes.h"
#include "../headers/Grass.h"

class Snail
{
public:
	Snail(ColorPair color, Grass* grass);
	virtual ~Snail();

	int getPosX() const;
	void setPosX(int posX);

	int getPosY() const;
	void setPosY(int posY);

	void setGrass(Grass* tiles);

	ColorPair getColor() const;
	void setColor(ColorPair color);

	void eat();
	void makeRandomMove();

protected:
private:
	int posX;
	int posY;
	ColorPair color;
	SnailState state;
	Grass* grass;
	int hunger;

	pthread_t snailThread;

	static const int minHunger;
	static const int maxHunger;

	unsigned decreaseHunger(unsigned amount = 1);
	void drawMove(int& deltaX, int& deltaY);

	static void* snailThreadFn(void* snail);
};

enum SnailMove
{
	ONLY_X,
	ONLY_Y,
	BOTH_XY
};

#endif /* HEADERS_SNAIL_H_ */

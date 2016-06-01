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
	Snail(ColorPair color, Grass* grass, int x, int y);
	void init();
	virtual ~Snail();

	void setPos(int x, int y);
	void changePos(int dx, int dy);
	void getPos(int &x, int &y) const;

	void setGrass(Grass* tiles);
	bool getStop() const;
	void setStop(bool val);

	void setState(SnailState state);
	SnailState getState() const;
	int getHunger() const;

	ColorPair getColor() const;
	void setColor(ColorPair color);

	void eat();
	bool makeRandomMove();

	void start();

	static const int minHunger;
	static const int maxHunger;
protected:
private:
	int posX;
	int posY;
	ColorPair color;
	SnailState state;
	Grass* grass;
	int hunger;
	bool stop;

	pthread_t snailThread;
	mutable pthread_mutex_t snailMutex;

	unsigned increaseHunger(unsigned amount = 1);
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

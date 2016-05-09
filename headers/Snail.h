/*
 * Snail.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_SNAIL_H_
#define HEADERS_SNAIL_H_

#include "../headers/includes.h"

class Snail
{
public:
	Snail();
	virtual ~Snail();

	int getPosX() const;
	void setPosX(int posX);

	int getPosY() const;
	void setPosY(int posY);

	ColorPair getColor() const;
	void setColor(ColorPair color);

protected:
private:
	int posX;
	int posY;
	ColorPair color;

};

#endif /* HEADERS_SNAIL_H_ */

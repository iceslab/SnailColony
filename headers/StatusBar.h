/*
 * StatusBar.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_STATUSBAR_H_
#define HEADERS_STATUSBAR_H_

#include "../headers/includes.h"
#include "../headers/SnailColony.h"

class StatusBar
{
public:
	StatusBar();
	StatusBar(int height, int width, int xPos, int yPos);
	virtual ~StatusBar();

	void setColony(SnailColony* colony);
	void setGrass(Grass* grass);
	void start();
	void refreshStatus();

protected:
private:
	int height;
	int width;
	WINDOW* statusWindow;
	SnailColony* colony;
	Grass* grass;
};


#endif /* HEADERS_STATUSBAR_H_ */

/*
 * StatusBar.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_STATUSBAR_H_
#define HEADERS_STATUSBAR_H_

#include "../headers/includes.h"

class StatusBar
{
public:
	StatusBar();
	StatusBar(int height, int width, int xPos, int yPos);
	virtual ~StatusBar();

	int getHeight() const {
		return height;
	}

	int getWidth() const {
		return width;
	}

protected:
private:
	int height;
	int width;
	WINDOW* statusWindow;
};


#endif /* HEADERS_STATUSBAR_H_ */

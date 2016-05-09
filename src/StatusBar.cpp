/*
 * StatusBar.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include "../headers/StatusBar.h"

StatusBar::StatusBar()
{
	height = 0;
	width = 0;
	statusWindow = nullptr;
}

StatusBar::StatusBar(int height, int width, int xPos, int yPos) : StatusBar()
{
	this->height = height;
	this->width = width;
	statusWindow = newwin(height, width, yPos, xPos);
	wborder(statusWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	wrefresh(statusWindow);
	refresh();
//	mvprintw(2, 1, "%d, %d", this->height, this->width);
}

StatusBar::~StatusBar()
{
	if(nullptr != statusWindow)
	{
		delwin(statusWindow);
		statusWindow = nullptr;
	}
}



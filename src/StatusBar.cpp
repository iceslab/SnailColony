/*
 * StatusBar.cpp
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#include <sstream>
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
}

StatusBar::~StatusBar()
{
	if(nullptr != statusWindow)
	{
		delwin(statusWindow);
		statusWindow = nullptr;
	}
}

void StatusBar::setColony(SnailColony* colony)
{
	this->colony = colony;
}

void StatusBar::setGrass(Grass* grass)
{
	this->grass = grass;
}

void StatusBar::refreshStatus()
{
	unsigned i = 0;

	werase(statusWindow);
	wborder(statusWindow, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0');
	for(; i < colony->getColonySize(); i++)
	{
		int x = 0, y = 0;
		ColorPair color = ColorPair::BLACK;
		SnailState state = colony->getSnailState(i);
		colony->getSnailColorAndPosition(i, color, x, y);

		stringstream ss;
		ss
		<< " - x: "<< x
		<<", y: "<< y
		<<" - state: " << snailStateToString(state)
		<<", hunger: " << colony->getSnailHunger(i) << "/"<< Snail::maxHunger;

		wattron(statusWindow, COLOR_PAIR(color));
		mvwprintw(statusWindow, i + 1, 2, "X");
		wattroff(statusWindow, COLOR_PAIR(color));
		mvwprintw(statusWindow, i + 1, 3, ss.str().c_str());
	}

	stringstream ss;
	ss << "Growth chance : "<< grass->getGrowthChancePercentage() << "%%";
	mvwprintw(statusWindow, 1, 50, ss.str().c_str());

	wrefresh(statusWindow);
	refresh();
}

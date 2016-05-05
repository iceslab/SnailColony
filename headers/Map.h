/*
 * Map.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "../headers/CommonUtils.h"

class Map {
public:
	WINDOW* mapWindow;

	Map(int height, int width, int xPos, int yPos);
	virtual ~Map();

protected:
private:
	int height;
	int width;

};

#endif /* SRC_MAP_H_ */

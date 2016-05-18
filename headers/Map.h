/*
 * Map.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "../headers/includes.h"
#include "../headers/Grass.h"
#include "../headers/SnailColony.h"

class Map {
public:
	Map();
	Map(int height, int width, int xPos, int yPos);
	Map(Map&& map);
	Map& operator= (Map&& map);
	virtual ~Map();

	int getHeight() const;
	int getWidth() const;

	SnailColony& getColony();

	void growMap();



protected:
private:
	int height;
	int width;
	WINDOW* mapWindow;
	Grass grass;
	SnailColony colony;

	void printGrass();
	void printColony();
};

#endif /* SRC_MAP_H_ */

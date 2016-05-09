/*
 * Map.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "../headers/includes.h"
#include "../headers/Snail.h"
#include "../headers/Tile.h"

class Map {
public:
	Map();
	Map(int height, int width, int xPos, int yPos);
	virtual ~Map();

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
	WINDOW* mapWindow;
	vector<vector<Tile>> tiles;
	vector<Snail> snails;

	void printTiles();
};

#endif /* SRC_MAP_H_ */

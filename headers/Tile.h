/*
 * Tile.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_TILE_H_
#define HEADERS_TILE_H_

#include "../headers/includes.h"

class Tile {
public:
	Tile(int value = 0);
	virtual ~Tile();

	void grow();
	void shrink();

	char getValue(ColorPair &color);
	void setValue(int value);

protected:
private:
	int value;
};

#endif /* HEADERS_TILE_H_ */

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

	unsigned grow(unsigned amount = 1);
	unsigned shrink(unsigned amount = 1);

	int getValue() const;
	char getValueAsChar(ColorPair &color) const;
	void setValue(int value);

protected:
private:
	int value;
	static const int minTileValue;
	static const int maxTileValue;
};

#endif /* HEADERS_TILE_H_ */

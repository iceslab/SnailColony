/*
 * Tile.h
 *
 *  Created on: 9 maj 2016
 *      Author: user
 */

#ifndef HEADERS_TILE_H_
#define HEADERS_TILE_H_

#include "../headers/includes.h"
#include "../headers/Snail.h"

class Tile {
public:
	Tile(int value = 0);
	virtual ~Tile();

	void grow();
	void shrink();

	char getValue(ColorPair &color);
	void setValue(int value);

	void addSnail(Snail* snail);
	void removeSnail(Snail* snail);
protected:
private:
	int value;
	vector<Snail*> snails;
};

#endif /* HEADERS_TILE_H_ */

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
	virtual ~Map();

	int getHeight() const;
	int getWidth() const;

	SnailColony* getColony();

	void setColony(SnailColony* colony);
	void setGrass(Grass* grass);

	void growMap();
	void resize(int width, int height);
	void reprint();

protected:
private:
	int height;
	int width;
	WINDOW* mapWindow;
	Grass* grass;
	SnailColony* colony;
	pthread_mutex_t mapMutex;

	void printGrass();
	void printColony();
	void printRain();

	random_device rd;
	mt19937 mt;
	uniform_real_distribution<double> dist;

	static const double dropFallChance;
};

#endif /* SRC_MAP_H_ */

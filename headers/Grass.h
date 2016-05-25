//
// Created by user on 11.05.16.
//

#ifndef SNAILCOLONY_GRASS_H
#define SNAILCOLONY_GRASS_H

#include "../headers/includes.h"
#include "../headers/Tile.h"

class Grass
{
public:
    Grass(int height = 0, int width = 0, int startingTileValue = -1);
    ~Grass();
    Grass(Grass&& grass);
    Grass& operator= (Grass&& grass);

    void growGrass();
    const Tile& getTile(int posX, int posY) const;
    Tile& getTile(int posX, int posY);

    int getHeight() const;
    int getWidth() const;

private:
    int height;
    int width;
    Tile** tiles;
//    vector<vector<Tile>> tiles;
};


#endif //SNAILCOLONY_GRASS_H

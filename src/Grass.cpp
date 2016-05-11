//
// Created by user on 11.05.16.
//

#include "../headers/Grass.h"

Grass::Grass(int height, int width, int startingTileValue) :
    height(height), width(width)
{
    if(startingTileValue > 9)
    {
        startingTileValue = 9;
    }

    tiles.resize(this->height);
    for(auto& tilesRow : tiles)
    {
        tilesRow.resize(this->width);
        for(auto& tile : tilesRow )
        {
            if(startingTileValue < 0)
            {
                tile.setValue(rand() % 10);
            }
            else
            {
                tile.setValue(startingTileValue);
            }
        }
    }
}

Grass::Grass(Grass&& grass)
{
    height = grass.height;
    width = grass.width;
    tiles = move(grass.tiles);

    grass.height = 0;
    grass.width = 0;
}

Grass& Grass::operator= (Grass&& grass)
{
    height = grass.height;
    width = grass.width;
    tiles = move(grass.tiles);

    grass.height = 0;
    grass.width = 0;

    return *this;
}

void Grass::growGrass()
{
    for(auto& tilesRow : tiles)
    {
        for(auto& tile : tilesRow)
        {
            tile.grow();
        }
    }
}

const Tile& Grass::getTile(int posX, int posY) const
{
    return tiles[posX][posY];
}

Tile& Grass::getTile(int posX, int posY)
{
    return tiles[posX][posY];
}

int Grass::getHeight() const
{
    return height;
}

int Grass::getWidth() const
{
    return width;
}
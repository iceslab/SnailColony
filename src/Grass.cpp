//
// Created by user on 11.05.16.
//

#include <fstream>
#include "../headers/Grass.h"

Grass::Grass(int height, int width, int startingTileValue) :
    height(height), width(width), tiles()
{
    if(startingTileValue > 9)
    {
        startingTileValue = 9;
    }

    tiles.resize(this->height);
    for(unsigned row = 0; row < this->height; row++)
    {

        tiles[row] = vector<Tile>(this->width);
        for(unsigned column = 0; column < this->width; column++)
        {
            if(startingTileValue < 0)
            {
                tiles[row][column].setValue(rand() % 10);
            }
            else
            {
                tiles[row][column].setValue(startingTileValue);
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
    ofstream ofs("tile.txt", ios::app | ios::out);
    ofs << "posX: " << posX
     << ", size: " << tiles.size() << endl
     << "posY: " << posY
     << ", size: " << tiles[posX].size() << endl << endl;
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
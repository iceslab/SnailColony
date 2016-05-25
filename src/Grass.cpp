//
// Created by user on 11.05.16.
//

#include <fstream>
#include <sstream>
#include "../headers/Grass.h"

Grass::Grass(int height, int width, int startingTileValue) :
    height(height), width(width), tiles(nullptr)
{
    if(startingTileValue > 9)
    {
        startingTileValue = 9;
    }

    tiles = new Tile*[this->height];
//    tiles.resize(this->height);
    for(unsigned row = 0; row < this->height; row++)
    {

//        tiles[row] = vector<Tile>(this->width);
        tiles[row] = new Tile[this->width]();
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

Grass::~Grass()
{
    if(nullptr != tiles)
    {
        for(unsigned row = 0; row < this->height; row++)
        {
            if(nullptr != tiles[row])
            {
                delete [] tiles[row];
                tiles[row] = nullptr;
            }
        }

        delete[] tiles;
        tiles = nullptr;
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
    for(unsigned row = 0; row < this->height; row++)
    {
        for(unsigned column = 0; column < this->width; column++)
        {
            tiles[row][column].grow();
        }
    }
}

const Tile& Grass::getTile(int posX, int posY) const
{
    return tiles[posY][posX];
}

Tile& Grass::getTile(int posX, int posY)
{
    ofstream ofs("tile.txt", ios::app | ios::out);
    ofs << "posX: " << posX
        << ", size: " << width - 1
        << endl
        << "posY: " << posY
        << ", size: " << height - 1
        << endl << endl;
    if(posX >= width)
    {
        stringstream ss;
        ss << "posX >= width, " << posX << " >= " << width << endl
            << "height: "<<height << ", width: "<< width<<endl;
        throw invalid_argument(ss.str());
    }

    if(posY >= height)
    {
        stringstream ss;
        ss << "posY >= height" << posY << " >= " << height << endl
          << "height: "<<height << ", width: "<< width<<endl;
        throw invalid_argument(ss.str());
    }

    return tiles[posY][posX];
}

int Grass::getHeight() const
{
    return height;
}

int Grass::getWidth() const
{
    return width;
}
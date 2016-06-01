//
// Created by user on 11.05.16.
//

#include <fstream>
#include <sstream>
#include "../headers/Grass.h"

Grass::Grass(int height, int width, int startingTileValue, double growthChancePercentage) :
    height(height), width(width), tiles(nullptr), rd(), mt(rd()), dist(0.0, 100.0), raining(false)
{
    pthread_mutex_init(&grassMutex, nullptr);
    pthread_mutex_init(&rainMutex, nullptr);
    pthread_cond_init(&rainVariable, nullptr);
    setGrowthChancePercentage(growthChancePercentage);

    if(startingTileValue > 9)
    {
        startingTileValue = 9;
    }

    pthread_mutex_lock(&grassMutex);
    createGrass(startingTileValue);
    pthread_mutex_unlock(&grassMutex);
}

Grass::~Grass()
{
    pthread_mutex_lock(&grassMutex);
    eraseGrass();
    pthread_mutex_unlock(&grassMutex);

    pthread_cond_destroy(&rainVariable);
    pthread_mutex_destroy(&rainMutex);
    pthread_mutex_destroy(&grassMutex);
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

void Grass::createGrass(int startingTileValue)
{
    if(nullptr == tiles)
    {
        tiles = new Tile*[this->height];
        for(unsigned row = 0; row < this->height; row++)
        {
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
}

void Grass::eraseGrass()
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

void Grass::growGrass()
{
    for(unsigned row = 0; row < this->height; row++)
    {
        for(unsigned column = 0; column < this->width; column++)
        {
            if(dist(mt) < growthChancePercentage)
                tiles[row][column].grow();
        }
    }
}

Tile& Grass::getTile(int posX, int posY)
{
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

void Grass::setHeight(int height)
{

}

void Grass::setWidth(int width)
{

}

int Grass::getHeight() const
{
    return height;
}

int Grass::getWidth() const
{
    return width;
}

void Grass::setGrowthChancePercentage(double percentage)
{
    pthread_mutex_lock(&grassMutex);
    if(percentage > 100.0)
    {
        growthChancePercentage = 100.0;
    }
    else if(percentage < 0.0)
    {
        growthChancePercentage = 0.0;
    }
    else
    {
        growthChancePercentage = percentage;
    }
    pthread_mutex_unlock(&grassMutex);
}

double Grass::getGrowthChancePercentage() const
{
    pthread_mutex_lock(&grassMutex);
    double retVal = growthChancePercentage;
    pthread_mutex_unlock(&grassMutex);
    return retVal;
}

bool Grass::isRaining()
{
    return raining;
}

void Grass::toggleRaining()
{
    pthread_mutex_lock(&rainMutex);
    raining = !raining;
    if(!raining)
        pthread_cond_broadcast(&rainVariable);
    pthread_mutex_unlock(&rainMutex);
}
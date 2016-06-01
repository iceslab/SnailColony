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
    Grass(int height = 0, int width = 0, int startingTileValue = -1, double growthChancePercentage = 20.0);
    ~Grass();
    Grass(Grass&& grass);
    Grass& operator= (Grass&& grass);

    void createGrass(int startingTileValue = -1);
    void eraseGrass();

    void growGrass();
    Tile& getTile(int posX, int posY);

    void resize(int width, int height);
    int getHeight() const;
    int getWidth() const;

    void setGrowthChancePercentage(double percentage);
    double getGrowthChancePercentage() const;

    bool isRaining();
    void toggleRaining();

    mutable pthread_mutex_t rainMutex;
    mutable pthread_cond_t rainVariable;
    mutable pthread_mutex_t grassMutex;
private:
    int height;
    int width;
    Tile** tiles;
    double growthChancePercentage;

    bool raining;

    random_device rd;
    mt19937 mt;
    uniform_real_distribution<double> dist;
//    vector<vector<Tile>> tiles;
};


#endif //SNAILCOLONY_GRASS_H

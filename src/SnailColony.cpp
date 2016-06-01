//
// Created by user on 11.05.16.
//

#include "../headers/SnailColony.h"

const unsigned SnailColony::maxColonySize = LAST_SNAIL_COLOR - FIRST_SNAIL_COLOR + 1;

SnailColony::SnailColony(unsigned startingSize) : snails(nullptr), grass(nullptr), snailsCount(0)
{
    pthread_mutex_init(&colonyMutex, nullptr);
    snails = new Snail*[maxColonySize];
    if(startingSize > maxColonySize)
    {
        startingSize = maxColonySize;
    }

    for(unsigned i = 0; i < startingSize; i++)
    {
        add();
    }
}

SnailColony::~SnailColony()
{
    if(nullptr != snails)
    {
        for(unsigned i = 0; i < snailsCount; i++)
            remove();

        delete[] snails;
        snails = nullptr;
    }
    pthread_mutex_destroy(&colonyMutex);
}

SnailColony::SnailColony(SnailColony&& colony)
{
    snails = colony.snails;
//    snails = move(colony.snails);
    grass = colony.grass;
}

SnailColony& SnailColony::operator= (SnailColony&& colony)
{
    snails = colony.snails;
//    snails = move(colony.snails);
    grass = colony.grass;

    return *this;
}

void SnailColony::add()
{
    if(nullptr != grass)
    {
        bool resurrected = false;
        for(unsigned i = 0; i < snailsCount; i++)
        {
            if(DEAD == getSnailState(i))
            {
                pthread_mutex_lock(&colonyMutex);
                delete snails[i];
                snails[i] = nullptr;
                Snail* snail = new Snail(static_cast<ColorPair>(i + FIRST_SNAIL_COLOR),
                                         grass,
                                         rand() % grass->getWidth(),
                                         rand() % grass->getHeight());
                snails[i] = snail;
                snails[i]->start();
                pthread_mutex_unlock(&colonyMutex);
                resurrected = true;
                break;
            }
        }

        if(!resurrected && snailsCount < maxColonySize)
        {
            Snail* snail = new Snail(static_cast<ColorPair>(snailsCount + FIRST_SNAIL_COLOR),
                                     grass,
                                     rand() % grass->getWidth(),
                                     rand() % grass->getHeight());
            pthread_mutex_lock(&colonyMutex);
            snails[snailsCount] = snail;
            snails[snailsCount++]->start();
            pthread_mutex_unlock(&colonyMutex);
        }
    }
}

void SnailColony::remove()
{
    if(snailsCount > 0)
    {
        pthread_mutex_lock(&colonyMutex);
        delete snails[--snailsCount];
        snails[snailsCount] = nullptr;
        pthread_mutex_unlock(&colonyMutex);
//        snails.back() = nullptr;
//        snails.pop_back();
    }
}

Snail** SnailColony::getSnails() const
{
    return snails;
}

unsigned SnailColony::getColonySize() const
{
    return snailsCount;
}

const Snail* SnailColony::getSnail(unsigned index) const
{
    return snails[index];
}

void SnailColony::setSnail(unsigned index, Snail* snail)
{
    snails[index] = snail;
}

SnailState SnailColony::getSnailState(unsigned index)
{
    pthread_mutex_lock(&colonyMutex);
    SnailState state = snails[index]->getState();
    pthread_mutex_unlock(&colonyMutex);
    return state;
}

void SnailColony::getSnailColorAndPosition(unsigned index, ColorPair &color, int &x, int &y)
{
    pthread_mutex_lock(&colonyMutex);
    color = snails[index]->getColor();
    snails[index]->getPos(x, y);
    pthread_mutex_unlock(&colonyMutex);
}

int SnailColony::getSnailHunger(unsigned index)
{
    pthread_mutex_lock(&colonyMutex);
    int retVal = snails[index]->getHunger();
    pthread_mutex_unlock(&colonyMutex);
    return retVal;
}

Snail* SnailColony::getSnail(unsigned index)
{
    return snails[index];
}

void SnailColony::setGrass(Grass* grass)
{
    this->grass = grass;
}


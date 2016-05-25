//
// Created by user on 11.05.16.
//

#include "../headers/SnailColony.h"

const unsigned SnailColony::maxColonySize = LAST_SNAIL_COLOR - FIRST_SNAIL_COLOR + 1;

SnailColony::SnailColony(unsigned startingSize) : snails(nullptr), grass(nullptr), snailsCount(0)
{
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
        delete[] snails;
        snails = nullptr;
    }
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
    if(nullptr != grass && snailsCount < maxColonySize)
    {
//        snails.emplace_back(static_cast<ColorPair>(snails.size() + FIRST_SNAIL_COLOR),
//                            grass,
//                            rand() % grass->getWidth(),
//                            rand() % grass->getHeight());
        Snail* snail = new Snail(static_cast<ColorPair>(snailsCount + FIRST_SNAIL_COLOR),
                                 grass,
                                 rand() % grass->getWidth(),
                                 rand() % grass->getHeight());
        snails[snailsCount] = snail;
//        snails.push_back(snail);
        snails[snailsCount++]->start();
    }
}

void SnailColony::remove()
{
    if(snailsCount > 0)
    {
        delete snails[--snailsCount];
        snails[snailsCount] = nullptr;
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

Snail* SnailColony::getSnail(unsigned index)
{
    return snails[index];
}

void SnailColony::setGrass(Grass* grass)
{
    this->grass = grass;
}

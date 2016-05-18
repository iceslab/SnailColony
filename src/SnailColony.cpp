//
// Created by user on 11.05.16.
//

#include "../headers/SnailColony.h"

const unsigned SnailColony::maxColonySize = LAST_SNAIL_COLOR - FIRST_SNAIL_COLOR + 1;

SnailColony::SnailColony(unsigned startingSize) : snails(), grass(nullptr)
{
    if(startingSize > maxColonySize)
    {
        startingSize = maxColonySize;
    }

    for(unsigned i = 0; i < startingSize; i++)
    {
        add();
    }
}

SnailColony::SnailColony(SnailColony&& colony)
{
    snails = move(colony.snails);
    grass = colony.grass;
}

SnailColony& SnailColony::operator= (SnailColony&& colony)
{
    snails = move(colony.snails);
    grass = colony.grass;

    return *this;
}

void SnailColony::add()
{
    if(nullptr != grass && snails.size() < maxColonySize)
    {
        snails.emplace_back(static_cast<ColorPair>(snails.size() + FIRST_SNAIL_COLOR),
                            grass,
                            rand() % grass->getWidth(),
                            rand() % grass->getHeight());
    }
}

void SnailColony::remove()
{
    if(snails.size() > 0)
    {
        snails.pop_back();
    }
}

const vector<Snail>& SnailColony::getSnails() const
{
    return snails;
}

unsigned SnailColony::getColonySize() const
{
    return snails.size();
}

const Snail& SnailColony::getSnail(unsigned index) const
{
    return snails[index];
}

void SnailColony::setGrass(Grass* grass)
{
    this->grass = grass;
}

//
// Created by user on 11.05.16.
//

#ifndef SNAILCOLONY_SNAILCOLONY_H
#define SNAILCOLONY_SNAILCOLONY_H

#include "../headers/Snail.h"

class SnailColony {
public:
    SnailColony(unsigned startingSize = 0);
    ~SnailColony();
    SnailColony(SnailColony&& colony);
    SnailColony& operator= (SnailColony&& colony);
    void add();
    void remove();

    Snail** getSnails() const;
    unsigned getColonySize() const;
    const Snail* getSnail(unsigned index) const;
    Snail* getSnail(unsigned index);
    void setSnail(unsigned index, Snail* snail);
    SnailState getSnailState(unsigned index);
    void getSnailColorAndPosition(unsigned index, ColorPair &color, int &x, int &y);
    int getSnailHunger(unsigned index);

    void setGrass(Grass* grass);
    static const unsigned maxColonySize;
private:


    Snail** snails;
    unsigned snailsCount;
    Grass* grass;
    pthread_mutex_t colonyMutex;

};


#endif //SNAILCOLONY_SNAILCOLONY_H

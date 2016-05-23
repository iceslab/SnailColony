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

    void setGrass(Grass* grass);
private:
    static const unsigned maxColonySize;
    Snail** snails;
    unsigned snailsCount;
    Grass* grass;

};


#endif //SNAILCOLONY_SNAILCOLONY_H

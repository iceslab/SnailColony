//
// Created by user on 11.05.16.
//

#ifndef SNAILCOLONY_SNAILCOLONY_H
#define SNAILCOLONY_SNAILCOLONY_H

#include "../headers/Snail.h"

class SnailColony {
public:
    SnailColony(unsigned startingSize = 0);
    void add();
    void remove();
private:
    vector<Snail> snails;
    static const unsigned maxColonySize;
};


#endif //SNAILCOLONY_SNAILCOLONY_H

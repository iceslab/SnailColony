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

    const vector<Snail>& getSnails() const;
    unsigned getColonySize() const;
    const Snail& getSnail(unsigned index) const;
private:
    static const unsigned maxColonySize;
    vector<Snail> snails;

};


#endif //SNAILCOLONY_SNAILCOLONY_H

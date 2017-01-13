#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H
#include "map.h"


class InteractiveMode
{
private:
    Map& cityMap;
    string intersection;

public:

    InteractiveMode(Map&);
    string getCurrentInt() const;
    void setCurrentInt(string&);
    void start();

};

#endif // INTERACTIVEMODE_H

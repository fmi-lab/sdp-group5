#ifndef INTERSECTION_H
#define INTERSECTION_H

#include<iostream>
#include<fstream>
using namespace std;

#include<string>
#include<vector>
#include<list>
#include<queue>
#include<set>

struct Street;

class Intersection
{
private:
    string name;
    int number;
    list<Street*> streets;
    bool Open;

public:

    Intersection(string,int);

    string getName() const;
    int getNumber() const;
    bool isOpen() const;
    //намиране на съседните кръстовища,които са отворени
    bool getOpenNeighbours(vector<Intersection*>&) const;

    //намиране на съседните кръстовища
    bool getNeighbours(vector<string>&) const;

    //намиране броя на отворените съседни кръстовища
    int countOpenNeighbours() const;

    //връща псевдоним на списъка с улиците, излизащи от кръстовището
    list<Street*>& getStreets();

    //добавяне на нова улица
    void addStreet(Street*);

    //изтриване на улица
    void removeStreet(Street*);

    //проверка за път до друго кръстовище
    bool path(Intersection*) const;

    //проверка за цикъл с начало това кръстовище
    bool cycle() const;

    //затваряне на кръстовището
    void close();

    //отваряне на кръстовището
    void open();

    friend class Map;
};


//улица (дължина и крайно кръстовище)
struct Street
{
    int length;
    Intersection* end;

    Street(int l,Intersection* e):length(l),end(e){}
};
#endif // INTERSECTION_H

#ifndef MAP_H
#define MAP_H

#include "intersection.h"
#include<map>
#include<cstring>
#include<cstdlib>



class Map{
private:

    map<string,Intersection*> intersections;
    int count;
    int closedInt;

    void copy(const Map&);
    void erase();
    bool eulerian(Intersection*&,Intersection*&,int&);
    Intersection* addIntersection(string);

public:

    Map();
    Map(const Map&);
    ~Map();
    Map& operator=(const Map&);

    bool read(ifstream&);
    bool print(ofstream&) const;

    bool getNeighbours(string,vector<string>&);

    //проверка за път между две кръстовиша
    bool path(string,string);

    //намира най-краткия път между две кръстовище, ако съществува
    bool getPath(string,string,vector<string>&);

    //проверка, дали от кръстовище може да се стигне до всички останали
    bool pathToAll(string);

    //проверка за цикъл от посочено кръстовище
    bool cycle(string);

    //затваряне на кръстовища
    void close(vector<string>&);

    //отваряне на кръстоища
    void open(vector<string>&);

    //намира маршрута на туристическа обиколка по всички улици,ако съществува
    bool tour(string s,list<string>& path);

    //намира всички задънени улици
    void closedStreets(vector<pair<string,string> >&);

    void closed(vector<string>&);

    string first() const;

    bool member(string) const;




};
#endif // MAP_H

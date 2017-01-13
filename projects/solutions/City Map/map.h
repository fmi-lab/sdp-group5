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

    //�������� �� ��� ����� ��� ����������
    bool path(string,string);

    //������ ���-������� ��� ����� ��� ����������, ��� ����������
    bool getPath(string,string,vector<string>&);

    //��������, ���� �� ���������� ���� �� �� ������ �� ������ ��������
    bool pathToAll(string);

    //�������� �� ����� �� �������� ����������
    bool cycle(string);

    //��������� �� ����������
    void close(vector<string>&);

    //�������� �� ���������
    void open(vector<string>&);

    //������ �������� �� ������������ �������� �� ������ �����,��� ����������
    bool tour(string s,list<string>& path);

    //������ ������ �������� �����
    void closedStreets(vector<pair<string,string> >&);

    void closed(vector<string>&);

    string first() const;

    bool member(string) const;




};
#endif // MAP_H

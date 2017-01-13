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
    //�������� �� ��������� ����������,����� �� ��������
    bool getOpenNeighbours(vector<Intersection*>&) const;

    //�������� �� ��������� ����������
    bool getNeighbours(vector<string>&) const;

    //�������� ���� �� ���������� ������� ����������
    int countOpenNeighbours() const;

    //����� ��������� �� ������� � �������, �������� �� ������������
    list<Street*>& getStreets();

    //�������� �� ���� �����
    void addStreet(Street*);

    //��������� �� �����
    void removeStreet(Street*);

    //�������� �� ��� �� ����� ����������
    bool path(Intersection*) const;

    //�������� �� ����� � ������ ���� ����������
    bool cycle() const;

    //��������� �� ������������
    void close();

    //�������� �� ������������
    void open();

    friend class Map;
};


//����� (������� � ������ ����������)
struct Street
{
    int length;
    Intersection* end;

    Street(int l,Intersection* e):length(l),end(e){}
};
#endif // INTERSECTION_H

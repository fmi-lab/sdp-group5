
#include "intersection.h"

Intersection::Intersection(string s,int n):name(s),number(n),Open(true){}

string Intersection::getName() const
{
    return name;
}

int Intersection::getNumber() const
{
    return number;
}

bool Intersection::isOpen() const
{
    return Open;
}

//намиране на списък от отворените съседни кръстовища
bool Intersection::getOpenNeighbours(vector<Intersection*>& v) const
{
    if(streets.empty())
    {
        return false;
    }

    for(list<Street*>::const_iterator it=streets.begin();it!=streets.end();++it)
    {
        if((*it)->end->isOpen()) v.push_back((*it)->end);
    }

    return true;
}

bool Intersection::getNeighbours(vector<string>& v) const
{
    if(streets.empty())
    {
        return false;
    }

    for(list<Street*>::const_iterator it=streets.begin();it!=streets.end();++it)
    {
        v.push_back((*it)->end->getName());
    }

    return true;
}

//намира броя на отворените съседни кръстовища
int Intersection::countOpenNeighbours() const
{
    int countN = 0;
    for(list<Street*>::const_iterator it=streets.begin();it!=streets.end();++it)
    {
        if((*it)->end->isOpen())
        {
            countN++;
        }
    }

    return countN;
}


list<Street*>& Intersection::getStreets()
{
    return streets;
}

void Intersection::open()
{
    Open = true;
}

void Intersection::close()
{
    Open = false;
}


void Intersection::addStreet(Street* s)
{

  streets.push_back(s);
}

void Intersection::removeStreet(Street* s)
{

    streets.remove(s);

}

//проверка за път до друго кръстовище чрез BFS
bool Intersection::path(Intersection* end) const
{

    if(!isOpen() || !end->isOpen())
    {
        return false;
    }

    queue<Intersection*> q;

    //за обходените върхове
    set<int> history;

    bool found = false;

    q.push((Intersection*)this);
    history.insert(number);

    while(!q.empty())
    {

        Intersection* p =q.front();
        q.pop();

        for(list<Street*>::iterator it=p->streets.begin();it!=p->streets.end();++it)
        {
            //стигнали сме до желаното кръстовище
            if(((*it)->end) == end)
            {
                return true;
            }
            else
            if(history.find((*it)->end->number) != history.end() && (*it)->end->isOpen())
            {
                //добавяме в опашката за обхождане
                q.push((*it)->end);
                history.insert((*it)->end->number);
            }


        }
    }
    //обхождането е завършило без да сме стигнали до търсеното кръстовище
    return false;
}


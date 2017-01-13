#include "map.h"

const int Max = 1000000;

void Map::copy(const Map& m)
{

    count = 0;
    closedInt = m.closedInt;

    for(map<string,Intersection*>::const_iterator it = m.intersections.begin();it != m.intersections.end();++it)
    {
        //добавя се връх
        Intersection *p = addIntersection(it->first);

        if(!it->second->isOpen())
        {
            p-> close();
        }

        //добавят се улиците, излизащи от върха, и кръстовищата, до които водят
        list<Street*> l = it->second->getStreets();
        for(list<Street*>::iterator i = l.begin();i!=l.end();++i)
        {
            Street* s = (*i);
            Intersection *n = addIntersection(s->end->getName());
            p->addStreet(new Street(s->length,n));
        }
    }


}


void Map::erase()
{

    for(map<string,Intersection*>::iterator it = intersections.begin();it != intersections.end();++it)
    {

        list<Street*> l = it->second->getStreets();
        //първо се изтриват улиците,излизащи от кръстовище
        for(list<Street*>::iterator i = l.begin();i!=l.end();++i)
        {
            delete (*i);
        }

        //и самото кръстовище
        delete it->second;
    }
}



Map::Map():count(0),closedInt(0){}

Map::Map(const Map& m):count(m.count)
{
    copy(m);
}

Map& Map::operator=(const Map& m)
{
    if(this!=&m)
    {
        erase();
        copy(m);
    }

    return *this;
}

Map::~Map()
{
    erase();
}

//връща указател към кръстовището, ако вече е добавено или добавя ново
Intersection* Map::addIntersection(string name)
{
    if(intersections[name])
        return intersections[name];

    Intersection *p= new Intersection(name,count);

    intersections[name] = p;
    count++;

    return p;

}

bool Map::getNeighbours(string s,vector<string>& v)
{
    Intersection* p = intersections[s];
    return p->getNeighbours(v);
}

bool Map::path(string s,string e)
{
    Intersection *start = intersections[s],*end = intersections[e];
    if(!start || !end)
    {
        return false;
    }
    return start->path(end);
}

//необходима за намиране на най-кратък път между две кръстовища
struct DiikstraEl
{
    int length;
    Intersection* parent;

    DiikstraEl(int l = Max,Intersection* p = NULL):length(l),parent(p){}
};


//намиране на най-кратък път чрез алгоритъма на Диикстра
bool Map::getPath(string s,string e,vector<string>& path)
{
    Intersection *start = intersections[s],*end = intersections[e];

    if(!start || !end)
    {
        return false;
    }

    if(!start->isOpen() || !end->isOpen())
    {
        return false;
    }

    vector<DiikstraEl> v;
    v.resize(count);

    int num = start->number;
    v[num].length = 0;

    queue<Intersection*> q;
    q.push(start);

    //BFS
    while(!q.empty())
    {

        Intersection* p =q.front();
        q.pop();

        list<Street*> l = p->getStreets();

        for(list<Street*>::iterator it=l.begin();it!=l.end();++it)
        {
           if((*it)->end->isOpen())
           {
                if(v[((*it)->end->number)].length == Max)
                {
                    q.push((*it)->end);
                }
                if(v[((*it)->end->number)].length >= v[p->number].length + (*it)->length)
                {
                    v[((*it)->end->number)].length = v[p->number].length + (*it)->length;
                    v[((*it)->end->number)].parent = p;
                }
           }

        }
    }



    int n = v[end->number].length;
    if(n == Max)
    {
        return false;
    }

    Intersection *par = end;
    vector<string> path2;

    //възстановяване на пътя
    while(par!=NULL)
    {
        path2.push_back(par->getName());
        par = v[par->number].parent;
    }

    while(!path2.empty())
    {
        path.push_back(path2.back());
        path2.pop_back();
    }
    return true;

}

void Map::close(vector<string>& l)
{

    for(vector<string>::iterator it = l.begin();it != l.end();++it)
    {
        if(member((*it)))
        {
            Intersection *p = intersections[*it];
            if(p->isOpen())
            {
                closedInt++;
            }

            p->close();
        }

    }
}


void Map::open(vector<string>& l)
{
    for(vector<string>::iterator it = l.begin();it != l.end();++it)
    {
        if(member((*it)))
        {
            Intersection *p = intersections[*it];
            if(!p->isOpen())
            {
                closedInt--;
            }

            p->open();
        }
    }
}

bool Map::cycle(string s)
{
    if(!member(s)) return false;

    vector<string> v;
    return getPath(s,s,v);
}

//записване на кръстовищата във файл по азбучен ред
bool Map::print(ofstream& f) const
{
    for(map<string,Intersection*>::const_iterator it = intersections.begin();it!=intersections.end();++it)
    {
        f<<it->first<<"->";
        list<Street*> l = (*it).second->getStreets();
        for(list<Street*>::iterator i = l.begin();i != l.end();++i)
        {
            f<<((*i)->end->getName());
            if(!(*i)->end->isOpen())
            {
                f<<"(closed)";
            }
            f<<", ";
        }
        f<<endl;
    }
}


//обхождат се всички достъпни от това кръстовище кръстовища с BFS и проверка дали са всички
bool Map::pathToAll(string s)
{
    if(!intersections[s] || !intersections[s]->isOpen())
    {
        return false;
    }

    queue<Intersection*> q;
    int length = 1;
    vector<int> history;
    history.resize(count);
    history[intersections[s]->getNumber()] = 1;
    q.push(intersections[s]);

    while(!q.empty())
    {

        Intersection* p = q.front();
        q.pop();


        list<Street*> l = p->getStreets();

        for(list<Street*>::iterator it=l.begin();it!=l.end();++it)
        {

            if(history[(*it)->end->getNumber()] == 0 && (*it)->end->isOpen())
            {

                history[(*it)->end->getNumber()]=1;
                q.push((*it)->end);
                length++;
            }

        }
    }

    if (count-closedInt== length)
    {
        return true;
    }
    return false;

}

//намиране на начално и крайно кръстовище на ойлеров път , ако е възможно
bool Map::eulerian(Intersection*& start,Intersection*& end,int& countSt)
{
    vector<int> v;
    countSt = 0;

    v.resize(count);
    start = NULL;
    end = NULL;

    //намиране на броя влизащи улици във всяко кръстовище
    for(map<string,Intersection*>::iterator it = intersections.begin();it!=intersections.end();++it)
    {
        //взимане на отворените съседни кръстовища на текущото кръстовище
        if((*it).second->isOpen())
        {

            vector<Intersection*> n;
            (*it).second->getOpenNeighbours(n);

            countSt+= ((*it).second->countOpenNeighbours());

            for(int i=0;i<n.size();i++)
            {
                v[n[i]->getNumber()]++;
            }

        }

    }

    //проверка за съществуване на ойлеров път или цикъл, ако графът е свързан
    for(map<string,Intersection*>::iterator it = intersections.begin();it!=intersections.end();++it)
    {
        //брой влизащи улици
        int out = (*it).second->countOpenNeighbours();
        //брой излизащи улици
        int in = v[(*it).second->number];

        if((*it).second->isOpen() && in != out)
        {
            if(out == 1+in)
            {
                if(start != NULL)
                {
                    return false;
                }
                else
                {
                    start = (*it).second;
                }
            }
            else
            if(out + 1 == in)
            {
                if(end != NULL)
                {
                    return false;
                }
                else
                {
                    end = (*it).second;
                }
            }
            else
            {
               return false;
            }
        }



    }

        if((start == NULL && end != NULL) || (start!=NULL && end==NULL))
        {
            return false;
        }

        return true;

}

//намиране на туристическа обиколка на всички улици,ако е възможно(ойлеров цикъл или път)
bool Map::tour(string s,list<string>& path)
{
    if(!member(s)) return false;

    Intersection* start1 = intersections[s];
    Intersection* start = NULL,*end = NULL;

    int countS = 0;
    if(!eulerian(start,end,countS))
    {
        return false;
    }

    if(start == NULL)
    {
        start=start1;
        end=start1;
    }
    else
    if(start != start1)
    {
        return false;
    }

    //обходени върхове с необходени ребра
    vector<list<string>::iterator> history;

    //обхойдане на копие на картата и унищожаване на обходените улици
    Map m=*this;

    start = m.intersections[start->getName()];
    end = m.intersections[end->getName()];

    Intersection *p = start;

    path.push_back(p->getName());
    list<string>::iterator pathIt=path.begin();
    do
    {

        bool found = false;

        list<Street*> l = p->getStreets();

        //намиране на необходена улица от текущия връх
        for(list<Street*>::iterator it = l.begin();!found && it != l.end()&&l.size()>0;++it)
        {

            if((*it)->end->isOpen())
            {
                found = true;
                countS--;
                Intersection* newI = (*it)->end;
                p->streets.remove(*it);

                if(p->streets.size()!=0)
                {
                    history.push_back(pathIt);
                }

                p=newI;

                pathIt = path.insert(pathIt,p->getName());

            }
        }



        //ако стигнем до края, но не всички улици са обходени
        if( p == end && countS > 0 )
        {

           bool found2 = false;

           while(!found2 && !history.empty())
           {
               list<string>::iterator pos= history.back();
               history.pop_back();
               Intersection* q = m.intersections[(*pos)];

               list<Street*> l = q->getStreets();
               for(list<Street*>::iterator it = l.begin();(!found2 && it != l.end() && l.size()>0);++it)
               {

                    if((*it)->end->isOpen())
                    {

                        found2 = true;
                        countS--;
                        p = (*it)->end;
                        end = q;
                        q->streets.remove(*it);
                        pathIt = pos;
                        pathIt = path.insert(pathIt,p->getName());

                        history.push_back(pathIt);

                       if(q->streets.size()>0)
                       {
                           history.push_back(pos);
                       }

                    }

               }


           }

           if(!found2)
           {
               return false;
           }

        }


    }
    while(p != end);



    if(countS==0) return true;

    return false;

}

//намиране на задънените улици
void Map::closedStreets(vector<pair<string,string> >& v)
{
    for(map<string,Intersection*>::iterator it = intersections.begin();it!=intersections.end();++it)
    {
        list<Street*> l = (*it).second->getStreets();
        for(list<Street*>::iterator i = l.begin();i!=l.end();++i)
        {
            if((*i)->end->streets.empty())
            {
                v.push_back(pair<string,string>((*it).second->getName(),(*i)->end->getName()));
            }
        }
    }

}

//прочитане на картата от входен поток
bool Map::read(ifstream& f)
{

    string s;
    if(!f) return false;
    while(getline(f,s))
    {

        char *t;
        const char *str = s.c_str();
        t = strtok((char*)str," ");

        string a(t);
        Intersection *p= addIntersection(a);

        t = strtok(NULL," ");
        while(t!=NULL)
        {
            string neighbour(t);
            t = strtok(NULL," ");
            int length = atoi(t);
            p->addStreet(new Street(length,addIntersection(neighbour)));
            t = strtok(NULL," ");
        }

    }
    return true;
}

string Map::first() const
{
    return (*intersections.begin()).first;
}

void Map::closed(vector<string>& v)
{
    for(map<string,Intersection*>::iterator it = intersections.begin();it!=intersections.end();++it)
    {
        if(!(*it).second->isOpen())
        {
            v.push_back((*it).second->getName());
        }
    }
}

bool Map::member(string s) const
{
    return intersections.find(s) != intersections.end();
}



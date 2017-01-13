

#include "multiList.h"


 void MultiList::read(ifstream& f)
{

    int n;
    string s;
    f>>n;
    getline(f,s);
    while(getline(f,s))
    {
        char *t,*t2;
        const char *str = s.c_str();
        t = strtok((char*)str," ");
        t2 = strtok(NULL," ");

        string a(t);
        string type(t2);
        ListEl<Data> *p;
        if(a=="queue") {p=new Queue<Data>(type);}
        else
        if(a=="stack") {p=new Stack<Data>(type);}
        else
        if(a=="list")   {p=new List<Data>(type);}
        else
        if(a=="binTree")   {p=new BinTree<Data>(type);}


        t = strtok(NULL," ");
        while(t!=NULL)
        {

            if(type=="int")
            {
                int x = atoi(t);
                p->add(x);
            }
            else
            if(type=="bool")
            {
                bool x = !(strcmp(t,"true"));
                p->add(x);
            }
            else
            if(type=="double")
            {
                double x = atof(t);
                p->add(x);
            }

            t = strtok(NULL," ");
        }
        hList.push_back(p);
        size++;

    }

}




bool MultiList::member(int x)
{
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType() == "int")
        {
            Data y(x);
            if((*it)->member(y)) return true;
        }
    }

    return false;

}

bool MultiList::member(bool x)
{
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType() == "bool")
        {
            Data y(x);
            if((*it)->member(y)) return true;
        }
    }

    return false;

}

bool MultiList::member(double x)
{
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType() == "double")
        {
            Data y(x);
            if((*it)->member(y)) return true;
        }
    }

    return false;

}

void MultiList::addBalanced(int x)
{

    if(hList.empty())
    {
        ListEl<Data> *p = new List<Data>("int");
        hList.push_back(p);

    }

    typename list<ListEl<Data>*>::iterator minIt = hList.begin();
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="int" && ((*minIt)->getDataType() != "ïnt" || (*it)->getSize()<(*minIt)->getSize()))
            minIt=it;
    }

    if((*minIt)->getDataType()=="int")
        (*minIt)->add(x);

}

void MultiList::addBalanced(double x)
{
    if(hList.empty())
    {
        ListEl<Data> *p = new List<Data>("double");
        hList.push_back(p);

    }

    typename list<ListEl<Data>*>::iterator minIt = hList.begin();
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="double" && ((*minIt)->getDataType() != "double" || (*it)->getSize()<(*minIt)->getSize()))
            minIt=it;
    }

    if((*minIt)->getDataType()=="double")
        (*minIt)->add(x);

}

void MultiList::addBalanced(bool x)
{
    if(hList.empty())
    {
        ListEl<Data> *p = new List<Data>("bool");
        hList.push_back(p);

    }

    typename list<ListEl<Data>*>::iterator minIt = hList.begin();
    for(typename list<ListEl<Data>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="bool" && ((*minIt)->getDataType() != "bool" || (*it)->getSize()<(*minIt)->getSize()))
            minIt=it;
    }

    if((*minIt)->getDataType()=="bool")
        (*minIt)->add(x);

}




bool MultiList::searchCond(ConditionI f) const
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="int")
        {
            if((*it)->searchCond(f)) return true;
        }

    }
    return false;
}
bool MultiList::searchCond(ConditionD f) const
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="double")
        {
            if((*it)->searchCond(f)) return true;
        }


    }
    return false;
}

bool MultiList::searchCond(ConditionB f) const
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="bool")
        {
            if((*it)->searchCond(f)) return true;
        }

    }
    return false;
}

void MultiList::filter(ConditionI f)
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="int")
        {
            (*it)->filter(f);
        }

    }

}


void MultiList::filter(ConditionD f)
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="double")
        {
            (*it)->filter(f);
        }


    }

}

void MultiList::filter(ConditionB f)
{
    for(typename list<ListEl<Data>*>::const_iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getDataType()=="bool")
        {
            (*it)->filter(f);
        }


    }

}


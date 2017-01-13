#ifndef HLIST_CPP
#define HLIST_CPP



#include<fstream>
#include<cstdlib>


#include<list>
#include<vector>

#include "queue.cpp"
#include "stack.cpp"
#include "list.cpp"
#include "tree.cpp"
#include<string>
#include<string.h>
#include<stdio.h>

template<typename T>
class SortedIterator;

template<typename T>
class Iterator;

template<typename T>
class HList{

protected:
    list<ListEl<T>*> hList;
    int size;

    void copy(const HList&);

    void erase();

public:

    HList():size(0){}
    HList(const HList&);

    HList& operator=(const HList&);

    ~HList();

    void readInt(ifstream&);

    bool member(const T&);

    void addBalanced(const T&);

    bool print(ofstream&);

    using Condition = bool (*)(T const&);

    bool searchCond(Condition) const;

    void filter(Condition);

    void sort();

    int getSize() const;

    SortedIterator<T> sortedIt() const;

    Iterator<T> iterator(bool mode) const;

    SortedIterator<T> searchSort(const T&);

    typename list<ListEl<T>*>::iterator begin();

    typename list<ListEl<T>*>::iterator end();

    void addStack(Stack<T>&);
    void addQueue(Queue<T>&);
    void addList(List<T>&);
    void addTree(BinTree<T>&);
};


template<typename T>
void HList<T>::copy(const HList& l)
{
    size = l.size;
    for(typename list<ListEl<T>*>::const_iterator it = l.hList.begin();it!=l.hList.end();++it)
    hList.push_back((*it)->clone());
}


template<typename T>
void HList<T>::erase()
{
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
        delete *it;

}


template<typename T>
HList<T>::HList(const HList& l)
{
    copy(l);
}

template<typename T>
HList<T>& HList<T>::operator=(const HList<T>& l)
{
    if(this!=&l)
    {
        erase();
        copy(l);
    }

    return *this;
}


template<typename T>
HList<T>::~HList()
{
    erase();
}

template<typename T>
void HList<T>::readInt(ifstream& f)
{

    int n;
    string s;
    f>>n;
    getline(f,s);
    while(getline(f,s))
    {

        char *t;
        const char *str = s.c_str();
        t = strtok((char*)str," ");

        string a(t);
        ListEl<T> *p;
        if(a=="queue") p=new Queue<T>();
        else
        if(a=="stack") p=new Stack<T>();
        else
        if(a=="list")   p=new List<T>();
        else
        if(a=="binTree")   p=new BinTree<T>();


        t = strtok(NULL," ");
        while(t!=NULL)
        {
            int x = atoi(t);
            p->add(x);
            t = strtok(NULL," ");
        }
        hList.push_back(p);
        size++;

    }

}



template<typename T>
bool HList<T>::member(const T& x)
{
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
        if((*it)->member(x)) return true;

    return false;

}

template<typename T>
void HList<T>::addBalanced(const T& x)
{
    if(hList.empty())
    {
        ListEl<T> *p = new List<T>();
        hList.push_back(p);

    }

    typename list<ListEl<T>*>::iterator minIt = hList.begin();
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->getSize()<(*minIt)->getSize()) minIt=it;
    }

    (*minIt)->add(x);

}


template<typename T>
bool HList<T>::print(ofstream& f)
{
    if(!f) return false;
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
    {

       (*it)->print(f);
       f<<endl;

    }

    return true;

}


template<typename T>
bool HList<T>::searchCond(Condition f) const
{
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        if((*it)->searchCond(f)) return true;
    }
    return false;
}


template<typename T>
void HList<T>::filter(Condition c)
{
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
    {
        (*it)->filter(c);
    }
}


template<typename T>
void HList<T>::sort()
{
    for(typename list<ListEl<T>*>::iterator it = hList.begin();it!=hList.end();++it)
        (*it)->sort();
}

template<typename T>
typename list<ListEl<T>*>::iterator HList<T>::begin()
{
    return hList.begin();
}

template<typename T>
typename list<ListEl<T>*>::iterator HList<T>::end()
{
    return hList.end();
}


template<typename T>
int HList<T>::getSize() const
{
    return size;
}


template<typename T>
SortedIterator<T> HList<T>::sortedIt() const
{
    return SortedIterator<T>(*this);
}

template<typename T>
Iterator<T> HList<T>::iterator(bool mode) const
{
    return Iterator<T>(*this,mode);
}


template<typename T>
SortedIterator<T> HList<T>::searchSort(const T& x)
{
    sort();
    SortedIterator<T> it=sortedIt();
    for(;it;++it)
    {
        if(*it==x) return it;
    }

    return it;
}

template<typename T>
void HList<T>::addStack(Stack<T>& x)
{
    ListEl<T> *p = new Stack<T>(x);
    hList.push_back(p);
    size++;
}

template<typename T>
void HList<T>::addQueue(Queue<T>& x)
{
    ListEl<T> *p = new Queue<T>(x);
    hList.push_back(p);
    size++;
}

template<typename T>
void HList<T>::addList(List<T>& x)
{
    ListEl<T> *p = new List<T>(x);
    hList.push_back(p);
    size++;
}

template<typename T>
void HList<T>::addTree(BinTree<T>& x)
{
    ListEl<T> *p = new BinTree<T>(x);
    hList.push_back(p);
    size++;
}




template<typename T>
class SortedIterator
{
private:
    Element<T>* it;
    vector<ElIterator<T>*> v;

    int count;
    int size;


    void copy(const SortedIterator& c)
    {
        it = c.it;
        count = c.count;
        size = c.size;
        v.resize(size);

        for(int i=0;i<size;i++)
        {
            if(c.v[i]->getType()=='q')
                v[i]=new QIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='s')
                v[i]=new SIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='l')
                v[i]=new LIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='t')
                v[i]=new TIterator<T>(*c.v[i]);
        }
    }

    void erase()
    {
        for(int i=0;i<size;i++)

            if(v[i]) delete v[i];
    }


public:

    SortedIterator(HList<T>& h):size(h.getSize())
    {

        v.resize(size);
        int j = 0;
        int minI = 0;

        for(typename list<ListEl<T>*>::iterator i = h.begin();i!=h.end();++i)
        {
            if((*i)->getType()=="queue")
                v[j]=new QIterator<T>((*i)->begin());
            else
            if((*i)->getType()=="stack")
                v[j]=new SIterator<T>((*i)->begin());
            else
            if((*i)->getType()=="list")
                v[j]=new LIterator<T>((*i)->begin());
            else
                v[j]=new TIterator<T>((*i)->begin());


            if(*(*v[j])<*(*v[minI]))
            {
                minI = j;
            }
            j++;

        }
        it = v[minI]->getElement();
        count = minI;
    }

    SortedIterator(const SortedIterator& i)
    {
        copy(i);
    }

    SortedIterator& operator=(const SortedIterator& i)
    {
        if(&i!=this)
        {
            erase();
            copy(i);
        }

        return *this;
    }


    SortedIterator& operator++()
    {

       if(v[count])
        v[count]->next();

       int minI = 0;

       for(int i = 1;i<size;i++)
       {

           if(!(*v[minI]) || ((*v[i]) && *(*v[i])<*(*v[minI])))
           {
               minI = i;
           }

       }

       it = v[minI]->getElement();
       count = minI;

       return *this;
    }

    SortedIterator& operator++(int i)
    {
        SortedIterator c(*this);
        ++(*this);
        return c;

    }

    T& operator*() const
    {
        return it->data;
    }

    operator bool()
    {
        return it!=NULL;
    }

    bool operator!()
    {
        return it==NULL;
    }

};




template<typename T>
class Iterator
{
private:
    Element<T>* it;

    vector<ElIterator<T>* > v;

    int count;
    int size;
    bool mode;

    void copy(const Iterator& c)
    {
        it = c.it;
        count = c.count;
        size = c.size;
        mode = c.mode;
        v.resize(size);

        for(int i=0;i<size;i++)
        {

            if(c.v[i]->getType()=='q')
                v[i]=new QIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='s')
                v[i]=new SIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='l')
                v[i]=new LIterator<T>(*c.v[i]);

            if(c.v[i]->getType()=='t')
                v[i]=new TIterator<T>(*c.v[i]);


        }
    }

    void erase()
    {
        for(int i=0;i<size;i++)
        {

            delete v[i];
        }
    }


public:

    Iterator(HList<T>& h,bool _mode = false):size(h.getSize()),mode(_mode),count(0)
    {

        v.resize(size);
        int j =0;

        for(typename list<ListEl<T>*>::iterator i = h.begin();i!=h.end();++i)
        {
            if((*i)->getType()=="queue")
                v[j]=new QIterator<T>((*i)->begin());
            else
            if((*i)->getType()=="stack")
                v[j]=new SIterator<T>((*i)->begin());
            else
            if((*i)->getType()=="list")
                v[j]=new LIterator<T>((*i)->begin());
            else
                v[j]=new TIterator<T>((*i)->begin());

                j++;

        }

        it = v[0]->getElement();

    }

    Iterator(const Iterator& i)
    {
        copy(i);
    }

    Iterator& operator=(const Iterator& i)
    {
        if(&i!=this)
        {
            erase();
            copy(i);
        }

        return *this;
    }


    Iterator& operator++()
    {

        if(v[count])
        v[count]->next();
        it = v[count]->getElement();


       if(mode)
       {
           count = (count + 1)%size;
           it = v[count]->getElement();
       }

       int i = 0;
       while(it == NULL && i<size)
       {
           count = (count + 1)%size;
           it=v[count]->getElement();
           i++;
       }


       return *this;
    }

    Iterator operator++(int i)
    {
        Iterator c(*this);
        ++(*this);
        return c;

    }

    T& operator*() const
    {
        return it->data;
    }

    operator bool()
    {
        return it!=NULL;
    }

    bool operator!()
    {
        return it==NULL;
    }

};






#endif // HLIST_CPP


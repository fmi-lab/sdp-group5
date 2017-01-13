#ifndef DOUBLELIST_CPP
#define DOUBLELIST_CPP

#include "listEl.cpp"


template<typename T>
bool Comp(const T& x,const T& y)
{
    return x<=y;
}

template<typename T>
bool Comp2(const T& x,const T& y)
{
    return y<=x;
}



template<typename T>
class ElIterator;


template<typename T>
class DoubleList:public ListEl<T>
{
protected:
    Element<T>* front;
    Element<T>* end;
    int size;
    string dataType;

    void copy(const DoubleList&);
    void erase();
    void addAt(const T&,bool);
    T getAt(bool);
    void removeEl(Element<T>* p);

    using Compare = bool(*)(const T&,const T&);

    Element<T>* mSort(Element<T>*,int,Compare = &Comp);
    Element<T>* Merge(Element<T>*,int,Element<T>*,int,Compare);



public:

    DoubleList(string t = " "):front(NULL),end(NULL),size(0),dataType(t){}
    DoubleList(const DoubleList& l)
    {
        copy(l);
    }
    virtual ~DoubleList()
    {
        erase();
    }
    DoubleList& operator=(const DoubleList& l)
    {
        if(this!=&l)
        {
            erase();
            copy(l);
        }

        return *this;
    }

    bool empty() const
    {
        return front==NULL;
    }

    int getSize() const
    {
        return size;
    }

    string getDataType() const
    {
        return dataType;
    }

    bool member(T const&) const;

    using Condition = bool (*)(T const&);
    using ConditionI = bool (*)(int);
    using ConditionD = bool (*)(double);
    using ConditionB = bool (*)(bool);

    bool searchCond(Condition) const;
    bool searchCond(ConditionB) const;
    bool searchCond(ConditionI) const;
    bool searchCond(ConditionD) const;
    void filter(Condition);
    void filter(ConditionI);
    void filter(ConditionB);
    void filter(ConditionD);

    void sort();

    virtual void add(const T&) = 0;
    virtual T get() = 0;
    virtual void print(ofstream&) const = 0;
    virtual Element<T>* begin() const = 0;
    virtual string getType() const = 0;


};

template<typename T>
void DoubleList<T>::copy(const DoubleList<T>& l)
{
    size = l.size;
    dataType = l.dataType;
    if(l.empty())
    {
        front = end = NULL;
    }
    else
    {
        Element<T>* p = l.front;
        front = new Element<T>(p->data);
        Element<T>* q = front;

        while(p->next!=NULL)
        {
            q->next=new Element<T>(p->next->data);
            q->next->prev = q;
            q=q->next;
            p=p->next;
        }
        end = q;
    }
}


template<typename T>
void DoubleList<T>::erase()
{
    while(front!=NULL)
    {
        Element<T>* p = front->next;
        delete front;
        front = p;
    }
    end=NULL;
}

template<typename T>
void DoubleList<T>::addAt(const T& x,bool fr)
{
    Element<T>* p =new Element<T>(x);
    if(empty())
        front = end = p;
    else
    {
        if(fr)
        {
            front->prev = p;
            p->next = front;
            front = p;
        }
        else
        {
            end->next = p;
            p->prev = end;
            end = p;
        }

    }
    size++;
}


template<typename T>
T DoubleList<T>::getAt(bool fr)
{
    if(empty()) return T();
    T x ;
    if(fr)
    {

        x= front->data;
        if(front->next!=NULL)
            front->next->prev = NULL;
        else
            end=NULL;
        Element<T>* p = front->next;
        delete front;
        front = p;
    }
    else
    {
        x = end->data;
        if(end->prev!=NULL)
            end->prev->next = NULL;
        else
            front=NULL;
        Element<T>* p = end->prev;
        delete end;
        end = p;
    }
    size--;
    return x;
}

template<typename T>
void DoubleList<T>::removeEl(Element<T>* p)
{
    if(p==NULL) return;
    if(p->prev!=NULL)
        p->prev->next = p->next;

    if(p->next!= NULL)
        p->next->prev = p->prev;

    if(front == p) front = p->next;
    if(end == p) end = p->prev;

    delete p;
}


template<typename T>
Element<T>* DoubleList<T>::mSort(Element<T>* start,int length,Compare f)
{

    if(length == 1) return start;
    Element<T>* mid = start;

    for(int i = 0;i<length/2;i++)
        mid=mid->next;

    mid->prev->next = NULL;
    mid->prev=NULL;

    return Merge(mSort(start,length/2,f),length/2,mSort(mid,length/2+length%2,f),length/2+length%2,f);
}


template<typename T>
Element<T>* DoubleList<T>::Merge(Element<T>* start1,int l1,Element<T>* start2,int l2,Compare f)
{
    if(start1==NULL||start2==NULL) return NULL;

    Element<T>* start=NULL;
    Element<T>* p=NULL;

    int i1 = 0,i2 = 0;

    if(f(start1->data,start2->data))
    {
        start = start1;
        start1 = start1->next;
        i1++;
    }
    else
    {
        start = start2;
        start2 = start2->next;
        i2++;
    }
    p = start;

    while(i1<l1&&i2<l2)
    {
        if(f(start1->data,start2->data))
        {
            p->next = start1;
            start1->prev = p;
            start1=start1->next;
            i1++;
        }
        else
        {
            p->next = start2;
            start2->prev = p;
            start2=start2->next;
            i2++;
        }

        p=p->next;
    }

    while(i1<l1)
    {
        p->next=start1;
        start1->prev = p;
        start1=start1->next;
        p=p->next;
        i1++;
    }

    while(i2<l2)
    {
        p->next = start2;
        start2->prev = p;
        start2=start2->next;
        p=p->next;
        i2++;
    }


     /*Element<T>* q = start;
     int i=0;
     while(q!=NULL)
     {
         q=q->next;
         i++;

     }*/

    return start;


}

template <typename T>
bool DoubleList<T>::member(T const& x) const
{
    Element<T>* p = front;
    while(p!=NULL)
    {
        if(p->data == x) return true;
        p=p->next;
    }

    return false;
}


template <typename T>
bool DoubleList<T>::searchCond(Condition f) const
{
    Element<T>* p = front;
    while(p!=NULL)
    {
        if(f(p->data)) return true;
        p=p->next;
    }

    return false;
}


template <typename T>
bool DoubleList<T>::searchCond(ConditionB f) const
{
    Element<T>* p = front;
    while(p!=NULL)
    {
        if(f(p->data)) return true;
        p=p->next;
    }

    return false;
}

template <typename T>
bool DoubleList<T>::searchCond(ConditionI f) const
{
    Element<T>* p = front;
    while(p!=NULL)
    {
        if(f(p->data)) return true;
        p=p->next;
    }

    return false;
}

template <typename T>
bool DoubleList<T>::searchCond(ConditionD f) const
{
    Element<T>* p = front;
    while(p!=NULL)
    {
        if(f(p->data)) return true;
        p=p->next;
    }

    return false;
}

template <typename T>
void DoubleList<T>::filter(Condition f)
{

    Element<T>* p = front;
    while(p!=NULL)
    {
        Element<T>* q = p->next;
        if(f(p->data))
        {
            removeEl(p);
        }
        p=q;
    }
}

template <typename T>
void DoubleList<T>::filter(ConditionI f)
{

    Element<T>* p = front;
    while(p!=NULL)
    {
        Element<T>* q = p->next;
        if(f(p->data))
        {
            removeEl(p);
        }
        p=q;
    }
}


template <typename T>
void DoubleList<T>::filter(ConditionB f)
{

    Element<T>* p = front;
    while(p!=NULL)
    {
        Element<T>* q = p->next;
        if(f(p->data))
        {
            removeEl(p);
        }
        p=q;
    }
}


template <typename T>
void DoubleList<T>::filter(ConditionD f)
{

    Element<T>* p = front;
    while(p!=NULL)
    {
        Element<T>* q = p->next;
        if(f(p->data))
        {
            removeEl(p);
        }
        p=q;
    }
}

template <typename T>
void DoubleList<T>::sort()
{

    if(front == NULL) return;
    front = mSort(front,size);

    Element<T>* p = front;
    while(p->next!=NULL)
        p=p->next;
    end = p;
}








#endif // DOUBLELIST_CPP

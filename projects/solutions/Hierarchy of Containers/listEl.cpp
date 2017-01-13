#ifndef LISTEL_CPP
#define LISTEL_CPP

#include<iostream>
#include<vector>

using namespace std;

template <typename T>
struct Element
{
    T data;
    Element<T>* next;
    Element<T>* prev;
    Element(const T& d,Element<T>* p =NULL,Element<T>* n =NULL):data(d),prev(p),next(n){}
};



template<typename T>
class ListEl
{

   public:

    virtual bool empty() const = 0;

    virtual int getSize() const = 0;
    virtual string getType() const = 0;
    virtual string getDataType() const = 0;
    virtual Element<T>* begin() const= 0;

    virtual bool member(T const&) const = 0;

    virtual void add(const T&) = 0;
    virtual T get() = 0;

    using Condition = bool (*)(T const&);
    using ConditionI = bool (*)(int);
    using ConditionD = bool (*)(double);
    using ConditionB = bool (*)(bool);

    virtual bool searchCond(Condition) const = 0;
    virtual bool searchCond(ConditionI) const = 0;
    virtual bool searchCond(ConditionD) const = 0;
    virtual bool searchCond(ConditionB) const = 0;

    virtual void filter(Condition) = 0;
    virtual void filter(ConditionI) = 0;
    virtual void filter(ConditionD) = 0;
    virtual void filter(ConditionB) = 0;

    virtual void sort() = 0;

    virtual void print(ofstream&) const = 0;


};


template<typename T>
class QIterator;

template<typename T>
class SIterator;

template<typename T>
class LIterator;

template<typename T>
class TIterator;

template<typename T>
class ElIterator
{
    protected:
        Element<T>* it;
        char type;

    public:

        ElIterator(Element<T>* e = NULL,char t = ' '): it(e),type(t){}

        operator bool() const
        {
            return it!=NULL;
        }

        bool operator!() const
        {
            return it==NULL;
        }


        virtual void next() = 0;

        T& operator*()
        {
            if(it!=NULL)
            return it->data;
        }

        Element<T>* getElement()
        {
            return it;
        }

        char getType() const
        {
            return type;
        }


};



#endif

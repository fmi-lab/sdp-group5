#ifndef STACK_CPP
#define STACK_CPP

#include "doubleList.cpp"


template<typename T>
class Stack:public DoubleList<T>
{
public:

    typedef DoubleList<T> DL;
    Stack(string t = " "):DoubleList<T>(t){}

    void add(const T& x)
    {

        DL::addAt(x,false);

    }

    T get()
    {
        return DL::getAt(false);
    }


    Element<T>* begin() const
    {
        return DL::end;
    }

    string getType() const
    {
        return "stack";
    }

    void sort()
    {

        if(DL::front == NULL) return;
        DL::front = DL::mSort(DL::front,DL::size,&Comp2);

        Element<T>* p = DL::front;
        while(p->next!=NULL)
            p=p->next;
        DL::end = p;
    }

    void print(ofstream& o) const
    {
        o<<getType()<<" ";
        o<<DL::getDataType()<<" ";

        SIterator<T> i(begin());
        while(i)
        {
            o<<(*i)<<" ";
            ++i;
        }

    }
};

template<typename T>
class SIterator:public ElIterator<T>
{

    public:

        typedef ElIterator<T> P;

	    SIterator(Element<T>* e = NULL): P::ElIterator(e,'s'){}

	    void next()
	    {
	        if(P::it!=NULL)
                P::it=P::it->prev;
	    }

        SIterator& operator++()
        {
            next();
            return *this;
        }

        SIterator operator++(int i)
        {
            SIterator copy(P::it);
            next();
            return copy;
        }



};


#endif

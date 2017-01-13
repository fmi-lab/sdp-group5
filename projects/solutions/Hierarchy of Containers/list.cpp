#ifndef LIST_CPP
#define LIST_CPP

#include "doubleList.cpp"





template<typename T>
class List:public DoubleList<T>
{
public:

    typedef DoubleList<T> DL;

    List(string t = " "):DoubleList<T>(t){}

    void add(const T& x)
    {
        DL::addAt(x,true);
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
        return "list";
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
        LIterator<T> i(begin());
        while(i)
        {
            o<<(*i)<<" ";
            ++i;
        }

    }

};


template<typename T>
class LIterator:public ElIterator<T>
{

    public:

        typedef ElIterator<T> P;

	    LIterator(Element<T>* e = NULL): P::ElIterator(e,'l'){}

	    void next()
	    {
	        if(P::it!=NULL)
                P::it=P::it->prev;
	    }

        LIterator& operator++()
        {
            next();
            return *this;
        }

        LIterator operator++(int i)
        {
            LIterator copy(P::it);
            next();

            return copy;
        }

        LIterator& operator--()
        {
            if(P::it!=NULL)
                P::it=P::it->next;
            return *this;
        }

        LIterator operator--(int i)
        {
            LIterator copy(P::it);
            --(*this);

            return copy;
        }




};


#endif

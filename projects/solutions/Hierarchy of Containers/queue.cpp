#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "doubleList.cpp"


template<typename T>
class Queue:public DoubleList<T>
{
public:
   typedef DoubleList<T> DL;

    Queue(string t =" "):DoubleList<T>(t){}

    void add(const T& x)
    {
        DL::addAt(x,false);
    }

    T get()
    {
        return DL::getAt(true);
    }


    Element<T>* begin() const
    {
        return DL::front;
    }

    string getType() const
    {
        return "queue";
    }

    void sort()
    {

        if(DL::front == NULL) return;
        DL::front = DL::mSort(DL::front,DL::size);

        Element<T>* p = DL::front;
        while(p->next!=NULL)
            p=p->next;
        DL::end = p;
    }

    void print(ofstream& o) const
    {
        o<<getType()<<" ";
        o<<DL::getDataType()<<" ";
        QIterator<T> i(begin());
        while(i)
        {
            o<<(*i)<<" ";
            ++i;
        }

    }

};


template<typename T>
class QIterator:public ElIterator<T>
{

    public:

        typedef ElIterator<T> P;

	    QIterator(Element<T>* e = NULL): P::ElIterator(e,'q'){}

        void next()
        {
            if(P::it!=NULL)
                P::it=P::it->next;
        }

        QIterator& operator++()
        {
            next();
            return *this;
        }

        QIterator operator++(int i)
        {
            QIterator copy(P::it);
            next();
            return copy;
        }




};


#endif


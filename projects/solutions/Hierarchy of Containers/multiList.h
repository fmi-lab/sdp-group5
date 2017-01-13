#ifndef MULTILIST_H
#define MULTILIST_H

#include "hList.cpp"



struct Data
{

    string type;
    union
    {
        int I;
        bool B;
        double D;
    };


    Data(){};
    Data(string t):type(t){}
    Data(const Data& d);
    Data(int i);
    Data(bool b);
    Data(double d);

    operator bool();
    operator double();
    operator int();
    bool operator==(Data const&) const;
    bool operator<(Data const& d) const;
    bool operator<=(const Data& d) const;


};

ofstream& operator<<(ofstream&,Data);
ifstream& operator>>(ifstream&,Data);
ostream& operator<<(ostream&,Data);
istream& operator>>(istream&,Data);




class MultiList:public HList<Data>
{
public:

     void read(ifstream&);

    bool member(int );

    bool member(bool);

    bool member(double);

    void addBalanced(int );
    void addBalanced(double);
    void addBalanced(bool);

    using ConditionB = bool (*)(bool);
    using ConditionI = bool (*)(int);
    using ConditionD = bool (*)(double);

    void filter(ConditionD);
    void filter(ConditionI);
    void filter(ConditionB);
    bool searchCond(ConditionI) const;
    bool searchCond(ConditionD) const;
    bool searchCond(ConditionB) const;

};



#endif // MULTILIST_CPP


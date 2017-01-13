#include "multiList.h"


Data::Data(const Data& d):type(d.type)
{
    if(type=="int") I=d.I;
    if(type=="bool") B=d.B;
    if(type=="double") D=d.D;
}

Data::Data(int i):type("int"),I(i){}

Data::Data(bool b):type("bool"),B(b){}

Data::Data(double d):type("double"),D(d){}

Data::operator bool()
{
    return B;
}

Data::operator double()
{
    return D;
}

Data::operator int()
{
    return I;
}
bool Data::operator==(Data const& d) const
{
    if(type=="int")
    {
        if(d.type == "int") return I==d.I;
        if(d.type == "double") return I==d.D;
        if(d.type == "bool") return I==d.B;
    }

    if(type=="bool")
    {
        if(d.type == "int") return B==d.I;
        if(d.type == "double") return B==d.D;
        if(d.type == "bool") return B==d.B;
    }

    if(type=="double")
    {
        if(d.type == "int") return D==d.I;
        if(d.type == "double") return D==d.D;
        if(d.type == "bool") return D==d.B;

    }
    return false;
}

bool Data::operator<(Data const& d) const
{
    if(type=="int")
    {
        if(d.type == "int") return I<d.I;
        if(d.type == "double") return I<d.D;
        if(d.type == "bool") return I<d.B;
    }

    if(type=="bool")
    {
        if(d.type == "int") return B<d.I;
        if(d.type == "double") return B<d.D;
        if(d.type == "bool") return B<d.B;
    }

    if(type=="double")
    {
        if(d.type == "int") return D<d.I;
        if(d.type == "double") return D<d.D;
        if(d.type == "bool") return D<d.B;

    }
    return false;
}

bool Data::operator<=(const Data& d) const
{
    return (*this<d||*this==d);
}

ofstream& operator<<(ofstream& f,Data d)
{
    if(d.type=="int") f<<d.I;
    if(d.type=="double") f<<d.D;
    if(d.type=="bool") f<<d.B;
    return f;
}

ifstream& operator>>(ifstream& f,Data d)
{
    if(d.type=="int") f>>d.I;
    if(d.type=="double") f>>d.D;
    if(d.type=="bool") f>>d.B;

    return f;
}

ostream& operator<<(ostream& f,Data d)
{
    if(d.type=="int") f<<d.I;
    if(d.type=="double") f<<d.D;
    if(d.type=="bool") f<<d.B;

    return f;
}

istream& operator>>(istream& f,Data d)
{
    if(d.type=="int") f>>d.I;
    if(d.type=="double") f>>d.D;
    if(d.type=="bool") f>>d.B;
    return f;
}





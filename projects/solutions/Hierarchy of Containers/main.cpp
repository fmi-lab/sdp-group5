//#include "hList.cpp"
#include "multiList.h"
#include<fstream>


bool cond(const int& x)
{
    return x%2 == 0;
}

bool cond2(double x)
{
    return x>10;
}

bool cond3(bool x)
{
    return x;
}


void Test1()
{
    HList<int> h;
    ifstream f("test1.txt");
    ofstream o("ans1.txt");
    h.readInt(f);
    h.print(o);
    for(int i = 0;i<10;i++)
    h.addBalanced(1000 + i);

    o<<endl<<"Add 10 integers :"<<endl;
    h.print(o);

    o<<endl<<"Member 128?: "<<h.member(128)<<endl;
    o<<endl<<"Member 1001?: "<<h.member(1001)<<endl;

    h.sort();
    o<<endl<<"Sorted list:"<<endl;
    h.print(o);


    o<<endl<<"Filter odd numbers: "<<endl;
    h.filter(&cond);
    h.print(o);

    o<<endl<<" Iterator 1: "<<endl;
    for(SortedIterator<int> it(h);it;++it)
        o<<*it<<" ";

    o<<endl<<" Iterator 2: "<<endl;
    for(Iterator<int> it(h);it;++it)
        o<<*it<<" ";

    o<<endl<<" Iterator 3: "<<endl;
    for(Iterator<int> it(h,true);it;++it)
    o<<*it<<" ";

}


void Test2()
{
    MultiList h;
    ifstream f("test2.txt");
    ofstream o("ans2.txt");
    h.read(f);
    h.print(o);



    o<<endl<<"Add 1000, 1225.25 and true: "<<endl;
    h.addBalanced(1000);
    h.addBalanced(1225.25);
    h.addBalanced(true);

    h.print(o);

    o<<endl<<"Member 128?: "<<h.member(128)<<endl;
    o<<endl<<"Member 1225.25?: "<<h.member(1225.25)<<endl;

    h.sort();
    o<<endl<<"Sorted list:"<<endl;
    h.print(o);


    o<<endl<<"Filter double numbers > 10: "<<endl;
    h.filter(&cond2);
    h.print(o);

    o<<endl<<"Filter odd integer numbers: "<<endl;
    h.filter(&cond3);
    h.print(o);

    o<<endl<<" Iterator 1: "<<endl;
    for(SortedIterator<Data> it(h);it;++it)
        o<<*it<<" ";
    o<<endl<<" Iterator 2: "<<endl;
    for(Iterator<Data> it(h);it;++it)
        o<<*it<<" ";
    o<<endl<<" Iterator 3: "<<endl;
    for(Iterator<Data> it(h,true);it;++it)
    o<<*it<<" ";
}

void Test3()
{
    BinTree<int> t;
    for(int i=0;i<10;i++)
        t.add(i);
    t.printNode(t.begin());
    cout<<endl<<"Balanced tree:"<<endl;
    t.sort();
    t.printNode(t.begin());


}

int main()
{
    Test1();
    Test2();
    //Test3();

}


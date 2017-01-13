#include<iostream>
#include<fstream>
using namespace std;
#include<string>
#include "map.h"
#include "interactiveMode.h"

int main(int argc,char **argv)
{
        if(argc>1 && strcmp(argv[1],"-i")==0)
        {
            ifstream f(argv[2]);
            ofstream o("ans.txt");
            Map m;
            m.read(f);
            m.print(o);
            InteractiveMode p(m);
            p.start();

        }

}

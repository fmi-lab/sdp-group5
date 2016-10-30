#include<iostream>
using namespace std;
#include<vector>

vector<int> s[3];

void hanoi(int n, int from, int mid, int to)
{
    if(n==1)
    {
        cout<<"disk "<<s[from].back()<<" from "<<from+1<<" to "<<to+1<<endl;
        s[to].push_back(s[from].back());
        s[from].pop_back();
    }
    else
    {
        hanoi(n-1, from, to, mid );
        cout<<"disk "<<s[from].back()<<" from "<<from+1<<" to "<<to+1<<endl;
        s[to].push_back(s[from].back());
        s[from].pop_back();
        hanoi(n-1, mid, from, to);
    }
}


int main()
{
    int n;
    cin>>n;

    for(int i=n;i>0;i--)
        s[0].push_back(i);

    hanoi(n, 0, 1, 2);

}

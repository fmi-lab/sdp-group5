#include<iostream>
using namespace std;
#include<queue>
#include<ctime>
#include<cstdlib>
#include<iomanip>


typedef pair<int,int> Position;

const int Max = 100;

int M[Max][Max];

void generateMatr(int A[][Max], int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            A[i][j]=-1;

    int cnt=0, x, y;
    while(cnt<0.3*n*n)
    {

        x=rand()%n;
        y=rand()%n;

        if(A[x][y]==-1)
            cnt++;
        A[x][y] = -2;
    }
}

bool isValid(int A[][100], int n, int x, int y)
{
    return x>=0 && x<n && y>=0 && y<n && A[x][y]==-1;
}


int main()
{
    srand(time(NULL));
    int n, startX, startY, endX, endY;
    cin>>n;
    generateMatr(M, n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            if(M[i][j]==-2) cout<<setw(4)<<"*";
            else cout<<setw(4)<<"-";
        cout<<endl;
    }

    cin>>startX>>startY>>endX>>endY;

    queue<Position> q;
    q.push(Position(startX, startY));
    M[startX][startY]=0;
    bool found=0;
    while(!q.empty()&&!found)
    {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();

        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1&&!found;j++)
            {
                if(abs(i+j)==1 && isValid(M,n,x+i,y+j))
                {
                    if(x+i==endX && y+j==endY)
                    {
                        found=1;
                    }
                    else
                    {
                        q.push(Position(x+i,y+j));
                    }
                    M[x+i][y+j]=M[x][y]+1;
                }
            }
        }


    }

    if(!found)
    {
        cout<<endl<<"Path is not found!"<<endl;
    }

    cout<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(M[i][j]==-2)
                cout<<setw(4)<<"*";
            else
            if(M[i][j]==-1)
                cout<<setw(4)<<"-";
            else
                cout<<setw(4)<<M[i][j];
        }
        cout<<endl;
    }

}



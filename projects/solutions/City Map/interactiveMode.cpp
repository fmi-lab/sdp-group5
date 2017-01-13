#include "interactiveMode.h"

InteractiveMode::InteractiveMode(Map& m):cityMap(m),intersection(m.first()){}

string InteractiveMode::getCurrentInt() const
{
    return intersection;
}

void InteractiveMode::setCurrentInt(string& s)
{
    intersection = s;
}

void InteractiveMode::start()
{
    string command;
    string s;
    cin>>command;
    while(command != "end")
    {
        if(command == "location")
        {
            cout<<getCurrentInt()<<endl;
        }
        else
        if(command == "change")
        {
            cin>>s;
            setCurrentInt(s);
            cout<<endl;
        }
        else
        if(command == "neighbours")
        {
            vector<string> v;
            cityMap.getNeighbours(intersection,v);
            for(int i=0;i<v.size();i++)
            {
                cout<<v[i]<<" ";
            }
            cout<<endl;
        }
        else
        if(command == "move")
        {
            cin>>s;
            vector<string> v;
            if(!cityMap.getPath(intersection,s,v))
            {
                cout<<"There is not path from "<<intersection<<" to "<<s<<endl;
            }
            else
            {
                cout<<endl;
                for(int i=1;i<v.size();i++)
                {
                    cout<<"->"<<v[i];
                }
                cout<<endl;
                intersection = s;
            }

        }
        else
        if(command == "close")
        {
            cin>>s;
            vector<string> v;
            v.push_back(s);
            cityMap.close(v);
        }
        else
        if(command == "open")
        {
            cin>>s;
            vector<string> v;
            v.push_back(s);
            cityMap.open(v);
        }
        else
        if(command == "closed")
        {
             vector<string> v;
             cityMap.closed(v);
             if(v.empty())
             {
                 cout<<"There aren't closed intersections!"<<endl;
             }
             else
             {
                 for(int i=0;i<v.size();i++)
                 {
                     cout<<v[i]<<" ";
                 }
                 cout<<endl;
             }
        }
        else
        if(command == "tour")
        {
            list<string> l;
            if(!cityMap.tour(intersection,l))
            {
                cout<<"Can't be made tour!"<<endl;
            }
            else
            {

                for(list<string>::reverse_iterator it = l.rbegin();it!=l.rend();++it)
                {
                    cout<<"=>"<<(*it);
                }
                cout<<endl;
            }
        }
        else
        if(command == "closedStreets")
        {
            vector<pair<string,string> > v;
            cityMap.closedStreets(v);
            if(v.empty())
            {
                cout<<"There aren't closed streets"<<endl;
            }
            else
            {
                for(int i=0;i<v.size();i++)
                cout<<v[i].first<<"->"<<v[i].second<<endl;
            }
        }
        else
        if(command == "pathToAll")
        {
            if(cityMap.pathToAll(intersection))
            {
                cout<<"There are paths to all other open intersections!"<<endl;
            }
            else
            {
                cout<<"There are not paths to all other intersections!"<<endl;
            }
        }
        else
        if(command == "cycle")
        {
            if(cityMap.cycle(intersection))
            {
                cout<<"There is a cycle starting and ending in this Intersection"<<endl;
            }
            else
            {
                cout<<"There is not a cycle starting and ending in this Intersection"<<endl;
            }
        }

        cin>>command;


    }

}

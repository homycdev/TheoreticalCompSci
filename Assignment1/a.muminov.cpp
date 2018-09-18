#include <bits/stdc++.h>
using namespace std;
vector<string> states,alpha,fin;
map<string,vector<string> > adj;
map<string,vector<string> > adj2;
map<string,bool > vis;
map<string,bool > vis2;

//Validates states
void validatestates(string a)
{
    for(int i = 0;i< states.size();i++)
    {
        if(a==states[i])
            return ;
    }
    cout<<"Error:\n";
    cout<<"E1: A state \'"<<a<<"\' is not in set of states";
    exit(0);
}

//Validates alphabet
void validatealpha(string a)
{
    for(int i=0;i<alpha.size();i++)
    {
        if(alpha[i] == a)
            return;
    }
    cout<<"Error:\n";
    cout<<"E3: A transition \'"<<a<<"\' is not represented in the alphabet";
    exit(0);

}
int CNT = 0;
void dfs(string x)
{
    if(vis[x])return;
    CNT++;
    vis[x]=1;
    for(int i=0;i<adj[x].size();i++)
    {
        dfs(adj[x][i]);
    }
}

//Needed to check disjoint in directed graph
void dfs2(string x)
{
    if(vis[x])
        return;
    vis[x] = 1;
    
    CNT++;

    for(int i=0;i<adj2[x].size();i++)
    {
        dfs2(adj2[x][i]);
    }
    return;
}

int main()
{

    freopen("fsa.txt","r",stdin);
    freopen("result.txt","w",stdout);

    string txt;
    getline(cin,txt);

    txt[txt.size()-1]=',';
    string temp = "";
    
    for(int i=8; i+1<txt.size(); i++)
    {
        temp = temp + txt[i];
        if(txt[i+1]==',')
        {
            states.push_back(temp);
            temp.clear();
            i++;
        }
    }
     getline(cin,txt);


     temp = ""; txt[txt.size()-1]=',';

    for(int i=7; i+1<txt.size(); i++)
    {
        temp = temp + txt[i];
        if(txt[i+1]==',')
        {
            alpha.push_back(temp);
            temp.clear();
            i++;
        }
    }


    getline(cin,txt);

    txt[txt.size()-1]=',';
    temp = "";
    vector<string> initstates;

    for(int i=9; i+1<txt.size(); i++)
    {
        temp = temp + txt[i];
        if(txt[i+1]==',')
        {
            initstates.push_back(temp);
            temp.clear();
            i++;
        }
    }
    if(initstates.empty())
    {
        printf("Error:\nE4: Initial state is not defined");
        return 0;
    }
    vector<string> finalstates;getline(cin,txt);

    txt[(int)txt.size()-1]=',';
    temp="";
    for(int i=8; i+1<txt.size(); i++)
    {
        temp = temp + txt[i];
        if(txt[i+1]==',')
        {
            finalstates.push_back(temp);
            temp.clear();
            i++;
        }
    }

    map<pair<string,string>, vector<string> > tran;
    temp="";  getline(cin,txt);
    txt[(int)txt.size()-1] = ',';
    for(int i=7; i+1<txt.size(); i++)
    {
        temp = temp + txt[i];
        if(txt[i+1]==',')
        {
            //Reading the transitions
            for(int j=0;j<temp.size();j++)
                if(temp[j] == '>')
                    temp[j] = ' ';
            stringstream in;

            in<<temp;
            string a,b,c;
            in>>a;in>>c;in>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
            adj2[a].push_back(b);
            validatestates(a);validatestates(b);validatealpha(c);
            tran[{a,b}].push_back(c);
            temp.clear();
            i++;
        }
    }
    vis.clear();
    string initialstate = initstates[0];

    dfs(initialstate);
     vis.clear();

    if(CNT != states.size())
    {
        cout<<"Error:\nE2: Some states are disjoint";
        return 0;
    }
    bool incomplete = 1;
    for(int i=0;i<states.size();i++)
    {
        set<string> h;
        for(int j=0;j<adj2[states[i]].size();j++)
        {
           for(int k=0;k<tran[{states[i],adj2[states[i]][j]}].size();k++)
            h.insert(tran[{states[i],adj2[states[i]][j]}][k]);
        }
        if(h.size()!=alpha.size())
            incomplete = 0;
    }
    if(incomplete==1)
        printf("FSA is complete");
    else printf("FSA is incomplete");
    bool war = 1;
    if(finalstates.empty()){

        if(war){war = 0; printf("\nWarning:");}
        printf("\nW1: Accepting state is not defined");
    }
    vis.clear();
    CNT  = 0;
    dfs2(initialstate);
    if(CNT != states.size())
    {
        if(war){war = 0; printf("\nWarning:");}
        printf("\nW2: Some states are not reachable from initial state");
    }
    int Nodet = 1;
    for(int i = 0;i<states.size();i++)
    {
        if(states.size()!=alpha.size())Nodet = 0;
    }

    return 0;
}
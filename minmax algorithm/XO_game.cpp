#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
char board[100][100];
void init()
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j]='*';
}
void print()
{
    cout<<"---------------------------------\n";
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            cout<<board[i][j]<<"  ";
        cout<<endl;
    }
    cout<<"---------------------------------\n";

}
string win;
bool iscan()
{
    for(int i=0; i<3; i++)
    {
        bool f=0;
        char c=board[i][0];
        for(int j=1; j<3; j++)
        {
            if(board[i][j]!=c)
            {
                f=1;
                break;
            }
        }
        if(!f && (c=='o' || c=='x'))
        {
            if(c=='x')
                win="computer";
            else
                win="your";
            return 0;
        }

    }
    for(int i=0; i<3; i++)
    {
        bool f=0;
        char c=board[0][i];
        for(int j=1; j<3; j++)
        {
            if(board[j][i]!=c)
            {
                f=1;
                break;
            }
        }
        if(!f && (c=='o' || c=='x'))
        {
            if(c=='x')
                win="computer";
            else
                win="your";
            return 0;
        }

    }
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2] && (board[0][0]=='o' || board[0][0]=='x'))
    {
        if(board[0][0]=='x')
            win="computer";
        else
            win="your";
        return 0;
    }
    if(board[0][2]==board[1][1] && board[0][2]==board[2][0] && (board[0][2]=='o' ||board[0][2]=='x'))
    {
        if(board[0][2]=='x')
            win="computer";
        else
            win="your";
        return 0;
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            if(board[i][j]=='*')
                return 1;
    }
    win="tie";
    return 0;
}
bool isok(int i,int j)
{
    return i>=0 && i<3 && j>=0 && j<3 && board[i][j]=='*';
}

int min_max_alg(int turn)
{
    if(!iscan())
    {
        if(win=="your")
            return -1;
        else if(win=="tie")
            return 0;
        else
            return 1;
    }
    if(turn)
    {
        int best=INT_MIN;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j]=='*')
                {
                    board[i][j]='x';
                    int score=min_max_alg(0);
                    best=max(best,score);
                    board[i][j]='*';
                }
            }
        }
        return best;
    }
    else
    {
        int best=INT_MAX;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j]=='*')
                {
                    board[i][j]='o';
                    int score=min_max_alg(1);
                    best=min(best,score);
                    board[i][j]='*';
                }
            }
        }
        return best;
    }
}

pair<int,int> best()
{
    pair<int,int>ans;
    int score=-1e9;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            if(board[i][j]=='*')
            {
                board[i][j]='x';
                int tmp=min_max_alg(0);
                board[i][j]='*';
                if(tmp>score)
                {
                    score=tmp;
                    ans.first=i;
                    ans.second=j;
                }
            }
    }
    return ans;
}






int main()
{
    init();
    cout<<"you is 'o' \ncomputer in 'x'\n";
    print();
    bool turn=1;
    while(iscan())
    {
        if(turn)
        {
            cout<<"Enter your choice : ";
            int i,j;
            while(true)
            {
                cin>>i>>j;
                i--;
                j--;
                if(isok(i,j))
                    break;
                cout<<"invaild option Enter again : ";

            }
            cout<<"ok option\n";
            board[i][j]='o';
            print();
            turn=0;
        }
        else
        {
            pair<int,int>p=best();
            board[p.first][p.second]='x';
            turn=1;
            print();
        }

    }
    cout<<win<<endl;
}

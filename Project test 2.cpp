#include<bits/stdc++.h>
using namespace std;
int a[100],m;
string st[100];

map<string,bool>mp;

vector<string>v[100];
vector<string>Final;
int bin_converter (int n)
{

    int i,j,cnt;
    for (i=0; i<m; i++)
    {
        for (j=0; j<n; j++)
        {
            st[a[i]].push_back('0');
        }
    }
    for (i=0; i<m; i++)
    {
        int temp=a[i];
        j=n-1;
        while (temp!=0)
        {
            if (temp%2==1)
                st[a[i]][j]='1';
            temp=temp/2;
            j--;
        }
    }

}
vector<string>t[100];
void reducing_minterms (string a, string b,int n)
{
    int i,j,len,cnt;
    len=a.size();
    cnt=0;
    for (i=0; i<len; i++)
    {
        if (a[i]!=b[i])
        {
            cnt++;
        }
    }
    if (cnt==1)
    {
        mp[a]=true;
        mp[b]=true;
        for (i=0; i<len; i++)
        {
            if (a[i]!=b[i])
            {
                a[i]='-';
                t[n].push_back(a);
                break;
            }
        }

    }
}
void grouping(int n)
{
    int i,j,cnt;
    for (i=0; i<m; i++)
    {
        cnt=0;
        for (j=0; j<n; j++)
        {
            if (st[a[i]][j]=='1')
                cnt++;
        }
        v[cnt].push_back(st[a[i]]);
        //cout<<st[i]<<endl;
    }
    printf("\n------Firstly grouped on the basis of the numbers of 1..------\n\n");
    for (i=0; i<=n-1; i++)
    {
        int len=v[i].size();
        if (len!=0)
        {

            printf("Group %d :-\n",i);
            for (j=0; j<len; j++)
                cout<<v[i][j]<<' ';
        }
        cout<<endl<<endl;
    }
    int p=n;
    while (p--)
    {
        for (i=0; i<=n-1; i++)
        {
            int len=v[i].size();
            if (len!=0)
            {
                for (j=0; j<len; j++)
                {
                    for (int k=0; k<v[i+1].size(); k++)
                    {
                        reducing_minterms(v[i][j],v[i+1][k],i);
                    }
                    if (mp[v[i][j]]==false)
                        Final.push_back(v[i][j]);
                }


            }
            // mp.clear();

        }
        for (i=0; i<=n-1; i++)
        {
            v[i].clear();
        }
        int flg=0;
        for (i=0; i<n; i++)
        {
            int len=t[i].size();
            if (len!=0)
            {
                if (flg==0)
                {
                    printf("\n-----------After Reducing Group------------\n\n");
                    flg=1;
                }
                printf("\nRduced Group %d :-\n\n",i);
                set<string>Red;
                set<string>::iterator it;
                for (j=0; j<len; j++)
                {
                    Red.insert(t[i][j]);

                }
                int L=Red.size();
                for (j=0; j<L; j++)
                {

                    it=Red.begin();
                    cout<<*it<<' ';
                    v[i].push_back(*it);
                    Red.erase(it);
                }

                cout<<endl;
            }
        }
        for (i=0; i<n; i++)
        {
            t[i].clear();
        }
    }

}
vector<string>ans[100];
void final_result(int n)
{
    int i,j,len,cnt,k,chk;
    len=Final.size();
    for (i=0;i<m;i++)
    {

        for (j=0;j<len;j++)
        {
            chk=1;
            for (k=0;k<n;k++)
            {
               if (st[a[i]][k]!=Final[j][k] && Final[j][k]!='-')
               {
                   chk=0;
                   break;
               }
            }
            if (chk==1)
            {
                ans[i].push_back(Final[j]);
            }
        }
    }
    Final.clear();
    for (i=0;i<m;i++)
    {
        if (ans[i].size()==1)
        {
            Final.push_back(ans[i][0]);
        }
    }



}
void display(int n)
{
    int i,j,len=Final.size();
    char ch;
    printf("\n**********Final Result After Simplification:- *************\n\n");
    printf("\n Minterms :- \n\n");

    for (i=0; i<len; i++)
    {
        cout<<Final[i]<<' ';
    }

    printf("\n\nUsing Variables:-\n\n");
    for (i=0; i<len; i++)
    {
        ch='A';
        for (j=0; j<n; j++)
        {
            if (Final[i][j]!='-')
                cout<<ch;
            if (Final[i][j]=='0')
                cout<<'`';
            ch++;
        }
        if (i!=len-1)
            cout<<" + ";
    }
    cout<<endl<<endl;
}
int main ()
{
    int i,j,n,l,cnt;
    while (1)
    {
        printf("Enter Number Of Variables(-1 for exit):-\n");
        cin>>n;
        if (n==-1)
            break;
        printf("Enter Number Of Minterms:-\n");
        cin>>m;
        for (i=0; i<m; i++)
            cin>>a[i];
        sort(a,a+n);
        bin_converter(n);
        grouping (n);
        display(n);
        final_result(n);


        mp.clear();
    }
    return 0;
}

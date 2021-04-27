#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

const int inc = 5;
const int n = (int)1e5;
const int m = (int)1e8;
vector<int> V;

long long comps = 0;
double timeTook = 0;
chrono::high_resolution_clock::time_point timeStart;
chrono::high_resolution_clock::time_point timeEnd;
chrono::duration<double> diff;

int rand(int a, int b)
{
    return a + random()%(b - a + 1);
}

int binSearch(int l, int p, int key)
{
    int mid = (l + p) / 2;
    
    if(p - l <= 1)return 0;
    
    if(comps++ > -1 && V[mid] == key ) return 1;
    else if(comps++ > -1 && V[mid] > key)
    {
        return binSearch(l, mid, key);
    }
    else if(comps++ > -1 && V[mid] < key)
    {
        return binSearch(l, mid, key);
    }

    return 0;
}

int pre(int l, int p, int key)
{
    comps = 0;
    timeStart = chrono::high_resolution_clock::now();
    int ans = binSearch(l, p, key);
    timeEnd = chrono::high_resolution_clock::now();
    diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
    //cerr<<diff.count()<<" ";
    timeTook = diff.count()*1000000000;
    return ans;
}

int main()
{
    srand(time(NULL) + getpid());
    
    
    V.reserve(0);
    for(int i = 0; i < n; i++)
    {
        V.push_back(i*2);
    }
    
    for(int size = 1000; size <= n; size+=1000)
    {
        vector<double> Com(4), Time(4);
        cerr<<size<<"\n";
        for(int i = 0; i < m; i++)
        {
            
            int small = size/1000 * 2;
            int mid = size;
            int big = size * 2 - size/10;
            int out = size + 1;
            
            

            pre(0, size-1, small);
            Com[0] += (double)comps*1.0  / m;
            Time[0] += (double)timeTook*1.0 / m;
            
            pre(0, size-1, small);
            Com[1] += (double)comps*1.0  / m;
            Time[1] += (double)timeTook*1.0 / m;

            pre(0, size-1, small);
            Com[2] += (double)comps*1.0  / m;
            Time[2] += (double)timeTook*1.0 / m;

            pre(0, size-1, small);
            Com[3] += (double)comps*1.0  / m;
            Time[3] += (double)timeTook*1.0 / m;
        }
        cout<<size<<";;";

        cout<<(long long)Com[0]<<";"<<(long long)Time[0]<<";;";
        cout<<(long long)Com[1]<<";"<<(long long)Time[1]<<";;";
        cout<<(long long)Com[2]<<";"<<(long long)Time[2]<<";;";
        cout<<(long long)Com[3]<<";"<<(long long)Time[3]<<"\n";

    }
    
    
}
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

const int inf = (int) 1e6;
const int m = 1000;

int comp1 = 0, swap1 = 0;
chrono::high_resolution_clock::time_point timeStart;
chrono::high_resolution_clock::time_point timeEnd;

int rand(int a, int b)
{
    return a + random()%(b - a + 1);
}

vector<int> randomizedArray(int len)
{
    vector<int> V;

    for(int i = 0; i < len; i++)
    {
        V.push_back(rand(-inf , inf));
    }

    return V;
}

int selection(int *v, int n, int k, int div) {
    if (n == 1 && k == 0) return v[0];

    int m = (n + div-1)/div;
    int *medians = new int[m];
    for (int i=0; i<m; i++) {
        if (div*i + div - 1 < n) {
            int *w = v + div*i;
            for (int j0=0; j0<(div+1)/2; j0++) {
                int jmin = j0;
                for (int j=j0+1; j<div; j++) {
                    comp1++;
                    if (w[j] < w[jmin]) jmin = j;
                }
                swap1++;
                swap(w[j0], w[jmin]);
            }
            medians[i] = w[(div+1)/2];
        } else {
            medians[i] = v[div*i];
        }
    }

    int pivot = selection(medians, m, m/2, div);
    delete [] medians;

    for (int i=0; i<n; i++) {
        if (v[i] == pivot) {
            swap1++;
            swap(v[i], v[n-1]);
            break;
        }
    }

    int store = 0;
    for (int i=0; i<n-1; i++) {
        if (v[i] < pivot) {
            swap1++;
            swap(v[i], v[store++]);
        }
    }
    swap(v[store], v[n-1]);

    if (store == k) {
        return pivot;
    } else if (store > k) {
        return selection(v, store, k, div);
    } else {
        return selection(v+store+1, n-store-1, k-store-1, div);
    }
}

int main()
{   
    srand(time(NULL) + getpid());
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);

    string param = "";
    cin>>param;
    
    int n = 0, k = 0;
    cin>>n;
    k = n/2;
    int Vs[n];
    vector<int> V;
    
    vector<double> comps(12, 0.0);
    vector<double> swaps(12, 0.0);
    vector<double> times(12, 0.0);

    for(int i = 0; i < m; i++)
    {
        if(!((i+1)%25))cerr<<"i = "<<i+1<<"\n";
        if(param == "r" || param == "-r")
        {
            V = randomizedArray(n);
        }
        else if(param == "p" || param == "-p")
        {
            for(int i = 1; i <= n; i++)
            {
                V.push_back(i);
            }
            random_shuffle(V.begin(), V.end());
        }
        for(int d = 3; d <= 25; d+=2)
        {
            for(int i = 0; i < n; i++)
            {
                Vs[i] = V[i];
            }
            comp1= 0;
            swap1 = 0;
            timeStart = chrono::high_resolution_clock::now();
            int sel = selection(&Vs[0], n, k-1, d);
            timeEnd = chrono::high_resolution_clock::now();
            //cout<<"Select size "<<d<<" found: "<<sel<<" Comps: "<<comp1<<" Swaps: "<<swap1<<"\n";
            chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
            double timeTake= diff.count()*1000000000.0 / m;
            double compMake = comp1*1.0 / m;
            double swapMake = swap1*1.0 / m;
            comps[(d-3)/2] += compMake;
            swaps[(d-3)/2] += swapMake;
            times[(d-3)/2] += timeTake;
        }
    }
    
    for(int i = 0; i < 12; i++)
    {
        cout<<3 + i*2 <<";"<<(long long)comps[i]<<";"<<(long long)swaps[i]<<";"<<(long long)times[i]<<"\n";
    }

    return 0;
} 
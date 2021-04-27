#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

const int inf = (int) 1e6;
vector<int> Vr(0);

int comp1 = 0, comp2 = 0, swap1 = 0, swap2 = 0;
int index1 = -1, index2 = -1;


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

int partitionRandom(int p, int r)
{
    int i = rand(p, r);
    swap2++;
    cerr<<"R swap "<<r<<" "<<i<<"\n";
    int tmp = Vr[r];
    Vr[r] = Vr[i];
    Vr[i] = tmp;
    tmp = 0;

    int x = Vr[r];
    i = p - 1;
    for(int j = p; j < r; j++)
    {
        comp2++;
        cerr<<"R comp "<<Vr[j]<<" "<<x<<"\n";
        if(Vr[j] <= x)
        {
            i++;
            cerr<<"R swap "<<j<<" "<<i<<"\n";
            swap2++;
            tmp = Vr[j];
            Vr[j] = Vr[i];
            Vr[i] = tmp;
            tmp = 0;
        }
    }
    cerr<<"R swap "<<r<<" "<<i+1<<"\n";
    swap2++;
    tmp = Vr[r];
    Vr[r] = Vr[i + 1];
    Vr[i + 1] = tmp;
    tmp = 0;

    return i + 1;
}

int randomizedSelection(int p, int r, int i)
{
    if(p == r) 
    {   
        index2 = p;
        return Vr[p];
    }
    int q = partitionRandom(p, r);
    cerr<<"R partition: "<<q<<"\n";
    int k = q - p + 1;
    if(i == k)
    {
        index2 = q;
        return Vr[q];
    }
    else if(i < k) return randomizedSelection(p, q-1, i);
    else return randomizedSelection(q+1, r, i-k);
}

int selection(int *v, int n, int k) {
    if (n == 1 && k == 0) return v[0];

    int m = (n + 4)/5;
    int *medians = new int[m];
    for (int i=0; i<m; i++) {
        if (5*i + 4 < n) {
            int *w = v + 5*i;
            for (int j0=0; j0<3; j0++) {
                int jmin = j0;
                for (int j=j0+1; j<5; j++) {
                    comp1++;
                    cerr<<"S comp "<<w[j]<<" "<<w[jmin]<<"\n";
                    if (w[j] < w[jmin]) jmin = j;
                }
                swap1++;
                cerr<<"S swap "<<j0<<" "<< jmin<<"\n";
                swap(w[j0], w[jmin]);
            }
            medians[i] = w[2];
        } else {
            medians[i] = v[5*i];
        }
    }

    int pivot = selection(medians, m, m/2);
    delete [] medians;

    for (int i=0; i<n; i++) {
        if (v[i] == pivot) {
            swap1++;
            cerr<<"S swap "<<i<<" "<< n-1<<"\n";
            swap(v[i], v[n-1]);
            break;
        }
    }

    int store = 0;
    for (int i=0; i<n-1; i++) {
        if (v[i] < pivot) {
            swap1++;
            cerr<<"S swap "<<i<<" "<<store+1<<"\n";
            swap(v[i], v[store++]);
        }
    }
    swap(v[store], v[n-1]);

    if (store == k) {
        return pivot;
    } else if (store > k) {
        return selection(v, store, k);
    } else {
        return selection(v+store+1, n-store-1, k-store-1);
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
    cin>>n>>k;
    int Vs[n];
    vector<int> V;
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
    else return 0;
    cerr<<"Array:\n";
    for(int i = 0; i < V.size(); i++)
    {
        cerr<<V[i]<<" ";
        Vs[i] = V[i];
        Vr.push_back(V[i]);
    }
    cerr<<"\n";

    int sel = selection(&Vs[0], n, k-1);
    int randSel = randomizedSelection(0, n-1, k);
    cout<<"\n\n\n";
    for(int i : V)
    {
        cout<<i<<" ";
    }
    cout<<"\n\n";

    for(int i = 0; i < n; i++)
    {
        if(Vs[i] == sel)
        {
            cout<<"["<<Vs[i]<<"] ";
        }
        else cout<<Vs[i]<<" ";
    }
    cout<<"\n";

    for(int i = 0; i < Vr.size(); i++)
    {
        if(i == index2)
        {
            cout<<"["<<Vr[i]<<"] ";
        }
        else cout<<Vr[i]<<" ";
    }
    cout<<"\n";
    k--;
    nth_element(V.begin(), V.begin() + k, V.end());
    for(int i : V)
    {
        cout<<i<<" ";
    }
    cout<<"\n";
    
    cout<<"Select: "<<sel<<"\n";
    cout<<"RandomSelect: "<<randSel<<"\n";
    cout<<"Control: "<<V[k]<<"\n";
    
    cerr<<"comp Select: "<<comp1<<" swap Select: "<<swap1<<"\n";;
    cerr<<"comp randomSelect: "<<comp2<<" swap randomSelect: "<<swap2<<"\n";
    return 0;
} 
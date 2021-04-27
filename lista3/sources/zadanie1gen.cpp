#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

const int inf = (int) 1e6;
const int m = 100;

chrono::high_resolution_clock::time_point timeStart;
chrono::high_resolution_clock::time_point timeEnd;

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
    int tmp = Vr[r];
    Vr[r] = Vr[i];
    Vr[i] = tmp;
    tmp = 0;

    int x = Vr[r];
    i = p - 1;
    for(int j = p; j < r; j++)
    {
        comp2++;
        if(Vr[j] <= x)
        {
            i++;
            swap2++;
            tmp = Vr[j];
            Vr[j] = Vr[i];
            Vr[i] = tmp;
            tmp = 0;
        }
    }
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
                    if (w[j] < w[jmin]) jmin = j;
                }
                swap1++;
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
    
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    t1 = chrono::high_resolution_clock::now();
    int type = 0;
    cin>>type;

    int ver = 0;
    cin>>ver;
    

    
    if(ver == 1)
    {
        for(int size = 100; size <= 10000; size+=100)
        {
            double compsS = 0.0;
            double swapsS = 0.0;
            double timesS = 0.0;

            double compsR = 0.0;
            double swapsR = 0.0;
            double timesR = 0.0;

            int Vs[size];
            vector<int> V;

            int k = -1;

            if(type == 1)
            {
                k = rand(1, 99);
            }
            else if(type == 2)
            {
                k = rand(size*2/5, size*3/5 );
            }
            else if (type == 3)
            {
                k = rand( size - 99, size - 1 );
            }

            cerr<<size<<" ";
            
            for(int i = 1; i <= m; i++)
            {
                for(int i = 1; i <= size; i++)
                {
                    V.push_back(i);
                }
                random_shuffle(V.begin(), V.end());
                ///// MEDIAN OF MEDIANS SELECT
                Vr = V;
                for(int i = 0; i < size; i++)
                {
                    Vs[i] = V[i];
                }
                comp1= 0;
                swap1 = 0;
                timeStart = chrono::high_resolution_clock::now();

                int sel = selection(&Vs[0], size, k-1);

                timeEnd = chrono::high_resolution_clock::now();
                
                chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
                
                double timeTake= diff.count()*1000000000.0 / m;
                double compMake = comp1*1.0 / m;
                double swapMake = swap1*1.0 / m;
                
                compsS += compMake;
                swapsS += swapMake;
                timesS += timeTake;
                /////RANDOM SELECT

                comp2= 0;
                swap2 = 0;

                timeStart = chrono::high_resolution_clock::now();

                int RSel = randomizedSelection(0, size-1, k);
                
                timeEnd = chrono::high_resolution_clock::now();
                
                diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
                
                timeTake= diff.count()*1000000000.0 / m;
                compMake = comp2*1.0 / m;
                swapMake = swap2*1.0 / m;
                
                compsR += compMake;
                swapsR += swapMake;
                timesR += timeTake;
            }
            long long tim1 = (long long)timesS;
            long long tim2 = (long long)timesR;
            cout<<size<<";;"<<(long long)compsS<<";"<<(long long)swapsS<<";"<<(long long)tim1<<
                ";;"<<(long long)compsR<<";"<<(long long)swapsR<<";"<<(long long)tim2<<"\n";

            
            t2 = chrono::high_resolution_clock::now();

            chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            double time = diff.count();
            cerr<<" "<< time <<"s\n";
                
        }
    }
    else if(ver == 2)
    {
        for(int size = 100; size <= 10000; size+=100)
        {
            double compsS = 0.0;
            double swapsS = 0.0;
            double timesS = 0.0;

            double compsR = 0.0;
            double swapsR = 0.0;
            double timesR = 0.0;

            int Vs[size];
            vector<int> V;

            int k = -1;

            if(type == 1)
            {
                k = rand(1, 99);
            }
            else if(type == 2)
            {
                k = rand(size*2/5, size*3/5 );
            }
            else if (type == 3)
            {
                k = rand( size - 99, size - 1 );
            }

            cerr<<size<<" ";
            for(int i = 1; i <= m; i++)
            {
                V = randomizedArray(size);
                ///// MEDIAN OF MEDIANS SELECT
                Vr = V;
                for(int i = 0; i < size; i++)
                {
                    Vs[i] = V[i];
                }
                comp1= 0;
                swap1 = 0;
                timeStart = chrono::high_resolution_clock::now();

                int sel = selection(&Vs[0], size, k-1);

                timeEnd = chrono::high_resolution_clock::now();
                
                chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
                
                double timeTake= diff.count()*1000000000.0 / m;
                double compMake = comp1*1.0 / m;
                double swapMake = swap1*1.0 / m;
                
                compsS += compMake;
                swapsS += swapMake;
                timesS += timeTake;
                /////RANDOM SELECT

                comp2= 0;
                swap2 = 0;

                timeStart = chrono::high_resolution_clock::now();

                int RSel = randomizedSelection(0, size-1, k);
                
                timeEnd = chrono::high_resolution_clock::now();
                
                diff = chrono::duration_cast<chrono::duration<double>>(timeEnd - timeStart);
                
                timeTake= diff.count()*1000000000.0 / m;
                compMake = comp2*1.0 / m;
                swapMake = swap2*1.0 / m;
                
                compsR += compMake;
                swapsR += swapMake;
                timesR += timeTake;
            }
            long long tim1 = (long long)timesS;
            long long tim2 = (long long)timesR;
            cout<<(long long)compsS<<";"<<(long long)swapsS<<";"<<(long long)tim1<<
                ";;"<<(long long)compsR<<";"<<(long long)swapsR<<";"<<(long long)tim2<<"\n";
            

            t2 = chrono::high_resolution_clock::now();

            chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
            double time = diff.count();
            cerr<<" "<< time <<"s\n";
        }
    }
    
    

    return 0;
} 
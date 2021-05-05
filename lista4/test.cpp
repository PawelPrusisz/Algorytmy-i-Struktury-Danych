#include <bits/stdc++.h>

using namespace std;

vector<string> loadFromFile(string fileName, int start, int end)
{
    vector<string> out;
	//fileName = "KJB.txt";
    ifstream myFile (fileName);
    string line;
    cerr<<"XD";
	if(myFile.is_open())
    {
		int num = 0;
        while(getline(myFile, line))
        {
			bool ok = true;
				for(int i = 0; i < line.size(); i++)
				{
					if(!isalpha(line[i]))
					{
						ok = false;
						break;
					}
				}
				cerr<<".";
				if(line.size() > 0 && ok)
				{
                    num++;
                    if(num >= start && num< end)
					    out.push_back(line);
					
				}
        }
    }
    else
    {
        cout<<"nieprawidlowa nazwa pliku\n";
    }
    random_shuffle(out.begin(), out.end());
    return out;
}


int main()
{
    
    vector<string> V = loadFromFile("aspell_wordlist.txt", 0, 1000000);
    for(int i = 0; i < V.size(); i++)
    {
        cout<<V[i]<<" ";
    }
}
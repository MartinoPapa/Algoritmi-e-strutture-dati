#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

string stampa_array(int v[], int N)
{
   string s = "";
   for (int i = 0; i < N; i++)
   {
      s += to_string(v[i]) + " ";
   }
   s += "\n";
   return s;
}

bool at_position(int *vec, int i, int j)
{
    int m = (i + j) / 2;
    if (i < j)
    {
        if(vec[m]==m) {
            return true;
        }
        if (vec[m] > m)
        {
            return at_position(vec, i, m-1);
        }
        else{
            return at_position(vec, m+1, j);
        }
    }
    return vec[m]==m;
}

int samarcanda(int *vec, int i, int massimo, int maxY){
    if(i>-1){
        massimo= max(maxY-vec[i], massimo);
        maxY = max(vec[i],maxY);
        return samarcanda(vec, i-1, massimo, maxY);
    }
    return massimo == INT16_MIN ? 0 : massimo;
}

int main()
{
    int n;
    int *vec = new int[n];
    input >> n; // num nodi
    int a;
    for (int i = 0; i < n; i++)
    {
        input >> a;
        vec[i]=a;
    }
    cout << samarcanda(vec, n-2, INT16_MIN, vec[n-1]);
    return 0;
}

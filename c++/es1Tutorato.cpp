#include <iostream>
#include <fstream> // file di testo
#include <vector>
#include <utility>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

void ruota(int* v, int N){
    int tmp=v[N-1];
    for (int i = N-1; i > 0; i--)
    {
        v[i]=v[i-1];
    }
    v[0]=tmp;
}

string stampa(int v[], int N){
    string s="";
    for (int i = 0; i < N; i++)
    {
        s+=to_string(v[i])+" ";
    }
    s+="\n";
    return s;
}

int main()
{
    int N;
    input >> N;
    int vec[N];
    for (int i = 0; i < N; i++)
    {
        input >> vec[i];
    }
    cout << stampa(vec, N);
    ruota(vec, N);
    cout << stampa(vec, N);
    return 0;
}
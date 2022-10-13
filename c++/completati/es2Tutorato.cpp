#include <iostream>
#include <fstream> // file di testo
#include <vector>
#include <utility>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int prodotto_incrociato(int v1[], int v2[], int N){
    int sum=0;
    for (int i = 0; i < N; i++)
    {
        sum+=(v1[i]*v2[N-i-1]);
    }
    return sum;
}

int prodotto_ricorsivo(int i, int v1[], int v2[], int N){
    if(i<N){
        int sum = v1[i]*v2[N-1-i];
        return sum+prodotto_ricorsivo(i+1, v1, v2, N);
    }
    else{
        return 0;
    }
}


int main()
{
    int N;
    input >> N;
    int vec1[N], vec2[N];
    for (int i = 0; i < N; i++)
    {
        input >> vec1[i];
    }
    for (int i = 0; i < N; i++)
    {
        input >> vec2[i];
    }
    output << prodotto_ricorsivo(0,vec1,vec2,N);
    
    return 0;
}
#include <iostream>
#include <fstream> // file di testo
#include <utility>
#include "martino.h"

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");


int main()
{
    int N;
    input >> N;
    int vec[N];
    for (int i = 0; i < N; i++)
    {
        input >> vec[i];
    }
    cout << stampa_array(vec, N);
    ruota_array(vec, N, 2);
    cout << stampa_array(vec, N);
    return 0;
}
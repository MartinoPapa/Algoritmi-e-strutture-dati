#include <iostream>
#include <fstream> // file di testo
/*

#include <utility> //pair
#include <algorithm> //sort, struct ...
#include <queue>
#include <stack>
*/

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int main()
{
    int N; //numeroElementi
    input >> N;
    int lista[N];
    for(int i = 0; i<N; i++){
        input >> lista[i];
    }

    int seqTmp=0, seqMax=0; //somma parziale, somma definitiva
    for(int i = 0; i<N; i++){
        seqTmp += lista[i];
        if(seqTmp > seqMax) seqMax=seqTmp; 
        else if(seqTmp < 0) seqTmp = 0;
    }
    output << seqMax;
    return 0;
}   
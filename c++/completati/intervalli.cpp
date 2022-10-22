#include <iostream>
#include <fstream> // file di testo
#include <utility>
#include <algorithm>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int lunghezza(pair<int, int> intervallo)
{
    return intervallo.second - intervallo.first + 1;
}

bool comparePairs(pair<int, int> p1, pair<int, int> p2)
{
    return (p1.first < p2.first);
}

int main()
{
    int N;
    input >> N;
    pair<int, int> *intervalli;
    intervalli = new pair<int, int>[N];
    int inizio, fine;
    input >> inizio;
    input >> fine;
    intervalli[0] = make_pair(inizio, fine);
    for (int i = 1; i < N; i++)
    {
        input >> inizio;
        input >> fine;
        intervalli[i] = make_pair(inizio, fine);
    }

    sort(intervalli, intervalli + N, comparePairs); // ordina per il primo elemento

    //fondo gli intervalli tra loro quando possibile
    pair<int, int> *mergedIntervalli;
    mergedIntervalli = new pair<int, int>[N];
    int NumMerged = 0;
    inizio = intervalli[0].first;
    fine = intervalli[0].second;
    for (int i = 1; i < N; i++)
    {
        if (fine >= intervalli[i].first)
        {
            fine = max(intervalli[i].second,fine);
        }
        else
        {
            mergedIntervalli[NumMerged] = make_pair(inizio, fine);
            NumMerged++;
            inizio = intervalli[i].first;
            fine = intervalli[i].second;
        }
    }
    mergedIntervalli[NumMerged] = make_pair(inizio, fine);
    NumMerged++;
    int lunghezzaMax=0;
    int inizioMax=0, fineMax=0;
    int l;
    
    //guardo gli spazi tra gli intervalli e cerco il più lungo
    for (int i = 0; i < NumMerged-1; i++)
    {
        l=mergedIntervalli[i+1].first-mergedIntervalli[i].second;
        if(l>lunghezzaMax){
            inizioMax=mergedIntervalli[i].second;
            fineMax=mergedIntervalli[i+1].first;
            lunghezzaMax=l;
        }
    }
    if(inizioMax!=fineMax){
        output << inizioMax << " " << fineMax;
    }
    else{
        output<<0;
    }
    return 0;
}
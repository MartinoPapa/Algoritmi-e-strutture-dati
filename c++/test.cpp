#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "librerie/array.h"
#include "librerie/grafi.h"

using namespace std;

ifstream input("input.txt");

int distanza_minima(int N, bool *sicuro, int *distanza)
{
    int min = INT16_MAX;
    int indexMin;
    for (int i = 0; i < N; i++)
    {
        if (!sicuro[i] && distanza[i] < min)
        {
            min = distanza[i];
            indexMin = i;
        }
    }
    return indexMin;
}

int *dijkstra(int **matrice_adiacenza, int N, int v0)
{
    int *distanza = new int[N];
    bool *sicuro = new bool[N];

    for (int i = 0; i < N; i++)
    {
        sicuro[i] = false;
        distanza[i] = INT16_MAX;
    }
    distanza[v0] = 0;
    int vicino;
    for (int i = 0; i < N - 1; i++)
    {
        vicino = distanza_minima(N, sicuro, distanza);
        sicuro[vicino] = true;
        if (distanza[vicino] != INT16_MAX)
        {
            for (int j = 0; j < N; j++)
            {
                if (!sicuro[j] && matrice_adiacenza[vicino][j] != INT16_MAX && (distanza[vicino] + matrice_adiacenza[vicino][j] < distanza[j]))
                {
                    distanza[j] = distanza[vicino] + matrice_adiacenza[vicino][j];
                }
            }
        }
    }
    return distanza;
}

void stampa_distanza(int *distanza, int N, int v0)
{
    cout << "Distanze da " << v0 << ":" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i << ") " << distanza[i] << endl;
    }
}

// colorazioni (parto da uno coloro, lo accerto, al contrario gli adiacenti, passo agli adiacenti degli adiacenti), distanza gruppi (erdos)
//  libreria grafi

int main()
{
    int n, m;
    input >> n; // num nodi
    input >> m; // num archi
    grafo g(n);

    int a, b, peso;
    for (int i = 0; i < m; i++)
    {
        input >> a;
        input >> b;
        g.link_two_way(a, b);
    }
    int setA[] = {0,1};
    int setB[] = {5,6};
    int distanzaSet = g.erdos_set(setA, setB, 2, 2);
    cout << distanzaSet;
    return 0;
}

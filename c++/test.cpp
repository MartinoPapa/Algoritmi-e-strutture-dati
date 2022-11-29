#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

void stampa_distanza(int *distanza, int N, int v0)
{
    cout << "Distanze da " << v0 << ":" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i << ") " << distanza[i] << endl;
    }
}

struct nodo;
struct nodo
{
    vector<int> edge;
    vector<int> pesi;
    int numEdge = 0;
    int key;
    nodo() {}
    void addEdge(int key)
    {
        this->edge.push_back(key);
        numEdge++;
    }
    void addEdge(int key, int peso)
    {
        this->edge.push_back(key);
        this->pesi.push_back(peso);
        numEdge++;
    }
};

struct grafo;
struct grafo
{
    nodo *nodi;
    int n;
    grafo(int n)
    {
        nodi = new nodo[n];
        for (int i = 0; i < n; i++)
        {
            this->nodi[i] = nodo();
            nodi[i].key = i;
        }
        this->n = n;
    }
    void link(int i, int j)
    {
        this->nodi[i].addEdge(j);
    }
    void link_two_way(int i, int j)
    {
        this->nodi[i].addEdge(j);
        this->nodi[j].addEdge(i);
    }
    void link(int i, int j, int peso)
    {
        this->nodi[i].addEdge(j, peso);
    }
    void link_two_way(int i, int j, int peso)
    {
        this->nodi[i].addEdge(j, peso);
        this->nodi[j].addEdge(i, peso);
    }
    int *erdos(int v0)
    {
        queue<int> q;
        int *distanze = new int[n];
        q.push(v0);
        for (int i = 0; i < n; i++)
            distanze[i] = -1;
        distanze[v0] = 0;
        int tmp, index;
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            for (int i = 0; i < nodi[tmp].numEdge; i++)
            {
                index = nodi[tmp].edge.at(i);
                if (distanze[index] == -1)
                {
                    distanze[index] = distanze[tmp] + 1;
                    q.push(index);
                }
            }
        }
        return distanze;
    }

    int *num_cammini(int a, int b)
    {
        int *numcammini = new int[n];
        int *distanze = new int[n];
        for (int i = 0; i < n; i++)
        {
            distanze[i] = -1;
            numcammini[i] = 0;
        }
        distanze[a] = 0;
        numcammini[a] = 1;
        queue<int> q;
        q.push(a);
        int tmp;
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            for (int vicino : this->nodi[tmp].edge)
            {
                if (distanze[vicino] == -1)
                {
                    distanze[vicino] = distanze[tmp] + 1;
                    q.push(vicino);
                }
                if (distanze[vicino] == distanze[tmp] + 1)
                {
                    numcammini[vicino] += numcammini[tmp];
                }
            }
        }
        int *res = new int[2];
        res[0] = distanze[b];
        res[1] = numcammini[b];
        return res;
    }
    int max_fortemente_connessa()
    {
        
    }
};
// colorazioni (parto da uno coloro, lo accerto, al contrario gli adiacenti, passo agli adiacenti degli adiacenti), distanza gruppi (erdos)
//  libreria grafi

int main()
{
    int n, m, n1, n2;
    input >> n; // num nodi
    input >> m; // num archi
    grafo g(n);

    int a, b, peso;
    for (int i = 0; i < m; i++)
    {
        input >> a;
        input >> b;
        g.link(a, b);
    }

    return 0;
}

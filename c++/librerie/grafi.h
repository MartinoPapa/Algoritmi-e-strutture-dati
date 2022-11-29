// necessita di array.h, queue, vector
// TODO:
//      to_matrix();
//      from_matrix();

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
    int distanza_minima(bool *sicuro, int *distanza)
    {
        int min = INT16_MAX;
        int indexMin;
        for (int i = 0; i < n; i++)
        {
            if (!sicuro[i] && distanza[i] < min)
            {
                min = distanza[i];
                indexMin = i;
            }
        }
        return indexMin;
    }
    int *dijkstra(int v0)
    {
        int *distanza = new int[n];
        bool *sicuro = new bool[n];
        for (int i = 0; i < n; i++)
        {
            sicuro[i] = false;
            distanza[i] = INT16_MAX;
        }
        distanza[v0] = 0;
        int vicino;
        int *index;
        for (int i = 0; i < n - 1; i++)
        {
            vicino = distanza_minima(sicuro, distanza);
            sicuro[vicino] = true;
            if (distanza[vicino] != INT16_MAX)
            {
                for (int j = 0; j < nodi[vicino].numEdge; j++)
                {
                    index = &nodi[vicino].edge.at(j); // chiave collegamento j-esimo
                    if (!sicuro[*index] && nodi[vicino].pesi[j] != INT16_MAX && distanza[vicino] + nodi[vicino].pesi[j] < distanza[*index])
                    {
                        distanza[*index] = distanza[vicino] + nodi[vicino].pesi[j];
                    }
                }
            }
        }
        return distanza;
    }
    bool color_rec(int *colors, int index, int color)
    {
        colors[index] = color;
        int *index_edge;
        for (int i = 0; i < nodi[index].numEdge; i++)
        {
            index_edge = &nodi[index].edge.at(i);
            if (colors[*index_edge] < 0)
            {
                if (!color_rec(colors, *index_edge, 1 - color))
                    return false;
            }
            else if (colors[*index_edge] == color)
                return false;
        }
        return true;
    }
    // retrun null se non bipartibile
    int *colora_bipartizione()
    {
        int *colors = new int[n];
        for (int i = 0; i < n; i++)
            colors[i] = -1;
        for (int i = 0; i < n; i++)
        {
            if (colors[i] < 0)
            { // evito di ripetere i calcoli su componenti connesse
                if (!color_rec(colors, i, 0))
                    return NULL; // non colorabile
            }
        }
        return colors;
    }
    // setA, setB ordinati
    int erdos_set(int *setA, int *setB, int nA, int nB)
    {
        queue<int> q;
        int *distanze = new int[n];
        for (int i = 0; i < n; i++)
        {
            if (binary_reserch(setA, nA, i) == -1)
                distanze[i] = INT16_MAX; // binary_reserch in array.h
            else
            {
                distanze[i] = 0;
                q.push(i);
                if (binary_reserch(setB, nB, i) != -1)
                    return 0;
            }
        }
        int tmp, index;
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            for (int i = 0; i < nodi[tmp].numEdge; i++)
            {
                index = nodi[tmp].edge.at(i);
                if (distanze[index] == INT16_MAX)
                {
                    distanze[index] = distanze[tmp] + 1;
                    q.push(index);
                    if (binary_reserch(setB, nB, index) != -1)
                        return distanze[index];
                }
            }
        }
        return INT16_MAX;
    }
     int diametro(){
        int max = 0;
        int *dist;
        for (int i = 0; i < n; i++)
        {
            dist=this->erdos(i);
            for (int j = 0; j < n; j++)
            {
                if(dist[j]>max) max=dist[j];
            }       
        }   
        return max;
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
            for (int vicino:this->nodi[tmp].edge)
            {
                if(distanze[vicino]==-1){
                    distanze[vicino] = distanze[tmp]+1;
                    q.push(vicino);
                }
                if(distanze[vicino]==distanze[tmp]+1){
                    numcammini[vicino] += numcammini[tmp];
                }
            }
        }
        int *res = new int[2];
        res[0]=distanze[b];
        res[1]=numcammini[b];
        return res;
    }
};

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
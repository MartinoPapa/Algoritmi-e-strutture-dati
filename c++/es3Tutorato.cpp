#include <iostream>
#include <fstream> // file di testo
#include <vector>
#include <utility>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

struct struttura
{
    vector<int> vettore;
    // struttura() : vettore()
    void aggiungi(int val)
    {
        vettore.push_back(val);
    }
    string stampa(int pos)
    {
        string s = "";
        for (auto &e : vettore)
        {
            s += to_string(pos) + " " + to_string(e) + "\n";
        }
        return s;
    }
};

int main()
{
    int N, M, Q; // numeroElementi
    input >> N;
    input >> M;
    input >> Q;

    vector<struttura> strutture(N);
    int pos, val, val1;
    for (int i = 0; i < M; i++)
    {
        input >> pos;
        input >> val;
        strutture[pos].aggiungi(val);
    }
    vector<pair<int, int>> pairs;
    for (int i = 0; i < Q; i++)
    {
        input >> val >> val1;
        pairs.push_back(make_pair(val, val1));
    }
    string s = to_string(N) + " " + to_string(M) + " " + to_string(Q) + "\n";
    for (int i = 0; i < N; i++)
    {
        s+=strutture[i].stampa(i);
    }
    for (auto &pair : pairs)
    {
        s += to_string(pair.first) + " " + to_string(pair.second) + "\n";
    }
    output << s;

    return 0;
}
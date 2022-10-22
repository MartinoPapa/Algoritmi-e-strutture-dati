#include <iostream>
#include <fstream> // file di testo
#include <utility>
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

int minimo(int *v, int nOrdinati, int N)
{
    int min = v[nOrdinati];
    int indexMin = nOrdinati;
    for (int i = nOrdinati + 1; i < N; i++)
    {
        if (v[i] < min)
        {
            min = v[i];
            indexMin = i;
        }
    }
    return indexMin;
}

int trova(int *v, int e)
{
    // sicuro di trovarlo perchè presenti tutti i numeri da 1-->N
    int i = 0;
    while (v[i] != e)
        i++;
    return i;
}

int swap(int *v, int i, int j)
{
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
    return v[i] + v[j];
}

int main()
{
    int N;
    input >> N;
    int *v;
    v = new int[N];
    for (int i = 0; i < N; i++)
    {
        input >> v[i];
        
    }

    // cercare valore minimo e vedere se conviene effettuare lo swap valore minimo <-> 1
    int indexMin = 0, indexPuntato;
    int nOrdinati = 0; // elementi al loro posto (all'inizio del vettore visto che parto da min)
    int prezzoTmp = 0; // prezzo elementi associati ad un minimo
    int prezzo = 0;
    int risparmioPotenziale = 0;
    int numScambi=0; //soulzione prima parte problema
    int nCiclo=1;
    indexMin = minimo(v, nOrdinati, N);
    while (nOrdinati != N)
    {
        indexPuntato = trova(v, indexMin + 1);
        if (indexMin == indexPuntato)
        {
            // elemento nella posizione corretta
            prezzo += min(prezzoTmp, prezzoTmp - risparmioPotenziale + 2 * (v[indexMin] + 1));
            numScambi+=nCiclo-1; //ogni ciclo richiede minimo nCiclo-1 scambi
            prezzoTmp = 0;
            risparmioPotenziale = 0;
            nCiclo=1;
            nOrdinati++;
            indexMin = minimo(v, nOrdinati, N);
        }
        else
        {
            nCiclo++;
            prezzoTmp += swap(v, indexMin, indexPuntato);
            indexMin = indexPuntato;
            risparmioPotenziale += (v[indexMin] - 1); // risparmio se swappo con elemento 1; indexMin <-- indexPuntato dopo lo swap
        }
    }
    prezzo += min(prezzoTmp, prezzoTmp - risparmioPotenziale + 2 * (v[indexMin] + 1));
    output << numScambi << " " << prezzo;

    return 0;
}
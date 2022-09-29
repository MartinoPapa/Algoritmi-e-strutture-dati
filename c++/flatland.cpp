#include <fstream> // file di testo
#include <iostream>
#include <algorithm>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

const bool Sx = 0;
const bool Dx = 1; // true

// funziona per tutti i casi N=5;
bool *nonRaggiungibili(bool v[], bool triste[], int N)
{
    bool hasAssistman = false;
    int posAssistman = -2;
    bool raggiungibileInverso=true;
    int posAssistInverso=2;
    for (int i = 1; i < N; i++)
    {
        if (hasAssistman)
        {
            triste[i] = false;
        }
        if (v[i])
        {
            // triangolo a destra

            if (posAssistman == i - 1)
            {
                hasAssistman = false;
            }
            else
            {
                hasAssistman = true;
                posAssistman = i;
            }
            if(!raggiungibileInverso){
                break; //da qui in poi tutti possono non essere raggiunti
            } 
            posAssistInverso=2;
            raggiungibileInverso=true;
        }
        else
        {
            // triangolo sinistra
            if(posAssistman == i-posAssistInverso){
                raggiungibileInverso=!raggiungibileInverso;
                posAssistInverso++;
            }
            hasAssistman = false;
        }
    }
    hasAssistman = false;
    posAssistman = -1;
    raggiungibileInverso=true;
    posAssistInverso=2;
    for (int i = N - 2; i >= 0; i--)
    {
        if (hasAssistman)
        {
            triste[i] = false;
        }
        if (!v[i])
        {
            // triangolo a sinistra
            if (posAssistman == i + 1)
            {
                hasAssistman = false;
            }
            else
            {
                hasAssistman = true;
                posAssistman = i;
            }
            if(!raggiungibileInverso) {
                break; //da qui in poi tutti possono non essere raggiunti
            }
            posAssistInverso=2;
            raggiungibileInverso=true;
        }
        else
        {
            // triangolo a destra
            if(posAssistman == i+posAssistInverso){
                raggiungibileInverso=!raggiungibileInverso;
                posAssistInverso++;           
            }
            hasAssistman = false;
        }
    }
    return triste;
}

int main()
{
    int N;
    input >> N;
    bool v[N];
    bool triste[N];
    char c;
    for (int i = 0; i < N; i++)
    {
        if ((N - i) % 2 == 0)
            triste[i] = false;
        else
            triste[i] = true;
        // triste[i]=true;
        input >> c;
        if (c == 's')
            v[i] = Sx;
        else
            v[i] = Dx;
    }

    bool *risultati;
    risultati = nonRaggiungibili(v, triste, N);

    string s = "";
    int numRes = 0;
    for (int i = 0; i < N; i++)
    {
        if (triste[i])
        {
            s.append(to_string(i) + " ");
            numRes++;
        }
    }
    output << numRes << endl;
    output << s;
    cout << numRes << endl;
    cout << s;

    return 0;
}
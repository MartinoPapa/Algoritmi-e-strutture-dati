#include <fstream> // file di testo
#include <iostream>
#include <algorithm>
/*

#include <utility> //pair
#include <algorithm> //sort, struct ...
#include <queue>
#include <stack>
*/

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int **matrice;
int *sommeColonna;

int main()
{
    int R, C; // righe, colonne
    input >> R;
    input >> C;
    matrice = new int *[R];
    sommeColonna = new int[C];

    // popolo la matrice
    for (int i = 0; i < R; i++)
    {
        matrice[i] = new int[C];
        for (int j = 0; j < C; j++)
        {
            input >> matrice[i][j];
        }
    }

    int sumTmp, sum = 0;
    // parto da ogni possibile riga
    for (int i = 0; i < R; i++)
    {
        for (int i = 0; i < C; i++)
        {
            sommeColonna[i] = 0;
        }
        // finisco in ogni possibile riga
        for (int iFinale = i; iFinale < R; iFinale++)
        {
            sumTmp = 0;
            // applico la sottosequenza
            for (int jFinale = 0; jFinale < C; jFinale++)
            {
                sommeColonna[jFinale] += matrice[iFinale][jFinale]; //aggiungo solo l'i-esimo elemento della colonna alla volta, e manteno le somme salvate (risparmiato un for)
                sumTmp += sommeColonna[jFinale];
                if (sumTmp > sum)
                    sum = sumTmp;
                else if (sumTmp < 0)
                    sumTmp = 0;
            }
        }
    }
    output << sum;
    cout << sum;

    return 0;
}
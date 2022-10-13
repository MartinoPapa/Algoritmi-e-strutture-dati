#include <iostream>
#include <fstream> // file di testo
#include "grafi.h"

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int nodi_livello(binary_tree *n, int i)
{
    if (n != NULL)
    {
        return (n->value == i) + nodi_livello(n->left, i + 1) + nodi_livello(n->right, i + 1);
    }
    else
    {
        return 0;
    }
}

int cammino_monotono_stretto(binary_tree *t)
{
    int maxL = 0, maxR = 0;
    if (t != NULL)
    {
        if (t->left != NULL)
        {
            if (t->value < t->left->value)
            {
                maxL = 1 + cammino_monotono_stretto(t->left);
            }
            else
            {
                maxL = max(maxL, cammino_monotono_stretto(t->left));
            }
        }
        if (t->right != NULL)
        {
            if (t->value < t->right->value)
            {
                maxR = 1 + cammino_monotono_stretto(t->right);
            }
            else
            {
                maxR = max(maxR, cammino_monotono_stretto(t->right));
            }
        }
    }
    return max(maxL, maxR);
}

int main()
{
    binary_tree nodo;
    nodo.value = 1;
    binary_tree left;
    left.value = 2;
    binary_tree right;
    right.value = 3;
    nodo.insert_left(&left);
    nodo.insert_right(&right);
    cout << nodo.dfs(IN);
    return 0;
}
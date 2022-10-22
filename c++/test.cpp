#include <iostream>
#include <fstream> // file di testo
#include <algorithm>
#include "grafi.h"

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");


struct binary_tree;
struct binary_tree
{
    binary_tree *parent = NULL, *left = NULL, *right = NULL;
    int value;
    int key;
    binary_tree(int key, int value){
        this->value = value;
        this->key = key;
    }
    void insert_left(binary_tree *nodo)
    {
        if (this->left == NULL)
        {
            left = nodo;
            nodo->parent = this;
        }
    }
    void insert_right(binary_tree *nodo)
    {
        if (this->right == NULL)
        {
            right = nodo;
            nodo->parent = this;
        }
    }
    void delete_left()
    {
        if (this->left != NULL)
        {
            this->left->delete_left();
            this->left->delete_right();
            this->left = NULL;
            delete this->left;
        }
    }
    void delete_right()
    {
        if (this->right != NULL)
        {
            this->right->delete_left();
            this->right->delete_right();
            this->right = NULL;
            delete this->right;
        }
    }
    string dfs(int order = PRE)
    {
        string s = "";
        switch (order)
        {
        case PRE:
            dfs_pre_order_rec(&s);
            break;

        case IN:
            dfs_in_order_rec(&s);
            break;

        case POST:
            dfs_post_order_rec(&s);
            break;

        default:
            break;
        }
        return s;
    }
    void dfs_pre_order_rec(string *s)
    {
        if (this != NULL)
        {
            s->append(to_string(this->key) + " ");
            this->left->dfs_pre_order_rec(s);
            this->right->dfs_pre_order_rec(s);
        }
    }
    void dfs_post_order_rec(string *s)
    {
        if (this != NULL)
        {
            this->left->dfs_pre_order_rec(s);
            this->right->dfs_pre_order_rec(s);
            s->append(to_string(this->key) + " ");
        }
    }
    void dfs_in_order_rec(string *s)
    {
        if (this != NULL)
        {
            this->left->dfs_pre_order_rec(s);
            s->append(to_string(this->key) + " ");
            this->right->dfs_pre_order_rec(s);

        }
    }
    int numero_foglie()
    {
        if (this != NULL)
        {
            if (this->left == NULL && this->right == NULL) return 1;
            else return this->left->numero_foglie() + this->right->numero_foglie();
        }
        return 0;
    }
    int grado_sbilanciamento()
    {
        if (this != NULL)
        {
            int numLeft = this->left->numero_foglie();
            int numRight = this->right->numero_foglie();
            return max({abs(numLeft - numRight), this->right->grado_sbilanciamento(), this->left->grado_sbilanciamento()});
        }
        return 0;
    }
};

struct reserch_tree;
struct reserch_tree:binary_tree{
    public:
    reserch_tree(int key, int value):binary_tree(key, value){};
    //trova il nodo con chiave k
    reserch_tree* lookupNode(int key){
        if(this == NULL || this->key == key) return this;
        else return key<this->key ? ((reserch_tree *) this->left)->lookupNode(key) : ((reserch_tree *)  this->right)->lookupNode(key) ;
    }
    reserch_tree* minimo(){
        reserch_tree *u=this;
        while (u->left != NULL)
        {
            u= (reserch_tree *) u->left;
        }
        return u;
    }
    reserch_tree* massimo(){
        reserch_tree *u=this;
        while (u->right != NULL)
        {
            u= (reserch_tree *) u->right;
        }
        return u;
    }
    reserch_tree* successore(){
        if(this !=NULL){
            //ogni elemento alla sua destra è >= al nodo this e <= ad eventuali nodi posti alla destra del padre di this
            if(this->right != NULL ) return ((reserch_tree *)this->right)->minimo(); 
            else{
                reserch_tree *p = (reserch_tree *) this->parent;
                reserch_tree *t = this;
                while (p!=NULL && t==p->right)
                {
                    t=p;
                    p= (reserch_tree *) p->parent;
                }
                return p;
            }
        }
        return this;
    }
    reserch_tree* predecessore(){
        if(this !=NULL){
            //ogni elemento alla sua destra è >= al nodo this e <= ad eventuali nodi posti alla destra del padre di this
            if(this->left != NULL ) return ((reserch_tree *) this->left)->massimo(); 
            else{
                reserch_tree *p = (reserch_tree *) this->parent;
                reserch_tree *t = this;
                while (p!=NULL && t==p->left)
                {
                    t=p;
                    p=(reserch_tree *) p->parent;
                }
                return p;
            }
        }
        return this;
    }
    static void link(binary_tree *padre, binary_tree *figlio, int key){
        if(figlio != NULL) figlio->parent=padre;  
        if(padre != NULL){
            if(key < padre->key) padre->left=figlio;
            else padre->right=figlio;
        }         
    }
    // va chiamato sulla radice dell'albero, restituisce il nodo aggiunto o modificato
    reserch_tree* insertNode(int key, int value){
        reserch_tree *parent = NULL;
        reserch_tree *u = this;
        while (u!=NULL && u->key != key) //cerco la posizione di inserimento
        {
            parent = u;
            u = (key < u->key) ?  (reserch_tree *) u->left : (reserch_tree *) u->right; //controllo da che parte proseguire la "discesa"
        }
        if(u != NULL && u->key == key){
            u->value = value; //chiave già presente, aggiorno value
        }
        else{
            u = new reserch_tree(key, value); // nuovo nodo
            link(parent,u, key);
            /* non possibile per come è stato scritto
            if(parent == NULL){
                this = nuovo; //primo nodo ad essere inserito
            }*/
        }
        return u;
    }
    //restituisce la radice dell'albero eventualmente modificata
    reserch_tree* removeNode(int key){
        reserch_tree *T = this;
        reserch_tree *u=this->lookupNode(key);
        if(u != NULL){
            if(u->left == NULL && u->right == NULL){ //u foglia
                link(u->parent,NULL,key);
                delete u;
            }
            else if(u->left != NULL && u->right != NULL){ //u ha sia nodi a dx che sx
                reserch_tree *successor = u->successore();
                link(successor->parent,successor->right, successor->key);
                u->key = successor->key;
                u->value = successor->value;
                delete successor;
            }
            else if(u->left != NULL){ //u ha solo il nodo a sinistra, (caso entrambi non nul nell'if precedente)
                link(u->parent,u->left, key); //collego l'elemento a sinistra di u con il parent di u
                
                if(u->parent==NULL){
                    T=(reserch_tree *) u->left; // nuova radice
                }              
                delete u;
            }
            else{ //u ha solo il nodo a destra
                 link(u->parent,u->right, key);
                 if(u->parent == NULL){
                    T=(reserch_tree *) u->right; // nuova radice
                 }
            }
        }
        return T;
    }
};

int main()
{
    reserch_tree *radice = new reserch_tree(4,2);
    radice->insertNode(5,0);
    radice=radice->removeNode(4);
    cout << radice->dfs(IN);
    return 0;
}
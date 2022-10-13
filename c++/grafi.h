using namespace std;

const int PRE = 0;
const int IN = 1;
const int POST = 2;

struct binary_tree;
struct binary_tree
{
    binary_tree *parent = NULL, *left = NULL, *right = NULL;
    int value;
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
            s->append(to_string(this->value) + " ");
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
            s->append(to_string(this->value) + " ");
        }
    }
    void dfs_in_order_rec(string *s)
    {
        if (this != NULL)
        {
            this->left->dfs_pre_order_rec(s);
            s->append(to_string(this->value) + " ");
            this->right->dfs_pre_order_rec(s);
        }
    }
};
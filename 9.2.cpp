/*
#include <iostream>
using namespace std;

struct node
{
    int val;
    node *right;
    node *left;
    node(int val , node *right , node *left){ this->val = val; this->right = right; this->left = left; }
};

class Solution
{
public:
    Solution(int n){ this->n = n;}
    ~Solution();
    void getpre();     //读入前序遍历
    void getin();      //读入后续遍历
    void creat();      //建树
    void postorder();  //输出后续遍历

private:
    node *root = NULL; //根节点
    int* pre   = NULL; //前序遍历
    int* in    = NULL; //中序遍历
    int n            ; //节点数
    node* DFS(int preptr_h , int preptr_t , int inptr_h , int inptr_t);
    void post(node* root);
    void clear(node* root);
};

Solution::~Solution()
{
    clear(root);
}

void Solution::getpre()
{
    pre = new int[n];
    for (int i = 0 ; i < n ; i++)
    {
        cin >> pre[i];
    }
}

void Solution::getin()
{
    in = new int[n];
    for (int i = 0 ; i < n ; i++)
    {
        cin >> in[i];
    }
}

void Solution::creat()
{
    root = DFS( 0 , n , 0 , n ) ;
}

void Solution::postorder()
{
    post(root);
    cout << endl;
}

node* Solution::DFS(int preptr_h, int preptr_t, int inptr_h, int inptr_t)
{
    if (preptr_h == preptr_t or inptr_h == inptr_t)
        return NULL;
    int val = pre[preptr_h];
    int i;
    for( i = inptr_h ; i < inptr_t; ++i)
    {
        if (in[i] == val)
            break;
    }
    node *left = DFS(preptr_h + 1 , i - inptr_h + preptr_h + 1 , inptr_h , i);
    node *right = DFS(i - inptr_h + preptr_h + 1 , preptr_t , i + 1, inptr_t);
    node *thenode = new node(val , right , left);
    return thenode;
}

void Solution::post(node* root)
{
    if (root != NULL)
    {
        post(root->left);
        post(root->right);
        cout << root->val << " ";
    }
}

void Solution::clear(node* root)
{
    if (root != NULL)
    {
        clear(root->left);
        clear(root->right);
        delete root;
    }
}

int main()
{
    int n;
    cin >> n;
    Solution ans(n);
    ans.getpre();
    ans.getin();
    ans.creat();
    ans.postorder();
    return 0;
}
*/
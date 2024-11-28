/*
#include<iostream>
using namespace std;

template<class T>
class BSTree
{
public:
    BSTree();
    ~BSTree();
    void insert(const T&);              //插入
    void removeByKey(const T&);         //按值删除
    void removeByIndex(int);            //按名次删除
    void searchByKey(const T&) const;   //按值查找
    void searchByIndex(int) const; //按名次查找
    void display() const;
private:
    struct Node
    {
        T data;
        int index;
        Node *left;
        Node *right;
        Node(const T& data, int index, Node *left = NULL, Node *right = NULL) {this->data = data; this->index = index; this->left = left; this->right = right;};
    };
    Node *root;
    void clear(Node *theRoot);
    void show(Node *theRoot) const;
    void deleteNode(Node *theRoot, Node *father);
    void substract(Node *theRoot); //从根到该节点名次减一
    void add(const T& val);
};

template <class T>
BSTree<T>::BSTree()
{
    root = NULL;
}

template <class T>
BSTree<T>::~BSTree()
{
    clear(root);
}

template <class T>
void BSTree<T>::clear(Node *theRoot)
{
    if (theRoot == NULL)
        return;
    clear(theRoot->left);
    clear(theRoot->right);
    delete theRoot;
}

template <class T>
void BSTree<T>::insert(const T& val)
{
    if (root == NULL)
    {
        root = new Node(val,0,NULL,NULL);
        cout<<0<<endl;
        return;
    }
    Node *temp = root;
    int ans = 0;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            cout<<0<<endl;
            return;
        }
        if (temp->data > val)
        {
            ans ^= temp->data;
            if (temp->left != NULL)
            {
                temp = temp->left;
            }else
            {
                temp->left = new Node(val,0,NULL,NULL);
                add(val);
                cout<<ans<<endl;
                return;
            }
        }else
        {
            ans ^= temp->data;
            if (temp->right != NULL)
            {
                temp = temp->right;
            }else
            {
                temp->right = new Node(val,0,NULL,NULL);
                add(val);
                cout<<ans<<endl;
                return;
            }
        }
    }
}

template <class T>
void BSTree<T>::searchByKey(const T& val) const
{
    if (root == NULL)
    {
        cout<<0<<endl;
        return;
    }
    int ans = val;
    Node *temp = root;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            cout<<ans<<endl;
            return;
        }
        if (temp->data > val)
        {
            ans ^= temp->data;
            temp = temp->left;
        }else
        {
            ans ^= temp->data;
            temp = temp->right;
        }
    }
    cout<<0<<endl;
}

template <class T>
void BSTree<T>::searchByIndex(int index) const
{
    int ind = 0;
    index -=1;
    Node *temp = root;
    int ans = 0;
    while (temp != NULL)
    {
        ans ^= temp->data;
        if (temp->index + ind == index)
        {
            cout<<ans<<endl;
            return;
        }
        if (temp->index + ind > index)
        {
            temp = temp->left;
        }else
        {
            ind += temp->index + 1;
            temp = temp->right;
        }
    }
    cout<<0<<endl;
}

template <class T>
void BSTree<T>::display() const
{
    show(root);
    cout<<endl;
}

template <class T>
void BSTree<T>::show(Node* theRoot) const
{
    if (theRoot == NULL)
        return;
    show(theRoot->left);
    cout<<"val:"<<theRoot->data<<"index:"<<theRoot->index<<" ";
    show(theRoot->right);
}

template <class T>
void BSTree<T>::removeByKey(const T& val)
{
    if (root == NULL)
    {
        cout<<0<<endl;
        return;
    }
    int ans = val;
    Node *temp = root;
    Node *prev = NULL;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            cout<<ans<<endl;
            substract(prev);
            deleteNode(temp, prev);
            return;
        }
        if (temp->data > val)
        {
            ans ^= temp->data;
            prev = temp;
            temp = temp->left;
        }else
        {
            ans ^= temp->data;
            prev = temp;
            temp = temp->right;
        }
    }
    cout<<0<<endl;
}

template <class T>
void BSTree<T>::removeByIndex(int index)
{
    int ind = 0;
    index -=1;
    Node *temp = root;
    Node *prev = NULL;
    int ans = 0;
    while (temp != NULL)
    {
        ans ^= temp->data;
        if (temp->index + ind == index)
        {
            substract(prev);
            deleteNode(temp, prev);
            cout<<ans<<endl;
            return;
        }
        if (temp->index + ind > index)
        {
            prev = temp;
            temp = temp->left;
        }else
        {
            ind += temp->index + 1;
            prev = temp;
            temp = temp->right;
        }
    }
    cout<<0<<endl;
}

template <class T>
void BSTree<T>::deleteNode(Node* theRoot, Node *father)
{
    if (theRoot->left == NULL && theRoot->right == NULL)
    {
        if (father != NULL)
        {
            if (father->left == theRoot)
            {
                father->left = NULL;
                father->index -= 1;
            }else
                father->right = NULL;
        }else
            root = NULL;
        delete theRoot;
        return;
    }
    if (theRoot->left == NULL && theRoot->right != NULL)
    {
        if (father != NULL)
        {
            if (father->left == theRoot)
            {
                father->left = theRoot->right;
                father->index -= 1;
            }else
                father->right = theRoot->right;
        }else
            root = theRoot->right;
        delete theRoot;
        return;
    }
    if (theRoot->right == NULL && theRoot->left != NULL)
    {
        if (father != NULL)
        {
            if (father->left == theRoot)
            {
                father->left = theRoot->left;
                father->index -= 1;
            }else
                father->right = theRoot->left;
        }else
            root = theRoot->left;
        delete theRoot;
        return;
    }

    if (father != NULL && father->left == theRoot)
        father->index -= 1;
    Node *prev = theRoot;
    Node *temp = theRoot->right;
    if (temp->left == NULL)
    {
        theRoot->data = temp->data;
        deleteNode(temp, prev);
        return;
    }
    prev = temp;
    temp = temp->left;
    while (temp->left != NULL)
    {
        prev->index -= 1;
        prev = temp;
        temp = temp->left;
    }
    theRoot->data = temp->data;
    deleteNode(temp, prev);
}

template <class T>
void BSTree<T>::substract(Node* theRoot)
{
    if (theRoot == NULL)
        return;
    Node *temp = root;
    while (temp != NULL)
    {
        if (temp == theRoot)
        {
            return;
        }
        if (temp->data > theRoot->data)
        {
            temp->index -= 1;
            temp = temp->left;
        }else
        {
            temp = temp->right;
        }
    }
}

template <class T>
void BSTree<T>::add(const T& val)
{
    Node *temp = root;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            return;
        }
        if (temp->data > val)
        {
            temp->index += 1;
            temp = temp->left;
        }else
        {
            temp = temp->right;
        }
    }
}


int main()
{
    int m;
    cin>>m;
    int a, b;
    BSTree<int> tree;
    while (m--)
    {
        cin>>a;
        cin>>b;
        switch (a)
        {
            case 0:
                {
                    tree.insert(b);
                }break;
            case 1:
                {
                    tree.searchByKey(b);
                }break;
            case 2:
                {
                    tree.removeByKey(b);
                }break;
            case 3:
                {
                    tree.searchByIndex(b);
                }break;
            case 4:
                {
                    tree.removeByIndex(b);
                }break;
            default:
                break;
        }
        //tree.display();
    }
}
*/
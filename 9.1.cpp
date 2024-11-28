/*
#include<iostream>
using namespace std;

template<class T>
class Queue;

template<class T>
class stack;

struct IntNode
{
    int val;
    IntNode* right;
    IntNode* left;
    IntNode(){right = NULL;left = NULL;val = -1;};
    IntNode(int _val){right = NULL;left = NULL;val = _val;};
    IntNode(int val , IntNode* right , IntNode* left);
};

IntNode::IntNode(int val, IntNode* right, IntNode* left)
{
    this->val = val;
    this->right = right;
    this->left = left;
}

template <class T , class Node>
class BinaryTree
{
public:
    BinaryTree();
    virtual ~BinaryTree();

    virtual int Size(int size);

    int PreTraverse();                                                              //前序遍历
    int InTraverse();                                                               //中序遍历
    int PostTraverse();                                                             //后序遍历
    int HiTraverse();                                                               //层次遍历

    virtual int figureNode();                                                       //计算节点数目
    virtual int figureDeep();                                                       //计算高度
    virtual int getNode(Node*& node);                                               //获取节点数
    virtual int getDeep(Node*& node);                                               //获取高度
    virtual int getNode(const T& node);                                             //获取节点数
    virtual int getDeep(const T& node);                                             //获取高度

    virtual  int insert(const T& val , const T& left , const T& right);             //单个插入
    virtual  int create_tree(const T& rootNode);                                    //建树

private:
    Node* root;
    Node** nodeList;
    int* deep;                                                                      //深度
    int* nums;                                                                      //节点数目
    int size;

    void pre(Node* node);                                                           //前序遍历递归函数
    void in(Node* node);                                                            //中序遍历函数
    void post(Node* node);                                                          //后序遍历函数

    int figureN(Node* node);                                                        //计算节点数递归函数
    int figureD(Node* node);                                                        //计算节点深度递归
};

template <class T, class Node>
BinaryTree<T, Node>::BinaryTree()
{
    root = NULL;
    nodeList = NULL;
    deep = NULL;
    nums = NULL;
    size = 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::Size(int size)
{
    this->size = size;
    nodeList = new Node*[size];
    for (int i = 0; i < size; i++)
    {
        nodeList[i] = new Node(i + 1);
    }
    deep = new int[size];
    for (int i = 0; i < size; i++)
    {
        deep[i] = 0;
    }
    nums = new int[size];
    for (int i = 0; i < size; i++)
    {
        nums[i] = 0;
    }
    return 0;
}

template <class T, class Node>
BinaryTree<T, Node>::~BinaryTree()
{
    Queue<Node*> clear;
    clear.push(root);
    while (!clear.empty())
    {
        if (clear.front()->right != NULL)
            clear.push(clear.front()->right);
        if (clear.front()->left != NULL)
            clear.push(clear.front()->left);
        delete clear.front();
        clear.pop();
    }
    delete[] nodeList;
    delete[] deep;
    delete[] nums;
}

template <class T, class Node>
int BinaryTree<T, Node>::PreTraverse()
{
    pre(root);
    cout << endl;
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::InTraverse()
{
    in(root);
    cout << endl;
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::PostTraverse()
{
    post(root);
    cout << endl;
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::HiTraverse()
{
    Queue<Node*> residue;
    residue.push(root);
    while (!residue.empty())
    {
        if (residue.front()->left != NULL)
            residue.push(residue.front()->left);
        if (residue.front()->right != NULL)
            residue.push(residue.front()->right);
        cout << residue.front()->val << " ";
        residue.pop();
    }
    cout << endl;
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::figureNode()
{
    figureN(root);
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::figureDeep()
{
    figureD(root);
    return 0;
}

template <class T, class Node>
int BinaryTree<T, Node>::getNode(Node*& node)
{
    return nums[node->val - 1];
}

template <class T, class Node>
int BinaryTree<T, Node>::getDeep(Node*& node)
{
    return deep[node->val - 1];
}

template <class T, class Node>
int BinaryTree<T, Node>::getNode(const T& node)
{
    return nums[node - 1];
}

template <class T, class Node>
int BinaryTree<T, Node>::getDeep(const T& node)
{
    return deep[node - 1];
}


template <class T, class Node>
int BinaryTree<T, Node>::insert(const T& val, const T& left, const T& right)
{
    if (left != -1)
        nodeList[val - 1]->left = nodeList[left - 1];
    if (right != -1)
        nodeList[val - 1]->right = nodeList[right - 1];
    return 0;
}


template <class T, class Node>
int BinaryTree<T, Node>::create_tree(const T& rootNode)
{
    root = nodeList[rootNode - 1];
    return 0;
}

template <class T, class Node>
void BinaryTree<T, Node>::pre(Node* node)
{
    if (node != NULL)
    {
        cout << node->val << " ";
        pre(node->left);
        pre(node->right);
    }
}

template <class T, class Node>
void BinaryTree<T, Node>::in(Node* node)
{
    stack<Node*> p;
    while (node != NULL || !p.empty())
    {
        if (node != NULL)
        {
            p.push(node);
            node = node->left;
        }else
        {
            cout << p.top()->val << " ";
            node = p.top()->right;
            p.pop();
        }
    }
}

template <class T, class Node>
void BinaryTree<T, Node>::post(Node* node)
{
    stack<Node*> p;
    Node* prev = NULL;
    while (node != NULL || !p.empty())
    {
        if (node != NULL)
        {
            p.push(node);
            node = node->left;
        }else
        {
            node = p.top();
            if (node->right == NULL || node->right == prev)
            {
                cout << node->val << " ";
                prev = node;
                p.pop();
                node = NULL;
            }else
            {
                node = node->right;
            }

        }
    }
}

template <class T, class Node>
int BinaryTree<T, Node>::figureN(Node* node)
{
    if (node == NULL)
        return 0;
    int result = 0;
    result = figureN(node->left) + figureN(node->right) + 1;
    nums[node->val - 1] = result;
    return result;
}

template <class T, class Node>
int BinaryTree<T, Node>::figureD(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }
    int result = 0;
    int l , r;
    l = figureD(node->left);
    r = figureD(node->right);
    result = (l > r ? l : r) + 1;
    deep[node->val - 1] = result;
    return result;
}


template<class T>
class Queue
{
public:
    explicit Queue(int cap = 2);
    Queue(Queue& other);
    ~Queue();
    T& front(); //获取队首元素
    T& back();  //获取队尾元素
    [[nodiscard]] int size() const; //获取队长
    [[nodiscard]] bool empty() const;  //判断空队
    void pop(); //删除队首元素
    void push(const T& item);  //入队
    void print() const; //打印
private:
    void large();   //容量加倍
    int capacity;   //容量
    int len;    //队长
    int head;   //队首指针
    int tail;   //队尾指针
    T* data;    //存放数组
};

template <class T>
Queue<T>::Queue(int cap)
{
    capacity = cap;
    data = new T[capacity];
    len = head = tail = 0;
}

template <class T>
Queue<T>::Queue(Queue& other)
{
    capacity = other.capacity;
    data = new T[capacity];
    len = other.len;
    head = other.head;
    tail = other.tail;
    for (int i = 0; i < capacity; i++)
        data[i] = other.data[i];
}


template <class T>
Queue<T>::~Queue()
{
    delete[] data;
}

template <class T>
T& Queue<T>::front()
{
    return data[head % capacity];
}

template <class T>
T& Queue<T>::back()
{
    return data[(tail + capacity - 1) % capacity];
}

template <class T>
int Queue<T>::size() const
{
    return len;
}

template <class T>
bool Queue<T>::empty() const
{
    return len == 0;
}

template <class T>
void Queue<T>::pop()
{
    if (len == 0)
        return;
    head = (head + 1) % capacity;
    --len;
}

template <class T>
void Queue<T>::push(const T& item)
{
    if (len + 1 == capacity)
    {
        large();
    }
    data[tail] = item;
    tail = (tail + 1) % capacity;
    ++len;
}

template <class T>
void Queue<T>::print() const
{
    int h = head;
    while (h != tail)
    {
        cout << data[h % capacity] << " ";
        h = (h + 1) % capacity;
    }
    cout << endl;
}

template <class T>
void Queue<T>::large()
{
    T* newDate = new T[capacity * 2];
    int f = head;
    for (int i = 0; i < len; i++ , f++)
    {
        newDate[i] = data[f % capacity];
    }
    delete[] data;
    data = newDate;
    head = 0;
    tail = len;
    capacity *= 2;
}

template<class T>
class stack
{
public:
    stack();
    ~stack(){delete []data;};
    T& top();
    void push(T);
    void pop();
    bool empty(){return tail == 0;};
    void display();
private:
    int size;
    T* data;
    int tail;
};

template <class T>
void stack<T>::display()
{
    for(int i = 0;i<tail;i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

template <class T>
stack<T>::stack()
{
    tail = 0;
    size = 1;
    data = new T[size];
}

template <class T>
T& stack<T>::top()
{
    if (tail == 0)
        throw  1;
    return data[tail - 1];
}

template <class T>
void stack<T>::push(T val)
{
    if (tail == size)
    {
        T* temp = new T[size*2];
        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        delete [] data;
        data = temp;
        size *= 2;
    }
    data[tail] = val;
    tail++;
}

template <class T>
void stack<T>::pop()
{
    if (tail == 0)
    {
        return;
    }
    tail -= 1;

}

double figure(string str)
{
    double sum = -1;
    stack<double> num;  //数字栈
    stack<int> op;      //操作栈
    double front;
    double back;
    int ope;
    double ans;
    char pre = '(';
    bool flag_f = false;
    bool flag = false;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            op.push(-1);
        }
        else if (str[i] == ')')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            ans = 0;
            while(true)
            {
                back = num.top();
                num.pop();
                ope = op.top();
                op.pop();
                if (ope == -1)
                {
                    num.push(ans + back);
                    break;
                }
                switch (ope)
                {
                    case 1:
                        ans += back;
                        break;
                    case 2:
                        ans -= back;
                        break;
                    case 3:
                        front = num.top();
                        num.pop();
                        num.push(front * back);
                        break;
                    case 4:
                        front = num.top();
                        num.pop();
                        num.push(front / back);
                        break;
                    default:
                        break;
                }
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
        }else if (str[i] == '+')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(1);
        }else if (str[i] == '-')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if(pre == '(')
            {
                flag_f = true;
                pre = str[i];
                continue;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(2);
        }else if (str[i] == '*')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(3);
        }else if (str[i] == '/')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(4);
        }else
        {
            if (sum != -1)
            {
                sum = sum * 10 + str[i] - '0';
            }else
            {
                sum = str[i] - '0';
            }
        }
        if (flag == true)
        {
            if (ope == 3)
            {
                num.push(front * back);
            }
            else if (ope == 4)
            {
                num.push(front / back);
            }
            flag = false;
        }
        pre = str[i];
    }
    if(sum != -1)
    {
        if (flag_f)
        {
            sum = 0 - sum;
            flag_f = false;
        }
        num.push(sum);
    }
    ans = 0;
    while(not op.empty())
    {
        back = num.top();
        num.pop();
        ope = op.top();
        op.pop();
        switch (ope)
        {
        case 1:
            ans += back;
            break;
        case 2:
            ans -= back;
            break;
        case 3:
            front = num.top();
            num.pop();
            num.push(front * back);
            break;
        case 4:
            front = num.top();
            num.pop();
            num.push(front / back);
            break;
        default:
            break;
        }
    }
    return ans + num.top();
}

int main()
{
    int n;
    int l , r;
    cin >> n;
    BinaryTree<int , IntNode> tree;
    tree.Size(n);
    for (int i = 1 ; i <= n ; ++i)
    {
        cin >> l;
        cin >> r;
        tree.insert(i , l , r);
    }
    tree.create_tree(1);
    tree.PreTraverse();
    tree.InTraverse();
    tree.PostTraverse();
    tree.HiTraverse();
    tree.figureNode();
    tree.figureDeep();
    for (int i = 1 ; i <= n ; ++i)
    {
        cout << tree.getNode(i) << " ";
    }
    cout << endl;

    for (int i = 1 ; i <= n ; ++i)
    {
        cout << tree.getDeep(i) << " ";
    }
    cout << endl;
    return 0;
}
*/
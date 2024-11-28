/*
#include <iostream>
using namespace std;

class HuffmanTree;

template<class T>
class MinHeap
{
public:
    explicit MinHeap(int cap = 10);
    ~MinHeap();
    void insert(const T& value);
    void remove();
    T& getMin();
    bool empty() const { return size == 0; };
private:

    T* data;
    int size;
    int capacity;
};

class HuffmanNode
{
friend class MinHeap<HuffmanNode>;
friend class HuffmanTree;
public:
    HuffmanNode(int weight , char c);
    bool small(const HuffmanNode &node) const;
private:
    int weight;
    char c;
    HuffmanNode *left;
    HuffmanNode *right;
};

class HuffmanTree
{
public:
    explicit HuffmanTree(const string& file);
    ~HuffmanTree();
    [[nodiscard]] string getHuffmanCode() const { return huffmanCode;};    //获取编码
    [[nodiscard]] int getHuffmanCodeLength() const { return static_cast<int>(huffmanCode.size());}; //获取长度
    void code();
private:
    int *weight = new int[26];
    string file = "";
    string huffmanCode = "";
    string *huffmanCodeSingle = new string[26];
    HuffmanNode *root = NULL;
    void clean(const HuffmanNode *root);
    void MakeHuffmanTree(); //建树
    void MakeHuffmanCode(); //编码
    void find(); //找出单个字符编码
    void DFSFind(const HuffmanNode *theRoot , const string& front); //找字符编码的递归函数

};

HuffmanNode::HuffmanNode(int weight, char c)
{
    this->weight = weight;
    this->c = c;
    this->left = NULL;
    this->right = NULL;
}

bool HuffmanNode::small(const HuffmanNode &node) const
{
    return this->weight < node.weight;
}

HuffmanTree::HuffmanTree(const string& file)
{
    this->file = file;
    for (int i = 0; i < 26; i++)
    {
        weight[i] = 0;
    }

    for(char &c : this->file)
    {
        ++weight[c - 'a'];
    }
    MakeHuffmanTree();
    MakeHuffmanCode();
}

HuffmanTree::~HuffmanTree()
{
    delete[] weight;
    clean(root);
}


void HuffmanTree::clean(const HuffmanNode *root)
{
    if(root == NULL)
        return;
    clean(root->left);
    clean(root->right);
    delete root;
}

void HuffmanTree::MakeHuffmanTree()
{
    MinHeap<HuffmanNode*> heap(30);
    for (int i = 0; i < 26; i++)
    {
        if(weight[i] != 0)
        {
            HuffmanNode *node = new HuffmanNode(weight[i], static_cast<char>(i + 'a'));
            heap.insert(node);
        }
    }
    while(!heap.empty())   //取两个最小树
    {
        HuffmanNode *left = heap.getMin();
        heap.remove();
        if(heap.empty())
        {
            root = left;
            break;
        }
        HuffmanNode *right = heap.getMin();
        heap.remove();
        HuffmanNode *node = new HuffmanNode(left->weight + right->weight, static_cast<char>(0));
        node->left = left;
        node->right = right;
        heap.insert(node);
    }
}

void HuffmanTree::MakeHuffmanCode()
{
    find();
    for(char &c : file)
    {
        huffmanCode += huffmanCodeSingle[c - 'a'];
    }
}

void HuffmanTree::find()
{
    DFSFind(root , "");
}

void HuffmanTree::DFSFind(const HuffmanNode* theRoot , const string& front)
{
    if(theRoot == NULL)
        return;
    if(theRoot->left == NULL && theRoot->right == NULL)
    {
        huffmanCodeSingle[theRoot->c - 'a'] = front;
        return;
    }
    DFSFind(theRoot->left, front + '0');
    DFSFind(theRoot->right, front + '1');
}

void HuffmanTree::code()
{
    for(int count = 0 ; count < 26 ; ++count)
    {
        cout << static_cast<char>(count + 'a') << ' ';
        cout << huffmanCodeSingle[count] << ' ';
    }
    cout << endl;
}


template <class T>
MinHeap<T>::MinHeap(int cap)
{
    size = 0;
    capacity = cap;
    data = new T[capacity + 1];
    data[0] = NULL;
}

template <class T>
MinHeap<T>::~MinHeap()
{
    delete[] data;
}

template <class T>
void MinHeap<T>::insert(const T& value)
{
    if (size == capacity)
    {
        capacity *= 2;
        T* newData = new T[capacity + 1];
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    data[size + 1] = value;
    size++;
    int parent = size;
    while (parent > 1)
    {
        parent = parent / 2;
        int leftChild = 2 * parent;
        int rightChild = leftChild + 1;
        int smallest = rightChild;
        if (rightChild > size || data[leftChild]->small(*data[rightChild]))
            smallest = leftChild;
        if (data[smallest]->small(*data[parent]))
        {
            T temp = data[parent];
            data[parent] = data[smallest];
            data[smallest] = temp;
        }
        else
            break;
    }
}

template <class T>
void MinHeap<T>::remove()
{
    if (size == 0)
        return;
    data[1] = data[size];
    --size;
    int parent = 1;
    while(parent * 2 <= size)
    {
        int leftChild = 2 * parent;
        int rightChild = leftChild + 1;
        int smallest = rightChild;
        if (rightChild > size || data[leftChild]->small(*data[rightChild]))
            smallest = leftChild;
        if (data[smallest]->small(*data[parent]))
        {
            T temp = data[parent];
            data[parent] = data[smallest];
            data[smallest] = temp;
        }
        else
            break;

        parent = smallest;
    }
}

template <class T>
T& MinHeap<T>::getMin()
{
    return data[1];
}


int main()
{
    string file;
    cin >> file;
    HuffmanTree tree(file);
    cout << tree.getHuffmanCodeLength() << endl;
}
*/
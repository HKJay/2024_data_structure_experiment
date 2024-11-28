/*
#include <iostream>
using namespace std;

template<class T>
class MinHeap
{
public:
    MinHeap(int cap = 10);
    ~MinHeap();
    void create(int n);
    void insert(T& value);
    void remove();
    void sort(int n);
    T& getMin();
    void display();
private:
    T* data;
    int size;
    int capacity;
};

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
void MinHeap<T>::create(int n)
{
    delete[] data;
    size = n;
    capacity = n;
    data = new T[capacity + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> data[i];
    }
    int parent = size / 2;          //找到第一个有孩子的节点
    while (parent >= 1)             //初始化
    {
        int node = parent;
        while(node * 2 <= size)
        {
            int leftChild = node * 2;
            int rightChild = leftChild + 1;
            int smallest = rightChild;
            if (rightChild > size || data[leftChild] < data[rightChild])
                smallest = leftChild;
            if (data[node] > data[smallest])
            {
                T temp = data[node];
                data[node] = data[smallest];
                data[smallest] = temp;
            }
            else
                break;
            node = smallest;
        }
        --parent;
    }
}


template <class T>
void MinHeap<T>::insert(T& value)
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
    while (parent > 1)  //自底向上检查
    {
        parent = parent / 2;
        int leftChild = 2 * parent;
        int rightChild = leftChild + 1;
        int smallest = rightChild;
        if (rightChild > size || data[leftChild] < data[rightChild])
            smallest = leftChild;
        if (data[parent] > data[smallest])
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
    while(parent * 2 <= size)  //自顶向下检查
    {
        int leftChild = 2 * parent;
        int rightChild = leftChild + 1;
        int smallest = rightChild;
        if (rightChild > size || data[leftChild] < data[rightChild])
            smallest = leftChild;
        if (data[parent] > data[smallest])
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
void MinHeap<T>::sort(int n)
{
    delete[] data;
    size = n;
    capacity = n;
    data = new T[capacity + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> data[i];
    }
    int parent = size / 2;
    while (parent >= 1)             //初始化
    {
        int node = parent;
        while(node * 2 <= size)
        {
            int leftChild = node * 2;
            int rightChild = leftChild + 1;
            int smallest = rightChild;
            if (rightChild > size || data[leftChild] < data[rightChild])
                smallest = leftChild;
            if (data[node] > data[smallest])
            {
                T temp = data[node];
                data[node] = data[smallest];
                data[smallest] = temp;
            }
            else
                break;
            node = smallest;
        }
        --parent;
    }
    for (int i = 1; i <= n; i++)      //输出
    {
        cout << getMin() << " ";
        remove();
    }
    cout << endl;
}

template <class T>
T& MinHeap<T>::getMin()
{
    return data[1];
}

template <class T>
void MinHeap<T>::display()
{
    for (int i = 1; i <= size; i++)
        cout << data[i] << " ";
    cout << endl;
}


int main()
{
    MinHeap<int> min(10);
    int n , m , op , num;
    cin >> n;
    min.create(n);
    cout<<min.getMin()<<endl;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        switch (op)
        {
            case 1:
                cin >> num;
                min.insert(num);
                //min.display();
                cout << min.getMin() << endl;
                break;
            case 2:
                min.remove();
                //min.display();
                cout << min.getMin() << endl;
                break;
            case 3:
                cin >> n;
                min.sort(n);
                break;
            default:
                break;
        }
    }

}
*/
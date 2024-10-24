/*
#include<iostream>
using namespace std;

template<class T>
class Queue
{
public:
    explicit Queue(int cap = 2);
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

int main()
{
    int n;
    cin >> n;
    Queue<int> ans;
    for (int i = 1; i <= n; i++)
    {
        ans.push(i);
    }
    while(ans.size() != 1)
    {
        ans.pop();
        ans.push(ans.front());
        ans.pop();
    }
    cout << ans.front() << endl;
    return 0;
}
*/
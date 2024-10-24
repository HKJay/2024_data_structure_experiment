#include <iostream>
using namespace std;

template<class T>
struct single
{
    single<T>* next;
    T data;
    single(const T& val){data = val;next = NULL;};
    single(const T& val , single<T>* next){data = val ; this->next = next;};
};

template<class T>
class chain
{
public:
    chain(){head = NULL; size = 0;};
    chain(const chain<T>& list);
    ~chain();

    class iterator  //迭代器
    {
    public:
        iterator(single<T>* TheNode = NULL){node = TheNode;};
        T& operator*(){return node->data;};
        T* operator->(){return &node->data;};

        iterator& operator++(){node = node->next; return *this;};
        bool operator==(const iterator& it){return node == it.node;};
        bool operator!=(const iterator& it){return node != it.node;};
    private:
        single<T>* node;
    };
    iterator begin(){return iterator(head);};
    iterator end(){return iterator(NULL);};

    void insert(const T& val , int index);  //指定位置插入
    void push_back(const T& val);   //末尾插入
    int remove(const T& val);  //删除指定元素
    int search(const T& val);  //查找元素
    void reverse(); //原地逆置
    int display(); //输出
private:
    single<T>* head;
    int size;
};

template <class T>
chain<T>::chain(const chain<T>& list)
{
    if (list.size = 0)
    {
        head = NULL;
        size = 0;
        return;
    }
    head = new single<T>(list.head->data);
    single<T>* temp = list.head->next;
    single<T>* temp2 = head;
    while (temp != NULL)
    {
        temp2->next = new single<T>(temp->data);
        temp2 = temp2->next;
        temp = temp->next;
    }
    temp2->next = NULL;
}

template <class T>
chain<T>::~chain()
{
    single<T>* temp = head;
    while (temp != NULL)
    {
        single<T>* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
}

template <class T>
void chain<T>::insert(const T& val, int index)
{
    if(index == 0)
    {
        single<T>* temp = new single<T>(val);
        temp->next = head;
        head = temp;
        return;
    }

    single<T>* temp = head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    single<T>* temp2 = temp->next;
    temp->next = new single<T>(val,temp2);
}

template <class T>
void chain<T>::push_back(const T& val)
{
    single<T>* temp = head;
    if (head == NULL)
    {
        head = new single<T>(val);
        return;
    }
    for (; temp->next != NULL; temp = temp->next){}
    temp->next = new single<T>(val,NULL);
    ++size;
}

template <class T>
int chain<T>::remove(const T& val)
{
    if (head->data == val)
    {
        single<T>* temp = head;
        head = head->next;
        delete temp;
        --size;
        return size;
    }
    single<T>* temp = head;
    for(;temp->next != NULL && temp->next->data != val ; temp = temp->next){}
    if(temp->next == NULL)
    {
        return -1;
    }

    single<T>* temp2 = temp->next;
    temp->next = temp->next->next;
    delete temp2;
    --size;
    return size;
}

template <class T>
int chain<T>::search(const T& val)
{
    single<T>* temp = head;
    for (int i = 0; temp != NULL; temp = temp->next , ++i)
    {
        if(temp->data == val) return i;
    }
    return -1;
}

template <class T>
void chain<T>::reverse()
{
    if(size == 0 || size == 1) return;
    single<T>* pre = head;
    single<T>* tail = head->next;
    pre->next = NULL;
    while(tail->next != NULL)
    {
        single<T>* temp = tail->next;
        tail->next = pre;
        pre = tail;
        tail = temp;
    }
    tail->next = pre;
    head = tail;
}

template <class T>
int chain<T>::display()
{
    iterator start = begin();
    int ans = 0;
    for(int i = 0 ; start != end(); ++start, ++i)
    {
        ans += i ^ (*start);
    }
    return ans;
}

template<class T>
class my_hash_map //链表散列
{
    public:

};
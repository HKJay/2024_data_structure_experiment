/*
#include <iostream>
using namespace std;

template<class T>
class chain;

template<class T>
class my_hash_map;

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
    friend class my_hash_map<T>;
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
    void display(); //输出
    int length(); //长度
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
        ++size;
        return;
    }

    single<T>* temp = head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    single<T>* temp2 = temp->next;
    temp->next = new single<T>(val,temp2);
    ++size;
}

template <class T>
void chain<T>::push_back(const T& val)
{
    single<T>* temp = head;
    if (head == NULL)
    {
        head = new single<T>(val);
        ++size;
        return;
    }
    for (; temp->next != NULL; temp = temp->next){}
    temp->next = new single<T>(val,NULL);
    ++size;
}

template <class T>
int chain<T>::remove(const T& val)
{
    if (head == NULL)
        return -1;
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
void chain<T>::display()
{
    iterator start = begin();
    int ans = 0;
    for(int i = 0 ; start != end(); ++start, ++i)
    {
        cout << *start << ' ';
    }
    cout << endl;
}

template <class T>
int chain<T>::length()
{
    return size;
}


template<class T>
class my_hash_map //链表散列
{
public:
    my_hash_map(int D);
    ~my_hash_map();
    int insert(T& val);
    int search(T& val);
    int remove(T& val);
    void print();
private:
    int D;
    chain<T>** table;
};

template <class T>
my_hash_map<T>::my_hash_map(int D)
{
    this->D = D;
    table = new chain<T>*[D];
    for (int i = 0; i < D; i++)
    {
        table[i] = NULL;
    }
}

template <class T>
my_hash_map<T>::~my_hash_map()
{
    for (int i = 0; i < D; i++)
    {
        if (table[i] != NULL)
        {
            delete table[i];
        }
    }
    delete []table;
}

template <class T>
int my_hash_map<T>::insert(T& val)
{
    if(table[val % D] == NULL)
    {
        table[val % D] = new chain<T>();
    }
    if(table[val % D]->search(val) == -1)
    {
        single<T>* temp = table[val % D]->head;
        if (table[val % D]->head == NULL)
        {
            table[val % D]->head = new single<T>(val);
            ++table[val % D]->size;
            return 1;
        }
        for (; temp->next != NULL; temp = temp->next){}
        temp->next = new single<T>(val,NULL);
        ++table[val % D]->size;
        return 1;
    }
    return -1;
}

template <class T>
int my_hash_map<T>::search(T& val)
{
    int s = -1;
    if(table[val % D] == NULL)
        return -1;
    single<T>* temp = table[val % D]->head;
    for (int i = 0; temp != NULL; temp = temp->next , ++i)
    {
        if(temp->data == val)
        {
            s = i;
            break;
        }
    }
    if(s == -1)
    {
        return -1;
    }
    return table[val % D]->size;
}

template <class T>
int my_hash_map<T>::remove(T& val)
{
    if (table[val % D] == NULL)
        return -1;
    if (table[val % D]->head == NULL)
        return -1;
    if (table[val % D]->head->data == val)
    {
        single<T>* temp = table[val % D]->head;
        table[val % D]->head = table[val % D]->head->next;
        delete temp;
        --table[val % D]->size;
        return table[val % D]->size;
    }
    single<T>* temp = table[val % D]->head;
    for(;temp->next != NULL && temp->next->data != val ; temp = temp->next){}
    if(temp->next == NULL)
    {
        return -1;
    }

    single<T>* temp2 = temp->next;
    temp->next = temp->next->next;
    delete temp2;
    --table[val % D]->size;
    return table[val % D]->size;
}

template <class T>
void my_hash_map<T>::print()
{
    for (int i = 0; i < D; i++)
    {
        if(table[i] != NULL)
        {
            table[i]->display();
        }else
        {
            cout<<"NULL"<<endl;
        }
    }
}

int main()
{
    int m , D , opt , x;
    int len;
    cin>>D;
    cin>>m;
    my_hash_map<int> ans(D);
    for (int i = 0; i < m; i++)
    {
        cin>>opt;
        cin>>x;
        switch (opt)
        {
        case 0:
            if(ans.insert(x) == -1)
                cout<<"Existed"<<endl;
            break;
        case 1:
            len = ans.search(x);
            if(len == -1)
                cout<<"Not Found"<<endl;
            else
                cout<<len<<endl;
            break;
        case 2:
            len = ans.remove(x);
            if(len == -1)
                cout<<"Delete Failed"<<endl;
            else
                cout<<len<<endl;
            break;
        default:
            break;

        }
        //ans.print();
    }
}*/
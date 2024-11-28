#include<iostream>
#include <map>
using namespace std;

template<class T>
class single;
template<class T>
class chain;

class myMap
{
public:
    explicit myMap(int size);
    ~myMap();
    void display() const;
    void flush();
    void insert(int from , int to);                 //插入
    void remove(int from , int to);                 //删除
    int  connectedNum();                            //连通分量数
    void connectedNode();                           //所有连通子图中最小点的编号（升序）
    int  dfsMin(int s, chain<int> *dfsChain);       //从 s 点开始的字典序最小的 dfs 序列，同时返回长度
    int  bfsMin(int t, chain<int> *bfsChain);       //从 t 点开始的字典序最小的 bfs 序列，同时返回长度
    int  path(int s , int t);                       //从 s 点到 t 点的最短路径，若是不存在路径则输出-1
private:
    int size;
    chain<int> *mapChain = NULL;
    chain<int> *connectedChain = NULL;

    void connect(bool *connected , int node);
    void dfs(bool *used, int s, chain<int>* dfsChain);
};

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
    void sortInsert(const T& val);
    void push_back(const T& val);   //末尾插入
    void remove(const T& val);  //删除指定元素
    int search(const T& val);  //查找元素
    void reverse(); //原地逆置
    int display(); //输出
    void sort();//排序
    void clear();   //清空
    void print(); //打印
    int Size() {return size;};
    chain<T>& SortedMerge( chain<T>& other);
    T& top()
    {
        return head->data;
    }

    bool empty()
    {
        return (head == NULL);
    }

    void removeTop()
    {
        if(head == NULL)
            return;
        single<T>* temp = head;
        head = head->next;
        delete temp;
        --size;
    }
private:
    single<T>* head;
    int size;
    single<T>* tail;
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
void chain<T>::sortInsert(const T& val)
{
    single<T>* temp = head;
    if (temp == NULL)
        head = new single<T>(val);
    else if (val < temp->data)
    {
        head = new single<T>(val);
        head->next = temp;
    }
    else
    {
        while (temp->next != NULL && val > temp->next->data)
        {
            temp = temp->next;
        }
        single<T>* temp2 = temp->next;
        temp->next = new single<T>(val,temp2);
    }
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
        tail = head;
        return;
    }
    tail->next = new single<T>(val,NULL);
    tail = tail->next;
    ++size;
}

template <class T>
void chain<T>::remove(const T& val)
{
    if (head->data == val)
    {
        single<T>* temp = head;
        head = head->next;
        delete temp;
        --size;
        return;
    }
    single<T>* temp = head;
    for(;temp->next != NULL && temp->next->data != val ; temp = temp->next){}
    if(temp->next == NULL)
    {
        cout<< -1 <<endl;
        return;
    }

    single<T>* temp2 = temp->next;
    temp->next = temp->next->next;
    delete temp2;
    if (temp->next == NULL)
        tail = temp;
    --size;
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
    for(int i = 0 ; start != end(); ++start, ++i)
    {
        cout<< *start << " ";
    }
    cout<<endl;
    return 1;
}

template <class T>
void chain<T>::sort()
{
    if (size == 0 || size == 1) return;
    single<T>* temp = head;
    T max = head->data;
    for(; temp != NULL; temp = temp->next)
    {
        if(max < temp->data) max = temp->data;
    }
    int j = 10;
    int p = 1;
    while(p <= max)
    {
        chain<T>* sorted = new chain<T>[19];
        temp = head;
        for(; temp != NULL; temp = temp->next)
        {

            const int& a = temp->data % j / p + 9;
            sorted[a].push_back(temp->data);
        }

        single<T>* start = head;
        for(int i = 0 ; i < 19 ; i++)
        {
            auto s = sorted[i].begin();
            while(s != NULL)
            {
                start->data = *s;
                start = start->next;
                ++s;
            }
            sorted[i].clear();
        }

        j *= 10;
        p *= 10;

    }
}

template <class T>
void chain<T>::clear()
{
    single<T>* temp = head;
    while(temp != NULL)
    {
        single<T>* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
    head = NULL;
    size = 0;
}

template <class T>
void chain<T>::print()
{
    cout<<"chain print"<<endl;
    single<T>* temp = head;
    while(temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

template <class T>
chain<T>& chain<T>::SortedMerge( chain<T>& other)
{
    chain<T>* temp = new chain<T>();
    chain<T>::iterator sa = begin();
    chain<T>::iterator sb = other.begin();
    while (sa != NULL && sb != NULL)
    {
        if(*sa > *sb)
        {
            temp->push_back(*sb);
            ++sb;
        }else
        {
            temp->push_back(*sa);
            ++sa;
        }
    }
    while (sb != NULL)
    {
        temp->push_back(*sb);
        ++sb;
    }
    while (sa != NULL)
    {
        temp->push_back(*sa);
        ++sa;
    }
    return *temp;
}

myMap::myMap(int size)
{
    this->size = size;
    mapChain = new chain<int>[size + 1]();
}

myMap::~myMap()
{
    delete [] this->mapChain;
}

void myMap::display() const
{
    for(int i = 1 ; i <= size ; i++)
        mapChain[i].display();
}

void myMap::flush()
{
    for(int i = 1 ; i <= size ; i++)
        mapChain[i].sort();
}


void myMap::insert(int from, int to)
{
    mapChain[from].sortInsert(to);
    mapChain[to].sortInsert(from);
}

void myMap::remove(int from, int to)
{
    mapChain[from].remove(to);
    mapChain[to].remove(from);
}

int myMap::connectedNum()
{
    connectedChain = new chain<int>();
    bool connected[size + 1];
    for(int i = 1 ; i <= size ; i++)
        connected[i] = false;
    for(int i = 1 ; i <= size ; i++)
    {
        if(connected[i])
            continue;
        connectedChain->push_back(i);
        connect(connected, i);
    }
    return connectedChain->Size();
}

void myMap::connect(bool* connected, int node)
{
    if (connected[node])
        return;
    connected[node] = true;
    chain<int>::iterator it = mapChain[node].begin();
    for(; it != mapChain[node].end(); ++it)
    {
        connect(connected, *it);
    }
}

void myMap::connectedNode()
{
    connectedChain->display();
}

int myMap::dfsMin(int s, chain<int>* dfsChain)
{
    bool used[size + 1];
    for(int i = 1 ; i <= size ; i++)
        used[i] = false;
    dfs(used, s, dfsChain);
    int ans = 0;
    for(int i = 1 ; i <= size ; i++)
    {
        if (used[i])
            ans++;
    }
    return ans;
}

void myMap::dfs(bool *used , int s , chain<int>* dfsChain)
{
    if(used[s])
        return;
    used[s] = true;
    dfsChain->push_back(s);
    chain<int>::iterator it = mapChain[s].begin();
    for(; it != mapChain[s].end(); ++it)
        dfs(used, *it, dfsChain);
}

int myMap::bfsMin(int t, chain<int>* bfsChain)
{
    bool used[size + 1];
    for(int i = 1 ; i <= size ; i++)
        used[i] = false;
    int ans = 0;
    chain<int> *pre = new chain<int>();
    chain<int> *tail = new chain<int>();
    pre->push_back(t);
    used[t] = true;
    while(!pre->empty())
    {
        //pre->sort();
        for(chain<int>::iterator it = pre->begin(); it != pre->end(); ++it)
        {
            bfsChain->push_back(*it);
        }
        while(!pre->empty())
        {
            int node = pre->top();
            pre->removeTop();
            ans++;
            chain<int>::iterator it = mapChain[node].begin();
            for(; it != mapChain[node].end(); ++it)
            {
                if(!used[*it])
                {
                    used[*it] = true;
                    tail->push_back(*it);
                }
            }
        }
        delete pre;
        pre = tail;
        tail = new chain<int>();
    }
    delete pre;
    delete tail;
    return ans;
}


int myMap::path(int s, int t)
{
    if(s == t)
        return 0;
    bool used[size + 1];
    for(int i = 1 ; i <= size ; i++)
        used[i] = false;
    int ans = 0;
    chain<int> *pre = new chain<int>();
    chain<int> *tail = new chain<int>();
    pre->push_back(s);
    used[s] = true;
    while(!pre->empty())
    {
        ans++;
        while(!pre->empty())
        {
            int node = pre->top();
            pre->removeTop();
            chain<int>::iterator it = mapChain[node].begin();
            for(; it != mapChain[node].end(); ++it)
            {
                if (*it == t)
                {
                    delete pre;
                    delete tail;
                    return ans;
                }
                if(!used[*it])
                {
                    used[*it] = true;
                    tail->push_back(*it);
                }
            }
        }
        delete pre;
        pre = tail;
        tail = new chain<int>();
    }
    delete pre;
    delete tail;
    return -1;
}


int main()
{
    int n ,m ,s ,t;
    int op , from , to;
    cin >> n >> m >> s >> t;
    myMap map(n);
    chain<int> *ch = new chain<int>();
    for(int i = 0 ; i < m ; i++)
    {
        cin >> op;
        cin >> from;
        cin >> to;
        switch(op)
        {
            case 0:
                map.insert(from, to);
                break;
            case 1:
                map.remove(from, to);
                break;
            default:
                break;
        }
    }
    //map.display();
    cout << map.connectedNum() << endl;
    map.connectedNode();
    cout << map.dfsMin(s , ch) << endl;
    ch->display();
    ch->clear();
    cout << map.bfsMin(t , ch) << endl;
    ch->display();
    cout<<map.path(s , t )<<endl;
    delete ch;
    return 0;
}
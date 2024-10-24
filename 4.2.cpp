/*
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
    void remove(const T& val);  //删除指定元素
    int search(const T& val);  //查找元素
    void reverse(); //原地逆置
    int display(); //输出
    void sort();//排序
    void clear();   //清空
    void print(); //打印
    chain<T>& SortedMerge( chain<T>& other);

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
    int ans = 0;
    for(int i = 0 ; start != end(); ++start, ++i)
    {
        ans += i ^ (*start);
    }
    return ans;
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



int main()
{
    int n ;
    int q;
    int num;
    chain<int> ans1;
    chain<int> ans2;
    chain<int> ans3;
    cin>>n;
    cin>>q;
    for(int i = 0 ; i < n ; i++)
    {
        cin>>num;
        ans1.push_back(num);
    }
    for(int i = 0 ; i < q ; i++)
    {
        cin>>num;
        ans2.push_back(num);
    }

    ans1.sort();
    cout<<ans1.display()<<endl;
    ans2.sort();
    cout<<ans2.display()<<endl;
    ans3 = ans1.SortedMerge(ans2);
    cout<<ans3.display()<<endl;
}*/
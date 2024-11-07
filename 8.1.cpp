/*
#include <iostream>
using namespace std;

template<class T>
class my_hash_map
{
public:
    my_hash_map(int D);
    ~my_hash_map();
    void insert(T& val);    //插入
    int search(T& val);     //搜索
    void remove(T& val);    //刪除
    void print();
private:
    int D;
    int size;
    T** table;
};

template <class T>
my_hash_map<T>::my_hash_map(int D)
{
    this->D = D;
    table = new T*[D];
    size = D;
    for (int i = 0; i < D; i++)
    {
        table[i] = NULL;
    }
}

template <class T>
my_hash_map<T>::~my_hash_map()
{
    for (int i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            delete table[i];
        }
    }
    delete []table;
}

template <class T>
void my_hash_map<T>::insert(T& val)
{
    int i = val % D;
    bool flag = true;
    while(i !=  val % D || flag)    //循环遍历
    {
        flag = false;
        if (table[i] == NULL)       //找到空位
        {
            table[i] = new T;
            *table[i] = val;
            cout<<i<<endl;
            return;
        }
        if (*table[i] == val)
        {
            cout << "Existed" << endl;
            return;
        }
        i = (i + 1) % size;
    }
}

template <class T>
int my_hash_map<T>::search(T& val)
{
    int i = val % D;
    bool flag = true;
    while(i !=  val % D || flag)
    {
        flag = false;
        if (table[i] == NULL)
            break;
        if (*table[i] == val)
        {
            return i;
        }
        i= (i + 1) % size;
    }
    return -1;
}

template <class T>
void my_hash_map<T>::remove(T& val)
{
    int i = val % D;
    int j;
    int pre;
    int mo = 0;
    bool flag = true;
    while(i !=  val % D || flag)    //找到并删除
    {
        flag = false;
        if (table[i] == NULL)
        {
            cout<<"Not Found"<<endl;
            return;
        }
        if (*table[i] == val)
        {
            break;
        }
        i = (i + 1) % size;
    }
    if(i == val % D && *table[i] != val)
    {
        cout<<"Not Found"<<endl;
        return;
    }
    delete table[i];
    pre = i; //空位
    j = (i + 1) % size;
    while(j != i)   //后面的元素前移
    {
        if (table[j] == NULL)
        {
            break;
        }
        if(!(j >  pre && pre >= *table[j] % D || *table[j] % D > j && j > pre || pre >= *table[j] % D && *table[j] % D > j))
        {
            j = (j + 1) % size;
            continue;
        }
        table[pre] = table[j];
        pre = j;
        ++mo;
        j = (j + 1) % size;
    }
    cout<<mo<<endl;
    table[pre] = NULL;
}

template <class T>
void my_hash_map<T>::print()
{
    for (int i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            cout << " " << *table[i] << " ";
        }
        else
        {
            cout<<" N ";
        }
    }
    cout << endl;
}

int main()
{
    int m , D , opt , x;
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
                ans.insert(x);
                break;
            case 1:
                cout << ans.search(x) << endl;
                break;
            case 2:
                ans.remove(x);
                break;
            default:
                break;

        }
        //ans.print();
    }
}
*/
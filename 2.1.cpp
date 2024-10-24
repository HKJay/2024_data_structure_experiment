/*#include <iostream>
using namespace std;

template<class T>
class Sort
{
public:
    Sort(T* &list);
    Sort(T* &list, int n);
    void rank_sort();   //名次排序
    void sel_sort();    //及时终止的选择排序
    void bub_sort();    //及时终止的冒泡排序
    void ins_sort();    //插入排序
    void print();   //输出
private:
    T* sort_list = new T[1];
    int size;
    int length = 1;
    void change_length();
};

template <class T>
Sort<T>::Sort(T*& list)
{
    size = 0;
    while (list[size] != -1)
    {
        if (size >= length) change_length();
        sort_list[size] = list[size];
        size++;
    }
}

template <class T>
Sort<T>::Sort(T*& list, int n)
{
    size = n;
    delete[] sort_list;
    sort_list = new T[size];
    length = n;
    for (int i = 0; i < size; i++)
    {
        sort_list[i] = list[i];
    }
}

template <class T>
void Sort<T>::rank_sort()
{
    int* rank = new int[size];  //排名
    for (int i = 0; i < size; i++)
        rank[i] = 0;
    for (int i = 1; i < size; i++)
        for (int j = 0; j < i; j++)
            if (sort_list[i] >= sort_list[j]) rank[i]++;
            else rank[j]++;

    T* temp = new T[size]; //排序
    for (int i = 0; i < size; i++)
        temp[rank[i]] = sort_list[i];
    for (int i = 0; i < size; i++)
        sort_list[i] = temp[i];

    delete[] temp;
    delete[] rank;
}

template <class T>
void Sort<T>::sel_sort()
{
    bool sorted = false;
    for (int i = size; !sorted && (i > 1); i--)
    {
        int index_of_max = 0;
        sorted = true;
        for (int j = 1; j < i; j++)
            if (sort_list[j] >= sort_list[index_of_max]) index_of_max = j;
            else sorted = false;
        T middle = sort_list[index_of_max];
        sort_list[index_of_max] = sort_list[i - 1];
        sort_list[i - 1] = middle;
    }
}

template <class T>
void Sort<T>::bub_sort()
{
    bool sorted = false;
    for (int i = size; !sorted && i > 1; i--)
    {
        sorted = true;
        for (int j = 0; j < i - 1; j++)
        {
            if (sort_list[j] > sort_list[j + 1])
            {
                sorted = false;
                T middle = sort_list[j];
                sort_list[j] = sort_list[j + 1];
                sort_list[j + 1] = middle;
            }
        }
    }
}

template <class T>
void Sort<T>::ins_sort()
{
    int* insert = new T[size];
    for (int i = 0; i < size; i++)
    {
        int j;
        for (j = 0; j < i; j++)
        {
            if (sort_list[i] < insert[j]) break;
        }
        for (int k = i; k > j; k--)
            insert[k] = insert[k - 1];
        insert[j] = sort_list[i];
    }
    for (int i = 0; i < size; i++)
        sort_list[i] = insert[i];
    delete[] insert;
}

template <class T>
void Sort<T>::print()
{
    for (int i = 0; i < size; i++)
        cout << sort_list[i] << " ";
    cout << endl;
}

template <class T>
void Sort<T>::change_length()
{
    length = length * 2;
    T* new_list = new T[length];
    for (int i = 0; i < size; i++)
        new_list[i] = sort_list[i];
    delete[] sort_list;
    sort_list = new_list;
}

int main()
{
    int n;
    cin >> n;
    int* list = new int[n + 1];
    for (int i = 0; i < n; i++)
        cin >> list[i];
    list[n] = -1;
    Sort<int> sorts(list , n);
    sorts.sel_sort();
    sorts.print();
    delete[] list;
    return 0;
}*/
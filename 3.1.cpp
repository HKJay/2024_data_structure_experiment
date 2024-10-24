/*
#include<iostream>
using namespace std;

class my_string
{
public:
    my_string(const char* thestr = "");
    int length() const
    {
        return size;
    }
    typedef char* iterator;
    iterator begin() const
    {
        return str;
    }
    iterator end() const
    {
        return str + size;
    }
    char& operator[](int index)
    {
        return str[index];
    }
    bool operator==(const my_string &other) const
    {
        if (size != other.size)
            return false;
        for (int i = 0; i < size; i++)
            if (str[i] != other.str[i])
                return false;
        return true;
    }
    void output() {cout << str << endl;}
private:
    char *str = nullptr;
    int size = 0;
    int capacity = 0;
};

my_string::my_string(const char* thestr)
{
    while (thestr[size] != '\0')
    {
        size++;
    }
    capacity = size + 1;
    str = new char[size + 1];
    for (int i = 0; i < size; i++)
    {
        str[i] = thestr[i];
    }
    str[size] = '\0';
}


template<class T>
void changelen(T*& a , int oldlength , int newlength) //改变数组容量
{
    T* temp = new T[newlength];
    int min ;
    if (oldlength > newlength)
        min = newlength;
    else
        min = oldlength;
    for (int i = 0; i < min; i++)
    {
        temp[i] = a[i];
    }
    delete[] a;
    a = temp;
}



class address_list
{
public:
    void insert(my_string tname, my_string tphone , my_string tclass , int tdor);
    void del(my_string tname);
    void change_phone(my_string tname, my_string tphone);
    void change_c_lass(my_string tname, my_string tclass);
    void change_dor(my_string tname, int dor);
    int find(my_string tname);
    int all_class(my_string tclass);
    void output()
    {
        for (int i = 0; i < size; i++)
        {name[i].output() ; phone[i].output() ; c_lass[i].output();  cout << dormitory[i] << endl;};
    }
private:
    int size = 0;
    int capacity = 1;
    my_string* name = new my_string[1]; //姓名
    my_string* phone = new my_string[1];  //电话号
    my_string* c_lass = new my_string[1]; //班级
    int* dormitory = new int[1]; //宿舍

};

void address_list::insert(my_string tname, my_string tphone, my_string tclass, int tdor)
{
    while (capacity <= size) //检测容量是否足够
    {
        changelen(name, capacity, capacity * 2);
        changelen(phone, capacity, capacity * 2);
        changelen(c_lass, capacity, capacity * 2);
        changelen(dormitory, capacity, capacity * 2);
        capacity *= 2;
    }
    name[size] = tname;
    phone[size] = tphone;
    c_lass[size] = tclass;
    dormitory[size] = tdor;
    size++;
}

void address_list::del(my_string tname)
{
    int index = 0;
    for (index = 0; index < size; index++) //依次寻找
        if (tname == name[index]) break;
    for (int i = index; i < size; i++) //将之后的元素前移
    {
        name[i] = name[i + 1];
        phone[i] = phone[i + 1];
        c_lass[i] = c_lass[i + 1];
        dormitory[i] = dormitory[i + 1];
    }
    size--;
}

void address_list::change_phone(my_string tname, my_string tphone)
{
    int index = 0;
    for (index = 0; index < size; index++)//依次寻找
        if(tname == name[index]) break;
    phone[index] = tphone;
}
void address_list::change_c_lass(my_string tname, my_string tclass)
{
    int index = 0;
    for (index = 0; index < size; index++)//依次寻找
        if(tname == name[index]) break;
    c_lass[index] = tclass;
}
void address_list::change_dor(my_string tname, int dor)
{
    int index = 0;
    for (index = 0; index < size; index++)//依次寻找
        if(tname == name[index]) break;
    dormitory[index] = dor;
}

int address_list::find(my_string tname)
{
    for (int i = 0; i < size; i++)//依次寻找
        if (tname == name[i]) return 1;
    return 0;
}

int address_list::all_class(my_string tclass)
{
    int ans = -1;
    for (int i = 0; i < size; i++)
    {
        if (tclass == c_lass[i])
        {
            if (ans == -1) //第一个
            {
                ans = dormitory[i];
            }
            else
            {
                ans ^= dormitory[i];
            }
        }
    }
    if (ans == -1) return 0;
    return ans;
}


int main()
{
    int n;
    int ope;
    char read[100];
    int l;
    int * ans = new int[n];
    int a = 0;
    my_string tname;
    my_string tphone;
    my_string tclass;
    int tdor;
    cin >> n;
    address_list answer;
    for (int i = 0; i < n; i++)
    {
        cin >> ope;
        switch (ope)
        {
            case 0:
                cin >> read;
                tname = read;
                cin >> read;
                tphone = read;
                cin >> read;
                tclass = read;
                cin >> tdor;
                answer.insert(tname, tphone, tclass, tdor);
                break;
            case 1:
                cin >> read;
                tname = read;
                answer.del(tname);
                break;
            case 2:
                int w;
                cin >> read;
                tname = read;
                cin >> w;
                switch (w)
                {
                    case 1:
                        cin >> read;
                        tphone = read;
                        answer.change_phone(tname, tphone);
                        break;
                    case 2:
                        cin >> read;
                        tclass = read;
                        answer.change_c_lass(tname, tclass);
                        break;
                    case 3:
                        cin >> tdor;
                        answer.change_dor(tname, tdor);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                cin >> read;
                tname = read;
                ans[a] = answer.find(tname);
                a += 1;
                break;
            case 4:
                cin >> read;
                tclass = read;
                ans[a] = answer.all_class(tclass);
                a += 1;
                break;
            default:
                break;

        }
    }
    for (int i = 0; i < a; i++)
        cout << ans[i] << endl;
    return 0;
}
*/
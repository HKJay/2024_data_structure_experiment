/*
#include <iomanip>
#include<iostream>
using namespace std;

template<class T>
class stack
{
public:
    stack();
    ~stack(){delete []data;};
    T& top();
    void push(T);
    void pop();
    bool empty(){return tail == 0;};
    void display();
private:
    int size;
    T* data;
    int tail;
};

template <class T>
void stack<T>::display()
{
    for(int i = 0;i<tail;i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

template <class T>
stack<T>::stack()
{
    tail = 0;
    size = 1;
    data = new T[size];
}

template <class T>
T& stack<T>::top()
{
    if (tail == 0)
        throw  1;
    return data[tail - 1];
}

template <class T>
void stack<T>::push(T val)
{
    if (tail == size)
    {
        T* temp = new T[size*2];
        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        delete [] data;
        data = temp;
        size *= 2;
    }
    data[tail] = val;
    tail++;
}

template <class T>
void stack<T>::pop()
{
    if (tail == 0)
    {
        return;
    }
    tail -= 1;

}

double figure(string str)
{
    double sum = -1;
    stack<double> num;
    stack<int> op;
    double front;
    double back;
    int ope;
    double ans;
    char pre = '(';
    bool flag_f = false;
    bool flag = false;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            op.push(-1);
        }
        else if (str[i] == ')')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            ans = 0;
            while(true)
            {
                back = num.top();
                num.pop();
                ope = op.top();
                op.pop();
                if (ope == -1)
                {
                    num.push(ans + back);
                    break;
                }
                switch (ope)
                {
                    case 1:
                        ans += back;
                        break;
                    case 2:
                        ans -= back;
                        break;
                    case 3:
                        front = num.top();
                        num.pop();
                        num.push(front * back);
                        break;
                    case 4:
                        front = num.top();
                        num.pop();
                        num.push(front / back);
                        break;
                    default:
                        break;
                }
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
        }else if (str[i] == '+')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(1);
        }else if (str[i] == '-')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if(pre == '(')
            {
                flag_f = true;
                pre = str[i];
                continue;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(2);
        }else if (str[i] == '*')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(3);
        }else if (str[i] == '/')
        {
            if (sum != -1)
            {
                if (flag_f)
                {
                    sum = 0 - sum;
                    flag_f = false;
                }
                num.push(sum);
                sum = -1;
            }
            if (not op.empty() && (op.top() == 3 || op.top() == 4))
            {
                flag = true;
                ope = op.top();
                op.pop();
                back = num.top();
                num.pop();
                front = num.top();
                num.pop();
            }
            op.push(4);
        }else
        {
            if (sum != -1)
            {
                sum = sum * 10 + str[i] - '0';
            }else
            {
                sum = str[i] - '0';
            }
        }
        if (flag == true)
        {
            if (ope == 3)
            {
                num.push(front * back);
            }
            else if (ope == 4)
            {
                num.push(front / back);
            }
            flag = false;
        }
        pre = str[i];
    }
    if(sum != -1)
    {
        if (flag_f)
        {
            sum = 0 - sum;
            flag_f = false;
        }
        num.push(sum);
    }
    ans = 0;
    while(not op.empty())
    {
        back = num.top();
        num.pop();
        ope = op.top();
        op.pop();
        switch (ope)
        {
        case 1:
            ans += back;
            break;
        case 2:
            ans -= back;
            break;
        case 3:
            front = num.top();
            num.pop();
            num.push(front * back);
            break;
        case 4:
            front = num.top();
            num.pop();
            num.push(front / back);
            break;
        default:
            break;
        }
    }
    return ans + num.top();
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        string str;
        cin>>str;
        cout << fixed <<setprecision(2) << figure(str)<<endl;
    }
}
*/
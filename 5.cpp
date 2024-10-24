/*
#include<iostream>
using namespace std;

struct single
{
    int row = -1;
    int col = -1;
    int value = -1;
};

class sparseMatrix //稀疏矩阵类
{
public:
    sparseMatrix(int row = 0, int col = 0){this->rows = row;this->cols = col;};
    sparseMatrix(sparseMatrix& copy);
    ~sparseMatrix(){delete []matrix;};
    sparseMatrix operator*(sparseMatrix second); //乘法
    sparseMatrix operator+(sparseMatrix second); //加法
    void operator=(const sparseMatrix& copy);//赋值
    void save_push(int row, int col, int value);
    void trans();
    void print();
    void fresh(int row,int col){this->rows = row;this->cols = col;len = 1;tail = 0 ; delete []matrix; matrix = new single;};
    void read();
    void re_read();

private:
    single* matrix = new single;

    int len = 1; //数组容量
    int tail = 0; //已存数量
    int rows;//行
    int cols;//列
};

sparseMatrix::sparseMatrix(sparseMatrix& copy)
{
    delete []matrix;
    rows = copy.rows;
    cols = copy.cols;
    len = copy.len;
    tail = copy.tail;
    matrix = new single[len];
    for (int i = 0; i < len; i++)
    {
        matrix[i].row = copy.matrix[i].row;
        matrix[i].col = copy.matrix[i].col;
        matrix[i].value = copy.matrix[i].value;
    }
}

sparseMatrix sparseMatrix::operator*(sparseMatrix second)
{
    sparseMatrix result(rows, second.cols);
    if (cols != second.rows)
    {
        cout<<-1<<endl;
        return second;
    }
    int* record = new int[rows * second.cols];
    for(int i = 0; i < rows * second.cols; i++)
        record[i] = 0;
    int* rowNum = new int[second.rows + 1];
    int* next = new int[second.rows + 1]; //记录second每行位置
    for (int i = 0; i < second.rows + 1 ; i++)
    {
        rowNum[i] = 0;
    }
    for (int i = 0; i < second.tail; i++)
    {
        rowNum[second.matrix[i].row] += 1;
    }
    next[1] = 0;
    for (int i = 2 ; i <= second.rows  ; i++)
    {
        next[i] = next[i - 1] + rowNum[i - 1];
    }
    for (int i = 0 ; i < tail ; ++i)
    {
        for (int j = next[matrix[i].col]; j < next[matrix[i].col] + rowNum[matrix[i].col]; j++)
        {
            record[(matrix[i].row - 1) * second.cols + second.matrix[j].col - 1] += matrix[i].value * second.matrix[j].value;
        }
    }
    for(int i = 1; i <= rows; i++)
    {
        for(int j = 1; j <= second.cols; j++)
        {
            if (record[(i - 1) * second.cols + j - 1] != 0)
            {
                result.save_push(i , j, record[(i - 1) * second.cols + j - 1]);
            }
        }
    }
    delete []record;
    delete []next;
    delete []rowNum;
    return result;
}

sparseMatrix sparseMatrix::operator+(sparseMatrix second)
{
    if (cols != second.cols || rows != second.rows)
    {
        cout<<-1<<endl;
        return second;
    }
    sparseMatrix result(rows, cols);
    int i = 0;
    int j = 0;
    while(i < tail && j < second.tail)
    {
        if(matrix[i].row < second.matrix[j].row)
        {
            result.save_push(matrix[i].row, matrix[i].col, matrix[i].value);
            i++;
        }else if(matrix[i].row > second.matrix[j].row)
        {
            result.save_push(second.matrix[j].row, second.matrix[j].col, second.matrix[j].value);
            j++;
        }else
        {
            if(matrix[i].col < second.matrix[j].col)
            {
                result.save_push(matrix[i].row, matrix[i].col, matrix[i].value);
                i++;
            }else if(matrix[i].col > second.matrix[j].col)
            {
                result.save_push(second.matrix[j].row, second.matrix[j].col, second.matrix[j].value);
                j++;
            }else
            {
                if (matrix[i].value + second.matrix[j].value != 0)
                result.save_push(matrix[i].row, matrix[i].col, matrix[i].value + second.matrix[j].value);
                i++;
                j++;
            }
        }
    }
    while(i < tail)
    {
        result.save_push(matrix[i].row, matrix[i].col, matrix[i].value);
        i++;
    }
    while(j < second.tail)
    {
        result.save_push(second.matrix[j].row, second.matrix[j].col, second.matrix[j].value);
        j++;
    }
    return result;
}
void sparseMatrix::operator=(const sparseMatrix& copy)
{
    delete []matrix;
    rows = copy.rows;
    cols = copy.cols;
    len = copy.len;
    tail = copy.tail;
    matrix = new single[len];
    for (int i = 0; i < len; i++)
    {
        matrix[i].row = copy.matrix[i].row;
        matrix[i].col = copy.matrix[i].col;
        matrix[i].value = copy.matrix[i].value;
    }
}


void sparseMatrix::save_push(int row, int col, int value)
{
    if (tail == len)
    {
        single* newM = new single[len * 2];
        for (int i = 0; i < len; i++)
        {
            newM[i].row = matrix[i].row;
            newM[i].col = matrix[i].col;
            newM[i].value = matrix[i].value;
        }
        delete []matrix;
        matrix = newM;
        len = len * 2;
    }
    matrix[tail].row = row;
    matrix[tail].col = col;
    matrix[tail].value = value;
    tail++;
}

void sparseMatrix::trans()
{
    single* old = new single[len];
    for (int i = 0; i < tail; i++)
    {
        old[i].row = matrix[i].row;
        old[i].col = matrix[i].col;
        old[i].value = matrix[i].value;
    }
    int *colSize = new int[cols + 1];
    int * next = new int[cols + 1];
    for(int i = 0; i < cols + 1; i++)
    {
        colSize[i] = 0;
    }
    for (int i = 0; i < tail; i++)
    {
        colSize[matrix[i].col] += 1;
    }
    next[0] = 0;
    next[1] = 0;
    for (int i = 2; i < cols + 1; i++)
    {
        next[i] = next[i - 1] + colSize[i - 1];
    }
    for (int i = 0; i < tail; i++)
    {
        matrix[next[old[i].col]].col = old[i].row;
        matrix[next[old[i].col]].row = old[i].col;
        matrix[next[old[i].col]].value = old[i].value;
        next[old[i].col] += 1;
    }
    delete []colSize;
    delete []next;
    delete []old;
    int mid = rows;
    rows = cols;
    cols = mid;
}

void sparseMatrix::print()
{
    cout << rows << ' ' << cols << endl;
    int loc = 0;
    for(int nrow = 1; nrow <= rows; nrow++)
    {
        int ncol = 1;
        if(loc < tail && nrow == matrix[loc].row && ncol == matrix[loc].col)
        {
            cout<<matrix[loc].value;
            ++loc;
        }else
        {
            cout<<0;
        }
        for(ncol = 2; ncol <= cols; ncol++)
        {
            if(loc < tail && nrow == matrix[loc].row && ncol == matrix[loc].col)
            {
                cout<<' '<<matrix[loc].value;
                ++loc;
            }else
            {
                cout<<' '<<0;
            }
        }
        cout<<endl;
    }
}

void sparseMatrix::read()
{
    int num;
    cin >> num;
    delete []matrix;
    matrix = new single[num];
    len = num;
    for (tail = 0; tail < num; tail++)
    {
        cin >> matrix[tail].row;
        cin >> matrix[tail].col;
        cin >> matrix[tail].value;
    }

}

void sparseMatrix::re_read()
{
    int val;
    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < cols + 1; j++)
        {
            cin >> val;
            if(val != 0)
            {
                if(tail == len)
                {
                    single* newM = new single[len * 2];
                    for (int ni = 0; ni < len; ni++)
                    {
                        newM[ni].row = matrix[ni].row;
                        newM[ni].col = matrix[ni].col;
                        newM[ni].value = matrix[ni].value;
                    }
                    delete []matrix;
                    matrix = newM;
                    len = len * 2;
                }
                matrix[tail].row = i;
                matrix[tail].col = j;
                matrix[tail].value = val;
                tail++;
            }
        }
    }
}


int main()
{
    int op;
    cin>>op;
    sparseMatrix ans;
    sparseMatrix second;
    int srow, scol ;
    for(int i = 0; i < op; i++)
    {
        int n;
        cin>>n;
        switch(n)
        {
            case 1:
                cin>>srow;
                cin>>scol;
                ans.fresh(srow,scol);
                ans.re_read();
                break;
            case 2:
                cin>>srow;
                cin>>scol;
                second.fresh(srow,scol);
                second.read();
                ans = ans * second;
                break;
            case 3:
                cin>>srow;
                cin>>scol;
                second.fresh(srow,scol);
                second.read();
                ans = ans + second;
                break;
            case 4:
                ans.print();
                break;
            case 5:
                ans.trans();
                break;
            default:
                break;
        }
    }
}
*/
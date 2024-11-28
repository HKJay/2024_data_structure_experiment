/*
#include <iostream>
using namespace std;

template <class T>
struct BinaryTreeNode//二叉树节点
{//二叉树节点
    T element;
    BinaryTreeNode<T>* leftChild;
    BinaryTreeNode<T>* rightChild;
    int leftSize;//规定为该节点左子树的元素个数

    BinaryTreeNode(const T& theElement)
	{
        element = theElement;
        leftChild = NULL;
        rightChild = NULL;
        leftSize = 0;
    }

    BinaryTreeNode(const T& theElement, BinaryTreeNode<T>* theLeft, BinaryTreeNode<T>* theRight, int LeftSize)
	{
        element = theElement;
        leftChild = theLeft;
        rightChild = theRight;
        leftSize = LeftSize;
    }
};

template <class T>
class indexedBSTree
{//二叉搜索树 （带索引）
	public:
    	indexedBSTree()
		{//初始化
			root = NULL;
        	size = 0;
    	}
    	int insert(const T& theElement);//插入函数
    	int find(const T& theElement);//搜索函数
    	int erase(const T& theElement);//删除函数
    	int Search(int a);//按名次搜索函数
    	int delete_(int a);//按名次删除函数
	private:
    	int size;
    	BinaryTreeNode<T>* root;
};

//插入函数
template <class T>
int indexedBSTree<T>::insert(const T& theElement)
{
    BinaryTreeNode<T>* p = root;
    BinaryTreeNode<T>* pp = NULL;
    //pp相当于一个影子跟屁虫，记p的父节点，与p同步下移，保证插入
    int sum = 0;
    while (p != NULL)
	{
        if (p->element < theElement)
		{//要插入的元素大，放右节点去
            sum ^= p->element;
            pp = p;
            p = p->rightChild;
        }
        else if (p->element > theElement)
		{//要插入的元素小，放左节点去
            sum ^= p->element;
            pp = p;
            p = p->leftChild;
        }
        else if (p->element == theElement)
		{//恰好相等，不需要插入
            return 0;
        }
    }

    //为新元素建立新节点，与pp相连
    BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(theElement);

    if (pp != NULL)
	{
		//新元素比父节点大，为pp的右孩子
        if (theElement > pp->element)
            pp->rightChild = newNode;
        //新元素比父节点小，为pp的左孩子
        else if (theElement < pp->element)
            pp->leftChild = newNode;
    }
    else
	{//空树，直接插入到根节点
        root = newNode;
    }

    size++;

    p = root;
    while (p->element != theElement)
    {//左子树元素个数更新 （即索引更新）
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p->leftSize++;
            p = p->leftChild;
        }
    }
    return sum;
}

//搜索函数
template <class T>
int indexedBSTree<T>::find(const T& theElement)
{
    BinaryTreeNode<T>* p = root;
    int sum = 0;
    while (p != NULL && p->element != theElement)
    {
        sum ^= p->element;
        if (p->element > theElement)
        {
            p = p->leftChild;
        }
        else if (p->element < theElement)
        {
            p = p->rightChild;
        }
    }
    //【查找中，未找到，输出 0】
    if (p == NULL)
        return 0;
    //找到了
    else
    {
    	//补充p->element=theElement的异或计算
        sum ^= p->element;
        return sum;
    }
}

//删除函数
template <class T>
int indexedBSTree<T>::erase(const T& theElement)
{
    BinaryTreeNode<T>* p = root;
    BinaryTreeNode<T>* pp = NULL;
    int sum = 0;
    while (p != NULL && p->element != theElement)
    {//未完且还没到要删除的元素
        sum ^= p->element;
        pp = p;
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p = p->leftChild;
        }
    }

    if (p == NULL)
    {//未找到
        return 0;
    }

    //p->element=theElement 异或计算补充
    sum ^= p->element;

    p = root;
    while (p != NULL && p->element != theElement)
    {//左子树元素个数更新(即索引值更新
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p->leftSize--;
            p = p->leftChild;
        }
    }

	//当前元素有两个孩子
    if (p->leftChild != NULL && p->rightChild != NULL)
    {
    	//min_right是删除节点的右孩子，用来找那个最小的右元素
        BinaryTreeNode<T>* min_right = p->rightChild;
        //s是待删除节点
        BinaryTreeNode<T>* s = p;

		//【替换的为右子树中最小的】
        while (min_right->leftChild != NULL)
        {
            min_right->leftSize--;
            s = min_right;//用s记录最小元素的父节点的位置
            min_right = min_right->leftChild;//min_right记录最小元素的位置
        }

   		//用newNode存好找到的最小元素
        BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(min_right->element, p->leftChild, p->rightChild, p->leftSize);

		//开始替换
		if (pp == NULL)
            root = newNode;
        else if (p == pp->leftChild)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;

        if (s == p)
            pp = newNode;
        else
            pp = s;

        delete p;
        p = min_right;
    }

	//当前元素只有一个孩子，【直接用该孩子替换当前元素】
    BinaryTreeNode<T>* c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    //删除节点位于根节点
	if (p == root)
        root = c;//根节点更新为孩子节点
    //删除节点不是根节点
	else
    {
        if (p == pp->leftChild) //p是pp的左孩子
            pp->leftChild = c;
        else //p是pp的右孩子
            pp->rightChild = c;
    }
    size--;
    delete p;
    return sum;
}

//按名次搜索函数
template <class T>
int indexedBSTree<T>::Search(int a)
{
    BinaryTreeNode<T>* p = root;
    int sum = 0;
    while (p != NULL && p->leftSize != a)
    {
        sum ^= p->element;
        if (p->leftSize > a)
        { //该节点的索引比b大，证明b在左孩子中
            p = p->leftChild;
        }
        else if (p->leftSize < a)
        {//该节点的索引比b小，证明b在右孩子中
            a = a - p->leftSize - 1;
            p = p->rightChild;
        }
    }
    //没找到
    if (p == NULL)
        return 0;
    //找到了
    else
    {
    	//补充最后一次，最后一次该节点的索引等于b
        sum ^= p->element;
        return sum;
    }
}

//按名次删除函数
template <class T>
int indexedBSTree<T>::delete_(int a)
{
    BinaryTreeNode<T>* p = root;
    BinaryTreeNode<T>* pp = NULL;
    int sum = 0;
    while (p != NULL && p->leftSize != a)
    {
        sum ^= p->element;
        pp = p;
        if (p->leftSize > a)
        {//该节点的索引比b大，证明b在左孩子中
            p = p->leftChild;
        }
        else if (p->leftSize < a)
        {//该节点的索引比b小，证明b在右孩子中
            a = a - p->leftSize - 1;
            p = p->rightChild;
        }
    }
    //没找到
    if (p == NULL)
        return 0;
    //补充最后一次比较异或计算
    sum ^= p->element;
    int theElement = p->element;
    p = root;
    while (p != NULL && p->element != theElement)
    {
        if (p->element < theElement)
        {
            p = p->rightChild;
        }
        else if (p->element > theElement)
        {
            p->leftSize--;
            p = p->leftChild;
        }
    }
    //同erase理
    if (p->leftChild != NULL && p->rightChild != NULL)
    {
        BinaryTreeNode<T>* min_right = p->rightChild;
        BinaryTreeNode<T>* s = p;
        while (min_right->leftChild != NULL)
        {
            min_right->leftSize--;
            s = min_right;
            min_right = min_right->leftChild;
        }

        BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(min_right->element, p->leftChild, p->rightChild, p->leftSize);
        if (pp == NULL)
            root = newNode;
        else if (p == pp->leftChild)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;

        if (s == p)
            pp = newNode;
        else
            pp = s;

        delete p;
        p = min_right;
    }

    BinaryTreeNode<T>* c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    if (p == root)
        root = c;
    else
    {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    size--;
    delete p;
    return sum;
}

int main()
{
    indexedBSTree<int> x;
    int m, a, b;
    cin >> m;
    for(int i=0;i<m;i++)
	{
        cin >> a >> b;
        if (a == 0)
		{
            cout << x.insert(b) << endl;
        }
        if (a == 1)
		{
            cout << x.find(b) << endl;
        }
        if (a == 2)
		{
            cout << x.erase(b) << endl;
        }
        if (a == 3)
		{
            b = b - 1;
            cout << x.Search(b) << endl;
        }
        if (a == 4)
		{
            b = b - 1;
            cout << x.delete_(b) << endl;
        }
    }
}
*/
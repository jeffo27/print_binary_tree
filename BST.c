// This project is intended for the printing of a binary search tree.

// It uses the typical Queue solution.
// Because I have no idea how to implement Polymorphism in C,
// (in C++ there exists the GREAT(for me) template, but not in C)
// I have to write 2 Queues, one for the tree node and another for
// the information needed in printing. It's kinda annoying.

// because of my poor coding skill, the program is very limited.
// when the height of the tree is closely around 7 , the tree
// it produces looks better, but when the height is too small or big,
// the program fails to draw well, because for me the spaces are
// too difficult the control.

// the algorithm source:blog.csdn.net/zhanglei8893/article/details/5713101

#include"BST.h"
#define TRUE 1
#define FALSE 0

SearchTree Insert(SearchTree T, int data)
{
	if(T == NULL)
	{
		T = (SearchTree)malloc(sizeof(struct Node));
		if(T == NULL)
			Error1("out of space for tree");

		T->key = data;
		T->LeftChild = T->RightChild = NULL;
	}
	else if(data < T->key)
		T->LeftChild = Insert(T->LeftChild, data);
	else if(data > T->key)
		T->RightChild = Insert(T->RightChild, data);

	return T;
}

Position Find(SearchTree T, int data)
{
	if(T == NULL)
		return NULL;
	else if(data < T->key)
		return Find(T->LeftChild, data);
	else if(data > T->key)
		return Find(T->RightChild, data);
	else
		return T;
}

SearchTree Delete(SearchTree T, int data)
{
	Position Tmp;

	if(T == NULL)
	{
		printf("not found\n");
		return NULL;
	}
	else if(data < T->key)
		T->LeftChild = Delete(T->LeftChild, data);
	else if(data > T->key)
		T->RightChild = Delete(T->RightChild, data);
	else
	{
		if(T->LeftChild && T->RightChild)
		{
			Tmp = FindMin(T->RightChild);
			T->key = Tmp->key;
			T->RightChild = Delete(T->RightChild, T->key);
		}
		else
		{
			Tmp = T;
			if(T->LeftChild == NULL)
				T = T->RightChild;
			else if( T->RightChild == NULL)
				T = T->LeftChild;
            free(Tmp);
		}
	}

	return T;
}

Position FindMin(SearchTree T)
{
	if(T->LeftChild)
		return FindMin(T->LeftChild);
	else
		return T;
}

int GetHeight(SearchTree T)
{
    int h_left, h_right;
    if(!T)
        return -1;
    else
    {
        h_left = GetHeight(T->LeftChild);
        h_right = GetHeight(T->RightChild);

        return 1 + ( (h_left > h_right) ? h_left : h_right );
    }
}

void Error1(char *s)
{
    printf("error:%s\n",s);
    exit(1);
}

// for PrintDepth.

// content of "Queue.c"

Queue CreateQ(void)
{
    Queue Q = (Queue)malloc(sizeof(struct Qrec));
    if(!Q)
        Error1("out of space for Queue for TreeNode");

    Q->front = Q->end = NULL;

    return Q;
}

void InQ(Queue Q, ElementType data)
{
    PtrToItem newNode = (PtrToItem)malloc(sizeof(ElementType));
    if(!newNode)
    {
        printf("no space for newNode\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    if(!Q->end)
        Q->front = Q->end = newNode;
    else
    {
        Q->end->next = newNode;
        Q->end = newNode;
    }
}

ElementType OutQ(Queue Q)
{
    ElementType data;
    PtrToItem temp;

    if(!Q->front)
    {
        printf("the Queue is empty\n");
        exit(1);
    }

    temp = Q->front;
    data = temp->data;

    if(temp->next == NULL)
        Q->front = Q->end = NULL;
    else
        Q->front = temp->next;

    free(temp);

    return data;
}

void Clear(Queue Q)
{
    PtrToItem curr, temp;

    curr = Q->front;

    while(curr)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(Q);

}

int IsEmpty(Queue Q)
{
    return Q->front == NULL;
}

int Power(int x, int n)
{
    if(n == 0)
        return 1;
    else if( n % 2 )
        return Power(x*x, n/2) * x;
    else
        return Power(x*x, n/2);
}

// the Queue for information.
//

infoItem MakeItem(int pos, int space, int level, int newline)
{
    infoItem newItem = (infoItem)malloc(sizeof(struct infoNode));
    if(!newItem)
        Error1("out of space for infoNode");

    newItem->pos = pos;
    newItem->space = space;
    newItem->level = level;
    newItem->newline = newline;
    newItem->next = NULL;

    return newItem;
}

infoQ CreateInfoQ(void)
{
    infoQ Q = (infoQ)malloc(sizeof(struct infoQrec));
    if(!Q)
        Error1("out of space for infoQ");

    Q->front = Q->end = NULL;

    return Q;
}

void Pushback(infoQ Q, infoItem item)
{
    infoItem newItem = item;

    if(!Q->end)
        Q->front = Q->end = newItem;
    else
    {
        Q->end->next = newItem;
        Q->end = newItem;
    }
}

infoItem PopFront(infoQ Q)
{
    infoItem item;

    if(!Q->front)
        Error1("the Queue is empty");

    item = Q->front;

    if(item->next == NULL)
        Q->front = Q->end = NULL;
    else
        Q->front = item->next;

    return item;
}

void ClearInfoQ(infoQ Q)
{
    infoItem curr, temp;

    curr = Q->front;

    while(curr)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(Q);

}

int InfoQEmpty(infoQ Q)
{
    return Q->front == NULL;
}

// the tree will look better and prettier,
// because the NULL nodes will also be printed.
// but also acquire a larger screen because
// this function divides the screen into
// many blocks, so the space here is consuming.
//
// |  |  |  |33|  |  |  |
// |  |22|  |  |  |44|  |
// |11|  |29|  |40|  |55|
//
// the key idea of this program is:
// while the node is not at the bottom,
// no matter if there is a node in the tree,
// we create a infoItem with the printing information,
// and push a NULL into the Queue.
// when we pop the elements out of the Queue,
// if the Node it contains is a NULL, we print some
// blank block, otherwise we print the key in the Node.


void PrintDepth(SearchTree T)
{
    Position currNode;
    Queue Q = CreateQ();
    infoQ IQ = CreateInfoQ();
    infoItem newInfo, currInfo, preInfo;
    int height = GetHeight(T);
    int ScreenWidth = Power(2, height+1);
    int pos, level, space, newline;
    int dataWidth = 1;
    int i;

    InQ(Q, T);
    level = 1;
    pos = ScreenWidth >> level;
    space = pos;
    newline = TRUE;

    newInfo = MakeItem(pos, space, level, newline);
    Pushback(IQ, newInfo);

    preInfo = newInfo;

    while(!IsEmpty(Q))
    {
        currNode = OutQ(Q);
        currInfo = PopFront(IQ);

        if(currInfo->newline)
            printf("\n");

        for(i=0; i<currInfo->space; i++)
            printf(" ");                   // note dataWidth = 2.

        if(currNode)
            printf("%d",currNode->key);
        else
            printf(" ");

        if(currInfo->level < height+1)
        {
            level = currInfo->level + 1;
            pos = currInfo->pos - (ScreenWidth >> level);
            if(level > preInfo->level)
            {
                newline = TRUE;
                space = pos;
            }
            else
            {
                newline = FALSE;
                space = pos - preInfo->pos;
            }

            space--;
            newInfo = MakeItem(pos, space, level, newline);

            Pushback(IQ, newInfo);

            preInfo = newInfo;

            if(currNode)
            {
                if(currNode->LeftChild)
                    InQ(Q, currNode->LeftChild);
                else
                    InQ(Q, NULL);
            }
            else
                InQ(Q, NULL);

            pos = currInfo->pos + (ScreenWidth >> level);
            newline = FALSE;
            space = pos - preInfo->pos;
            space--;

            newInfo = MakeItem(pos, space, level, newline);

            Pushback(IQ, newInfo);

            if(currNode)
            {
                if(currNode->RightChild)
                    InQ(Q, currNode->RightChild);
                else
                    InQ(Q, NULL);
            }
            else
                InQ(Q, NULL);

            preInfo = newInfo;

        }

    }

    printf("\n\n");
}


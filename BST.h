#include<stdio.h>
#include<stdlib.h>

// definition of the Tree.

struct Node {
	int key;
	struct Node *LeftChild;
	struct Node *RightChild;
};

typedef struct Node *Position;
typedef struct Node *SearchTree;

int GetHeight(SearchTree T);
SearchTree Insert(SearchTree T, int data);
Position Find(SearchTree T, int data);
SearchTree Delete(SearchTree T, int data);
Position FindMin(SearchTree T);

void Error1(char *s);

// Definition of the Queue of Nodes.

typedef Position ElementType;

struct Q_Item {
    ElementType data;
    struct Q_Item *next;
};

typedef struct Q_Item *PtrToItem;

struct Qrec {
    PtrToItem front, end;
};

typedef struct Qrec *Queue;

Queue CreateQ(void);
void InQ(Queue Q, ElementType data);
ElementType OutQ(Queue Q);
void Clear(Queue Q);
int IsEmpty(Queue Q);
int Power(int x, int n);

// Definition of the Queue of the info needed in PrintDepth.

struct infoNode {
    int pos;
    int space;
    int level;
    int newline;
    struct infoNode *next;
};

typedef struct infoNode *infoItem;

struct infoQrec {
    infoItem front, end;
};

typedef struct infoQrec *infoQ;

infoItem MakeItem(int pos, int space, int level, int newline);
infoQ CreateInfoQ(void);
void Pushback(infoQ Q, infoItem item);
infoItem PopFront(infoQ Q);
int InfoQEmpty(infoQ Q);

// the final function is here

void PrintDepth(SearchTree T);
void PrintDepth_2(SearchTree T);














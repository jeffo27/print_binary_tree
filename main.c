#include"BST.h"

int main(void)
{
	int i, n;
	int key;
    SearchTree T = NULL;
	FILE *fp;

	printf("enter the number of nodes in the tree:");
	scanf("%d",&n);

	fp = fopen("input.in", "r");

	for(i=0; i<n; i++)
    {
        fscanf(fp,"%d",&key);
        T = Insert(T, key);     // remember assign the returned Tree to T.
    }

    PrintDepth(T);

	return 0;
}



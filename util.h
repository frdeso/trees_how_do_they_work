typedef struct node{
	int value;
	struct node *left;
	struct node *right;
}node;
void PrintNode(node *n)
{
	printf("\\%d\n",n->value);
}

void PrintLine()
{
	int i;	
	printf("\n");
	for(i = 0; i< 80; ++i)
		printf("-");
	printf("\n");
}

node* CreateNode(int value)
{
	struct	node *newNode;
	newNode = malloc(sizeof(node));

	newNode->value= value;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

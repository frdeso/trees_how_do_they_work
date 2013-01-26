#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "util.h"




/*
 Inserting a node in a totaly un-balanced way
*/
void InsertNode(int value, struct node *root)
{
	if(value >= root->value)
	{
		if(root->right == NULL)
			root->right = CreateNode(value);
		else
			InsertNode(value, root->right);	
	}
	else
	{
		
		if(root->left == NULL)
			root->left = CreateNode(value);
		else
			InsertNode(value, root->left);
	}
}

void PrintTreePreOrder(node *n, short depth)
{
	if(n != NULL)
	{
		int i;
		for(i = 0;i<depth;++i)
			printf("|");
		PrintNode(n);
		PrintTreePreOrder(n->left,depth + 1);
		PrintTreePreOrder(n->right,depth + 1);
	}
	return;
}

void PrintTreeInOrder(node *n)
{
	if(n->left != NULL)
		PrintTreeInOrder(n->left);

	PrintNode(n);

	if(n->right != NULL)
		PrintTreeInOrder(n->right);
}

int FindTreeDepth(node *n)
{
	if(n == NULL)
		return 0;
	int left_depth = FindTreeDepth(n->left);
	int right_depth = FindTreeDepth(n->right);
	if(left_depth > right_depth)
		return left_depth + 1;
	else
		return right_depth + 1; 
}

void PrintBFS(node *n)
{
	printf("Breadth-First Search \n");
	GQueue *q = g_queue_new();
	
	node * current;

	if(n == NULL)
		return;

	g_queue_push_tail(q,n);
	
	while(!g_queue_is_empty(q))
	{
		current = g_queue_pop_head(q);
		if(current != NULL)
		{
			PrintNode(current);

			g_queue_push_tail(q, current->left);
			g_queue_push_tail(q, current->right);
		}
	}

	g_queue_free(q);
}

void PrintReverseBFS(node *n)
{

	printf("Reverse Breadth-First Search \n");
	GQueue *q = g_queue_new();
	GQueue *s = g_queue_new();

	node * current;

	if(n == NULL)
		return;

	g_queue_push_tail(q,n);
	
	while(!g_queue_is_empty(q))
	{
		current = g_queue_pop_head(q);
		if(current != NULL)
		{
			g_queue_push_head(s, current);

			g_queue_push_tail(q, current->left);
			g_queue_push_tail(q, current->right);
		}
	}

	int i, size = g_queue_get_length(s);

	for(i = 0; i<size;++i)
	{
		current = g_queue_pop_head(s);
		PrintNode(current);
	}
	g_queue_free(s);
	g_queue_free(q);
}


GQueue *getAllNodes(node *n, GQueue *q)
{
	if(n->left != NULL)
		q = getAllNodes( n->left, q);

	g_queue_push_tail(q,n);

	if(n->right != NULL)
		q = getAllNodes(n->right, q);
	return q;

}
/*int isBalanced(node *n)
{
	int right = 1,left = 1;
	if(n->left != NULL)
		left =  isBalanced(n->left);
	if(n->right != NULL)
		right = isBalanced(n->right);

	return(left && right) left && right && abs(FindTreeDepth(n->left)-FindTreeDepth(n->right)) <=1;
}*/
void AddToBalancedTree(node *root, node *n)
{
	if(n->value >= root->value)
	{
		if(root->right == NULL)
			root->right = n;
		else
			AddToBalancedTree(root->right, n);	
	}
	else
	{
		if(root->left == NULL)
			root->left = n;
		else
			AddToBalancedTree(root->left, n);
	}


}

node *BalanceThatTree(node *n)
{
	
	printf("Get elements... \n");
	GQueue *q = g_queue_new();
	
	q = getAllNodes(n, q);
	node *current;
	int i;
	int size = g_queue_get_length(q);
	for(i = 0;i < size;++i)
	{
		current = g_queue_peek_nth(q, i);
		PrintNode(current);
	}
	
	printf("Creating balanced tree...");

	node *root = g_queue_pop_head(q); 
	for(i = 0;i < size;++i)
	{
		current = g_queue_peek_nth(q, i);
		AddToBalancedTree(root, current);
	}	
	g_queue_free(q);
}

int main()
{
	node *root;

	root = CreateNode(100);
	InsertNode(15,root);
	InsertNode(140,root);
	InsertNode(108,root);
	InsertNode(63,root);
	InsertNode(45,root);
	InsertNode(75,root);
	InsertNode(132,root);
	InsertNode(30,root);

	InsertNode(10,root);
	InsertNode(8,root);
	InsertNode(150,root);
	InsertNode(24,root);
	InsertNode(80,root);
	InsertNode(102,root);
	InsertNode(120,root);
	InsertNode(99,root);


	PrintLine();
	printf("depth : %d",FindTreeDepth(root));

	PrintLine();

	PrintTreePreOrder(root, 0);
	
	PrintLine();

	PrintTreeInOrder(root);
	
	PrintLine();

	PrintBFS(root);

	PrintLine();
	PrintReverseBFS(root);
	return 0;
}

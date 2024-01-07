/*
Description
Each node of a binary tree has a field id which is the identifier of the node. Build a binary tree and check if the tree is a balanced tree, compute the height of the given tree (the number of nodes of the tree can be upto 50000)
Input
Line 1 contains MakeRoot u: make the root of the tree having id = u
Each subsequent line contains: AddLeft or AddRightcommands with the format
AddLeft u v: create a node having id = u, add this node as a left-child of the node with id = v (if not exists)
AddRight u v: create a node having id = u, add this node as a right-child of the node with id = v (if not exists)
The last line contains * which marks the end of the input
Output
Write two integers z and h (separated by a SPACE character) in which h is the height (the number of nodes of the longest path from the root to a leaf) and z = 1 if the tree is balanced and z = 0, otherwise

Example
Input
MakeRoot 1
AddLeft 2 1
AddRight 3 1
AddLeft 9 2
AddRight 4 2
AddLeft 6 3
AddRight 5 3
AddLeft 7 4
AddRight 8 4
*
Output
1 4
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int id;
	struct node* left;
	struct node* right;
}node;

node* makeNode(int id)
{
	node* p = malloc(sizeof(node));
	p->id = id;
	p->left = NULL;
	p->right = NULL;
	return p;
}

node* findNode(node* root, int id)
{
	if(root == NULL || root->id == id) return root;
	node* p = findNode(root->left, id);
	if(p != NULL) return p;
	else return findNode(root->right, id);
}

node* addleft(node* root, int child, int dad)
{
	node* p = findNode(root, dad);
	if(p != NULL)
	{
		p->left = makeNode(child);
	}
	return root;	
}

node* addright(node* root, int child, int dad)
{
	node* p = findNode(root, dad);
	if(p != NULL)
	{
		p->right = makeNode(child);
	}
	return root;
}

int height(node* root)
{
	if(root == NULL) return 0;
	int lh = height(root->left);
	int rh = height(root->right);
	return fmax(lh, rh) + 1;
}

int isbalance(node *root)
{
	if(root == NULL) return 1;
	int lh = height(root->left);
	int rh = height(root->right);
	if(abs(lh - rh) <= 1 && isbalance(root->left) && isbalance(root->right)) return 1;
	else return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	node* root = NULL;
	char cmd[10];
	while(scanf("%s", cmd) == 1)
	{
		if(strcmp(cmd, "MakeRoot") == 0)
		{
			int id; scanf("%d", &id);
			root = makeNode(id);
		}
		if(strcmp(cmd, "AddLeft") == 0)
		{
			int child, dad; scanf("%d %d", &child, &dad);
			root = addleft(root, child, dad);
		}
		if(strcmp(cmd, "AddRight") == 0)
		{
			int child, dad; scanf("%d %d", &child, &dad);
			root = addright(root, child, dad);
		}
		if(strcmp(cmd, "*") == 0) break;
	}
	int h = height(root);
	int z = isbalance(root);
	printf("%d %d\n", z, h);
}



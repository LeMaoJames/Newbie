#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char key[10];
	int mass;
	struct Node *left;
	struct Node *right;
}Node; 

Node *makeNode(char *key, int mass)
{
	Node* p = malloc(sizeof(Node));
	strcpy(p->key, key);
	p->mass = mass;
	p->left = NULL;
	p->right = NULL;
	return p;
}

Node *insert(Node *root, char *key, int mass)
{
	Node *p = makeNode(key, mass);
	if(root == NULL) return p;
	int c = strcmp(root->key, key);
	if(c > 0)
	{
		if(root->left == NULL) root->left = p;
		else root->left = insert(root->left, key, mass);
	}
	else if(c < 0)
	{
		if(root->right == NULL) root->right = p;
		else root->right = insert(root->right, key, mass);
	}
	return root;
}

Node *find(Node *root, char *key)
{
	if(root == NULL) return NULL;
	int c = strcmp(root->key, key);
	if(c > 0)
	{
		find(root->left, key);
	}
	else if(c < 0)
	{
		find(root->right, key);
	}
	else return root;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n; scanf("%d", &n);
	char key[10]; 
	int mass;
	Node *root = NULL;
	for(int i = 0; i < n; i++)
	{
		scanf("%s %d", key, &mass);
		root = insert(root, key, mass);
	}
	int m; scanf("%d", &m);
	int item, num;
	for(int i = 0; i < m; i++)
	{
		scanf("%d", &item);
		int sum = 0;
		for(int j = 0; j < item; j++)
		{
			scanf("%s %d", key, &num);
			Node *p = find(root, key);
			sum += num * p->mass;
		}
		printf("%d\n", sum);
	}
	return 0;
}

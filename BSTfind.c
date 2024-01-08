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
	if(root->id < id)
    {
        return findNode(root->right, id);
    }
    else return findNode(root->left, id);
}

node* insert(node* root, int id)
{
    if(root == NULL) return makeNode(id);
    node* p = findNode(root, id);
    if(p != NULL) return root;
    else if(root->id > id)
    {
        root->left = insert(root->left, id);
    }
    else root->right = insert(root->right, id);
    return root;
}

void preorder(node* root)
{
    if(root == NULL) return;
    printf("%d ", root->id);
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    freopen("input.txt", "r", stdin);
    node* root = NULL;
    char cmd[10];
    while(scanf("%s", cmd) == 1)
    {
        if(strcmp(cmd, "insert") == 0)
        {
            int id; scanf("%d", &id);
            root = insert(root, id);
        }
        if(strcmp(cmd, "find") == 0)
        {
            int id; scanf("%d", &id);
            node* p = findNode(root, id);
            if(p != NULL)
            {
            	printf("%d\n", p->id);
			}
			else printf("Not found\n");
        }
        if(strcmp(cmd, "#") == 0)
        {
            break;
        }
    }
	return 0;
}




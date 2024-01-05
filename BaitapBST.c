// Một trung tâm mua sắm trực tuyến có n mặt hàng, trong bài tập này đối với mỗi mặt hàng chúng ta chỉ quan tâm đến mã số và trọng lượng của mặt hàng. Mã số có không quá 9 ký tự, còn trọng lượng là số nguyên (được tính bằng gam). Các đơn hàng được tạo liên tục và cần tính tổng trọng lượng các sản phẩm trong đơn hàng.
// Dữ liệu đầu vào được cho như sau:
// Đầu tiên là số n (<100 000) là số lượng mặt hàng.
// Sau đó là n dòng, mỗi dòng chứa 1 cặp mã số và trọng lượng của mặt hàng tương ứng.
// Tiếp đó là số m (< 10000) - số lượng đơn hàng.
// Cuối cùng là m dòng mỗi dòng mô tả 1 đơn hàng bao gồm: đầu tiên là số k - số lượng mục hàng trong đơn hàng, sau đó là k cặp gồm mã số sản phẩm và số lượng sản phẩm.
// Dữ liệu đầu ra:
// Chương trình xuất ra 1 số nguyên là trọng lượng tương ứng với mỗi đơn hàng.
// Ví dụ,
// Đầu vào:
// 3
// a11 150
// a12 500
// a20 200
// 2
// 1 a11 2
// 2 a12 1 a20 3
// Đầu ra:
// 300
// 1100
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

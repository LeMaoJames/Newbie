// Description
// Mỗi nút của cây có trường id (số nguyên duy nhất, không trùng lặp)
// Thực hiện 1 chuỗi các hành động sau đây bao gồm các thao tác liên quan đến xây dựng cây và duyệt cây:
// MakeRoot u: Tạo ra nút gốc u của cây
// Insert u v: tạo mới 1 nút u và chèn vào cuối danh sách nút con của nút v
// PreOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự trước
// InOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự giữa
// PostOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự sau
// Dữ liệu: bao gồm các dòng, mỗi dòng là 1 trong số các hành động được mô tả ở trên, dòng cuối dùng là * (đánh dấu sự kết thúc của dữ liệu).
// Kết quả: ghi ra trên mỗi dòng, thứ tự các nút được thăm trong phép duyệt theo thứ tự trước, giữa, sau của các hành động $PreOrder, $InOrder, $PostOrder tương ứng đọc được từ dữ liệu đầu vào
// Ví dụ
// Dữ liệu
// MakeRoot 10
// Insert 11 10
// Insert 1 10
// Insert 3 10
// InOrder
// Insert 5 11
// Insert 4 11
// Insert 8 3
// PreOrder
// Insert 2 3
// Insert 7 3
// Insert 6 4
// Insert 9 4
// InOrder
// PostOrder
// *

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int id;
	struct Node* left;
	struct Node* rsib;
}Node;

Node* root = NULL;

Node* makeNode(int id)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->id = id;
	newNode->left = newNode->rsib = NULL;
	return newNode;
}

Node* findNode(Node* r, int id)
{
	if (r == NULL) return NULL;
	if(r->id == id) return r;
	Node *p = r->left;
	while(p != NULL)
	{
		Node *q = findNode(p, id);
		if (q != NULL)return q;
		p = p->rsib;
	}
}

void insertNode(int child, int dad)
{
	Node* p = findNode(root, dad);
	if(p->left == NULL) p->left = makeNode(child);
	else
	{
		Node* q = p->left;
		while(q->rsib != NULL)
		{
			q = q->rsib;
		}
		q->rsib = makeNode(child);
	}
	
}

void preOrder(Node* r)
{
	if(r == NULL) return;
	printf("%d ", r->id);
	for(Node *p = r->left; p != NULL; p = p->rsib)
	{
		preOrder(p);
	}
}

void inOrder(Node * root)
{
	if (root == NULL) return;
	Node * temp = root->left;
	inOrder(temp);
	printf("%d ", root->id);
	if (temp == NULL) return;
	for (Node * it = temp->rsib; it != NULL; it = it->rsib)
	{
		inOrder(it);
	}
}

void postOrder(Node *r)
{
	if(r == NULL) return;
	for(Node *p = r->left; p != NULL; p = p->rsib)
	{
		postOrder(p);
	}
	printf("%d ", r->id);
}

int main()
{
 	freopen("input.txt", "r", stdin);
	char input[10];
	while(scanf("%s", input) == 1)
	{
		if(strcmp(input, "*") == 0) break;
		
		if(strcmp(input, "MakeRoot") == 0)
		{
			int id; scanf("%d", &id);
			root = makeNode(id);
		}
		
		if(strcmp(input, "Insert") == 0)
		{
			int child, dad; scanf("%d %d", &child, &dad);
			insertNode(child, dad);
		}
		if(strcmp(input, "InOrder") == 0)
		{
			inOrder(root);
			printf("\n");
		}
		if(strcmp(input, "PreOrder") == 0)
		{
			preOrder(root);
			printf("\n");
		}
		if(strcmp(input, "PostOrder") == 0)
		{
			postOrder(root);
			printf("\n");
		}
	}
	return 0;
}


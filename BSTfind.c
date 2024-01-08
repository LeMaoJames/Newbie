/*
Description
Cho một cây nhị phân có khóa là kiểu số nguyên
Giả thiết tất cả các nút trong cây có khóa khác nhau.
Cài đặt các thao tác sau:
insert k: chèn một nút mới có khóa k vào cây, nếu trong cây đã có nút có khóa k thì không thêm vào
preorder: in (trên một dòng mới) thứ tự các khóa của cây khi thăm theo kiểu Pre-Order traversal (mỗi phần tử cách nhau bởi một kí tự trắng)
find k: tìm nút có khóa k trong cây. Nếu không tìm thấy thì In ra màn hình: Not found. Nếu tìm thấy in ra màn hình khóa k. Sau khi in xuống dòng.
Input
Mỗi dòng chứa một trong các câu lệnh trên
Việc nhập liệu kết thúc bằng một dòng chứa kí tự #
Output
Ghi ra màn hình kết quả của các câu lệnh preorder hoặc find
Example
Input
insert 5
insert 9
insert 2
insert 1
find 3
#
Output
Not found
Example
Input
insert 5
insert 9
insert 2
insert 1
find 2
#
Output
2
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




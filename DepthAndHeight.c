/*
Mỗi nút trên 1 cây có trường id (identifier) là một số nguyên (id của các nút trên cây đôi một khác nhau)
Thực hiện 1 chuỗi các hành động sau đây bao gồm các thao tác liên quan đến xây dựng cây và duyệt cây
· MakeRoot u: Tạo ra nút gốc u của cây
· Insert u v: tạo mới 1 nút u và chèn vào cuối danh sách nút con của nút v (nếu nút có id bằng v không tồn tại hoặc nút có id bằng u đã tồn tại thì không thêm mới)
· Height u: Tính và trả về độ cao của nút u
· Depth u: Tính và trả về độ sâu của nút u
Biết rằng dữ liệu đầu vào có 1 lệnh duy nhất là MakeRoot và luôn ở dòng đầu tiên
· Dữ liệu: bao gồm các dòng, mỗi dòng có định dạng như mô tả ở trên, trong đó dòng cuối dùng ghi * (dấu hiệu kết thúc dữ liệu)
· Kết quả: ghi ra mỗi dòng kết quả của các lệnh Height và Depth tương ứng đọc được từ đầu vào
Ví dụ:
Dữ liệu
MakeRoot 10
Insert 11 10
Insert 1 10
Insert 3 10
Insert 5 11
Insert 4 11
Height 10
Depth 10
Insert 8 3
Insert 2 3
Insert 7 3
Insert 6 4
Insert 9 4
Height 10
Depth 10
Depth 3
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int id;
	struct node* left;
	struct node* rsib;
}node;

node* makeNode(int id)
{
	node* p = malloc(sizeof(node));
	p->id = id;
	p->left = NULL;
	p->rsib = NULL;
	return p;
}

node* findNode(node* root, int id)
{
    if(root == NULL || root->id == id) return root;
    for(node* p = root->left; p != NULL; p = p->rsib)
    {
        node* q = findNode(p, id);
        if(q != NULL) return q;
    }
}

node* insert(node* root, int child, int dad)
{
    if(root == NULL) return root;
    node* p = findNode(root, dad);
    if(p->left == NULL)
    {
        p->left = makeNode(child);
    }
    else
    {
        node* q = p->left;
        while(q->rsib != NULL)
        {
            q = q->rsib;
        }
        q->rsib = makeNode(child);
    }
    return root;
}

int height(node* r)
{
    if(r == NULL) return 0;
    int maxh = 0;
    for(node* p = r->left; p != NULL; p = p->rsib)
    {
        maxh = fmax(maxh, height(p));
    }
    return maxh + 1;

}

int levelUtil(node* root, int id, int level)
{
    if(root == NULL) return 0;
    if(root->id == id) return level;
    for(node* p = root->left; p != NULL; p = p->rsib)
    {
        int downlevel = levelUtil(p, id, level + 1);
        if(downlevel != 0) return downlevel;
    }
}

int getlevel(node* root, int id)
{
    levelUtil(root, id, 1);
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
        if(strcmp(cmd, "Insert") == 0)
        {
            int child, dad; scanf("%d %d", &child, &dad);
            root = insert(root, child, dad);
        }
        if(strcmp(cmd, "Height") == 0)
        {
            int id; scanf("%d", &id);
            node* p = findNode(root, id);
            printf("%d\n", height(root) - getlevel(root, id) + 1);
        }
        if(strcmp(cmd, "Depth") == 0)
        {
            int id; scanf("%d", &id);
            printf("%d\n", getlevel(root, id));
        }
        if(strcmp(cmd, "*") == 0) break;
    }
	return 0;
}




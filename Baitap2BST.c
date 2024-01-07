/*
Giả sử bạn đang phát triển dịch vụ quản lý sản phẩm cho 1 cửa hàng trực tuyến. Trong phạm vi bài tập này với mỗi sản phẩm chúng ta chỉ quan tâm tới mã sản phẩm, giá bán và số lượng trong kho. Mã sản phẩm có không quá 9 ký tự, giá bán (vnd) và số lượng trong kho là các số nguyên.
Dịch vụ cần xử lý các yêu cầu sau: Thêm sản phẩm, cập nhật giá bán, xóa sản phẩm, kiểm tra và đặt hàng.
Dữ liệu đầu vào được cung cấp như sau:
Đầu tiên là 1 số nguyên n (< 100000) - số lượng sản phẩm, sau đó là n dòng, mỗi dòng chứa thông tin về 1 sản phẩm gồm có Mã sản phẩm, số lượng hiện có trong kho và giá bán hiện tại.
Sau đó là 1 số nguyên m (< 10000) - số lượng yêu cầu cần xử lý,
tiếp sau đó là m dòng, mỗi dòng là 1 yêu cầu cần xử lý.
Trên mỗi dòng là mã yêu cầu và các tham số cần thiết.
a) Nếu mã yêu cầu là add (thêm sản phẩm) thì các tham số tiếp theo là mã sản phẩm, số lượng. Nếu là sản phẩm mới thì giá bán để là -1 (giá trị không hợp lệ).  Nếu ngược lại thì cập nhật số lượng sản phẩm trong kho. Cuối cùng xuất ra số lượng sản phẩm và giá bán hiện tại của sản phẩm đó.
b) Nếu mã yêu cầu là update (cập nhật sản phẩm) thì các tham số tiếp theo là mã sản phẩm và giá sản phẩm. Nếu mã sản phẩm không tồn tại thì xuất ra thông báo "San pham khong ton tai". Nếu ngược lại thì xuất ra giá cũ và giá mới của sản phẩm sau khi cập nhật.
c) Nễu mã yêu cầu là delete (xóa sản phẩm) thì tham số tiếp theo là mã sản phẩm. Nếu mã sản phẩm không tồn tại thì xuất ra thông báo "San pham khong ton tai". Nếu ngược lại thì xóa sản phẩm và đưa ra thông báo "Da xoa san pham". (Trong thực tế có thể hạn chế sử dụng yêu cầu xóa)
d) Nếu mã yêu cầu là check thì tham số tiếp theo là mã sản phẩm. Nếu tìm thấy mã sản phẩm thì xuất ra số lượng và giá hiện tại của sản phẩm. Nếu ngược lại thì đưa ra thông báo "San pham khong ton tai".
e) Nếu mã yêu cầu là order (đặt hàng) thì các tham số tiếp theo là mã sản phẩm và số lượng. Nếu mã sản phẩm không tồn tại thì đưa ra thông báo "San pham khong ton tai", nếu ngược lại và số lượng vượt quá số lượng trong kho thì xuất ra thông báo "Khong du so luong", nếu ngược lại và giá đang là 1 giá trị không hợp lệ (< 0) thì đưa ra thông báo "Khong the dat hang san pham chua co gia", nếu ngược lại (có sản phẩm, đủ số lượng và giá hợp lệ) thì cập nhật giảm số lượng sản phẩm trong kho và đưa ra thông báo "Da dat hang", sau đó đưa ra số lượng sản phẩm còn lại trong kho sau khi đã cập nhật và tổng giá trị hàng đã đặt.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char key[10];
	int gia;
	int sl;
	struct node* left;
	struct node* right;
}node;

node* makeNode(char *key, int gia, int sl)
{
	node *p = malloc(sizeof(node));
	strcpy(p->key, key);
	p->gia = gia;
	p->sl = sl;
	p->left = NULL;
	p->right = NULL;
	return p;
}

node* insert(node *root, char* key, int sl, int gia)
{
	node* p = makeNode(key, gia, sl);
	if(root == NULL) return p;
	int c = strcmp(p->key, root->key);
	if(c < 0)
	{
		root->left = insert(root->left, key, sl, gia);
	}
	else if(c > 0)
	{
		root->right = insert(root->right, key, sl, gia);
	}
	return root;
}

node* find(node *root, char* key)
{
	if(root == NULL) return root;
	int c = strcmp(root->key, key);
	if(c == 0) return root;
	else if(c > 0)
	{
		return find(root->left, key);
	}
	else if(c < 0)
	{
		return find(root->right, key);
	}
}

node* findMin(node *r)
{
	if(r == NULL) return r;
	node* p = r;
	while(p->left != NULL)
	{
		p = p->left;
	}
	return p;
}

node* deleteNode(node *root, char* key)
{
	if(root == NULL) return root;
	int c = strcmp(root->key, key);
	if(c > 0)
	{
		root->left = deleteNode(root->left, key);
		return root;
	}
	else if(c < 0)
	{
		root->right = deleteNode(root->right, key);
		return root;
	}
	else
	{
		if(root->left == NULL)
		{
			node* tmp = root->right;
			free(root);
			return tmp;
		}
		else if(root->right == NULL)
		{
			node* tmp = root->left;
			free(root);
			return tmp;
		}
		else
		{
			node* tmp = findMin(root->right);
			strcpy(root->key, tmp->key);
			root->gia = tmp->gia;
			root->sl = tmp->sl;
			root->right = deleteNode(root->right, tmp->key);
		}
		return root;
	}
	
	
}

int main()
{
	freopen("input.txt", "r", stdin);
	char cmd[8];
	node* root = NULL;
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		int gia, sl;
		char key[10];
		scanf("%s %d %d", key, &sl, &gia);
		root = insert(root, key, sl, gia);
	}
	int m; scanf("%d", &m);
	int gia, sl;
	char key[10];
	for(int i = 0; i < m; i++)
	{
		scanf("%s", cmd);
		if(strcmp(cmd, "add") == 0)
		{
			scanf("%s %d", key, &sl);
			node* p = find(root, key);
			if(p != NULL)
			{
				p->sl += sl;
				printf("%d %d\n", p->sl, p->gia);
			}
			else
			{
				root = insert(root, key, sl, -1);
				printf("%d -1\n", sl);
			}
		}
		if(strcmp(cmd, "update") == 0)
		{
			scanf("%s %d", key, &gia);
			node* p = find(root, key);
			if(p != NULL)
			{
				printf("%d %d\n", p->gia, gia);
				p->gia = gia;
			}
			else
			{
				printf("San pham khong ton tai\n");
			}
			
		}
		if(strcmp(cmd, "delete") == 0)
		{
			scanf("%s", key);
			node *p = find(root, key);
			if(p != NULL)
			{
				root = deleteNode(root, key);
				printf("Da xoa san pham\n");
			}
			else
			{
				printf("San pham khong ton tai\n");
			}
		}
		if(strcmp(cmd, "check") == 0)
		{
			scanf("%s", key);
			node *p = find(root, key);
			if(p != NULL)
			{
				printf("%d %d\n", p->sl, p->gia);
			}
			else
			{
				printf("San pham khong ton tai\n");
			}
		}
		if(strcmp(cmd, "order") == 0)
		{
			scanf("%s %d", key, &sl);
			node* p = find(root, key);
			if(p == NULL)
			{
				printf("San pham khong ton tai\n");
			}
			else
			{
				if(p->sl < sl)
				{
					printf("Khong du so luong\n");
				}
				else if(p->gia == -1)
				{
					printf("Khong the dat hang san pham chua co gia\n");
				}
				else
				{
					p->sl -= sl;
					printf("Da dat hang %d %d\n", p->sl, sl * (p->gia));
				}
			}
		}
	}
	return 0;
}

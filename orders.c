/*
Dữ liệu bán hàng trong 1 cửa hàng trực tuyến bao gồm 1 dãy các dòng, mỗi dòng biểu diễn 1 đơn hàng có các thông tin như sau:
<CustomerID> <ProductID> <Price> <ShopID> <TimePoint>
trong đó:
<CustomerID>: chuỗi có độ dài từ 3 tới 10
<ProductID>: chuỗi có độ dài từ 3 tới 10
<Price>: Giá là số nguyên dương từ 1 tới 1000
<ShopID>: Chuỗi độ dài từ 3 tới 10
<TimePoint>: chuỗi biểu diễn thời gian theo định dạng HH:MM:SS
Hãy thực hiện 1 chuỗi truy vấn theo định dạng sau:

?total_number_orders - Trả về số lượng đơn hàng.
?total_revenue: Trả về tổng thu nhập của công ty
?revenue_of_shop <ShopID>: Trả về tổng thu nhập của cửa hàng.
?total_consume_of_customer_shop <CustomerID> <ShopID>: Trả vể tổng giá trị hóa đơn của khách hạng tại cửa hàng.
?total_revenue_in_period <from_time> <to_time>: Trả về tổng thu nhập của công ti trong khoảng thời gian (bao gồm cả 2 đầu mút).
Ví dụ:
Đầu vào:
C001 P001 10 SHOP001 10:30:10
C001 P002 30 SHOP001 12:30:10
C003 P001 40 SHOP002 10:15:20
C001 P001 80 SHOP002 08:40:10
C002 P001 130 SHOP001 10:30:10
C002 P001 160 SHOP003 11:30:20
#
?total_number_orders
?total_revenue
?revenue_of_shop SHOP001
?total_consume_of_customer_shop C001 SHOP001 
?total_revenue_in_period 10:00:00 18:40:45
#
Đầu ra:
6
450
170
40
370
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct shop
{
	char cusID[11];
	char shopID[11];
	int price;
}shop;

typedef struct timetp
{
	char timep[9];
	int price;
}timetp;

int cmpshop(const void* a, const void* b)
{
	char* shop2 = ((shop*)a)->shopID;
	char* shop1 = ((shop*)b)->shopID;
	int c = strcmp(shop2, shop1);
	if(c > 0) return 1;
	else if(c < 0) return -1;
	else if(c == 0) return 0;
}

int cmptime(const void* a, const void* b)
{
	char* time2 = ((timetp*)a)->timep;
	char* time1 = ((timetp*)b)->timep;
	int c = strcmp(time2, time1);
	if(c > 0) return 1;
	else if(c < 0) return -1;
	else if(c == 0) return 0;
}

int ShopSearch(shop* ashop, int l, int r, char* shopID)//tra ve vi tri dau tien 
{
	int res = -1;
	while(l <= r)
	{
		int m = l + (r - l) / 2;
		int c = strcmp(ashop[m].shopID, shopID);
		if(c > 0)
		{
			r = m - 1;
		}
		else if(c < 0)
		{
			l = m + 1;
		}
		else if(c == 0)
		{
			res = m;
			r = m - 1;
		}
	}
	return res;
}

int lower_boundtime(timetp* atime, int n, char* timep)
{
	int mid;
	int low = 0;
	int high = n;
	while(low < high)
	{
		mid = low + (high - low) / 2;
		if(strcmp(timep, atime[mid].timep) <= 0)
		{
			high = mid;
		}
		else low = mid + 1;
	}
	if(low < n && strcmp(atime[low].timep, timep) < 0)
	{
		low++;
	}
	return low;
}

int upper_boundtime(timetp* atime, int n, char* timep)
{
	int mid;
	int low = 0;
	int high = n;
	while(low < high)
	{
		mid = low + (high - low) / 2;
		if(strcmp(timep, atime[mid].timep) >= 0)
		{
			low = mid + 1;
		}
		else high = mid;
	}
	if(low < n && strcmp(atime[low].timep, timep) <= 0)
	{
		low++;
	}
	return low;
}

int ShopCusSearch(shop* ashop, int l, int r, char* shopID, char* cusID)
{
	int p = ShopSearch(ashop, l, r, shopID);
	if(p == -1) return p;
	else while(strcmp(ashop[p].shopID, shopID) == 0)
	{
		if(strcmp(ashop[p].cusID, cusID) == 0) return p;
		else p++;
	}
	return -1;
}



int main()
{
//	freopen("input.txt", "r", stdin);
	shop* ashop = malloc(100001 * sizeof(shop));
	timetp* atime = malloc(100001 * sizeof(timetp));
	int ishop = 0;
	int itime = 0;
	char cusID[11], pID[11], shopID[11], timep[9];
	int price;
	while(scanf("%s", cusID) == 1)
	{
		if(strcmp(cusID, "#") == 0) break;
		scanf("%s", pID);
		scanf("%d", &price);
		scanf("%s", shopID);
		scanf("%s", timep);
		//insert vao mang time
		strcpy(atime[itime].timep, timep);
		atime[itime].price = price;
		itime++;
		//xu ly insert mang shop
		int found = 0;
		for(int i = 0; i < ishop; i++)
		{
			if(strcmp(ashop[i].shopID, shopID) == 0 && strcmp(ashop[i].cusID, cusID) == 0)
			{
				ashop[i].price += price;
				found = 1;
			}
		}
		if(!found) //khong tim thay thi chen
		{
			strcpy(ashop[ishop].shopID, shopID);
			strcpy(ashop[ishop].cusID, cusID);
			ashop[ishop].price = price;
			ishop++;
		}
	}
	qsort(ashop, ishop, sizeof(shop), cmpshop);
	qsort(atime, itime, sizeof(timetp), cmptime);
//	for(int i = 0; i < ishop; i++)
//	{
//		printf("%s %s %d\n", ashop[i].cusID, ashop[i].shopID, ashop[i].price);
//	}
//	for(int i = 0; i < itime; i++)
//	{
//		printf("%s %d\n", atime[i].timep, atime[i].price);
//	}
	char cmd[50];
	while(scanf("%s", cmd) == 1)
	{
		if(strcmp(cmd, "#") == 0) break;
		if(strcmp(cmd, "?total_number_orders") == 0)
		{
			printf("%d\n", itime);
		}
		if(strcmp(cmd, "?total_revenue") == 0)
		{
			int total = 0;
			for(int i = 0; i < ishop; i++)
			{
				total += ashop[i].price;
			}
			printf("%d\n", total);
		}
		if(strcmp(cmd, "?revenue_of_shop") == 0)
		{
			scanf("%s", shopID);
			int p = ShopSearch(ashop, 0, ishop, shopID);
			int total = 0;
			for(int i = p; strcmp(ashop[i].shopID, shopID) == 0; i++)
			{
				total += ashop[i].price;
			}
			printf("%d\n", total);
		}
		if(strcmp(cmd, "?total_consume_of_customer_shop") == 0)
		{
			scanf("%s %s", cusID, shopID);
			int p = ShopCusSearch(ashop, 0, ishop, shopID, cusID);
			printf("%d\n", ashop[p].price);
		}
		if(strcmp(cmd, "?total_revenue_in_period") == 0)
		{
			char time1[9], time2[9];
			scanf("%s %s", time1, time2);
			int p = lower_boundtime(atime, itime, time1);
			int total = 0;
//			printf("%d\n", p);
			for(int i = p; strcmp(atime[i].timep, time2) <= 0 && i < itime; i++)
			{
				total += atime[i].price;
			}
			printf("%d\n", total);
		}
		
	}
	return 0;
}

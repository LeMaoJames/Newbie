#include <stdio.h>

int main()
{
	int n; scanf("%d", &n);
	int x[n];
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	int nh; scanf("%d", &nh);
	int h[nh];
	for(int i = 0; i < nh; i++)
	{
		scanf("%d", &h[i]);
	}
	int y[n];
	for(int i = 0; i < n; i++)
	{
		y[i] = 0;
		for(int k = 0; k < nh; k++)
		{
			//Tinh y[i]
			if(i - k >= 0)
			{
				y[i] += h[k] * x[i - k];
			}
			else break;
		}
		printf("y[%d] = %d\n", i, y[i]);
	}
}

#include <cstdio>

using namespace std;

int n;
double x1, y1, x2, y2, x3, y3, x4, y4;

int main()
{
	printf("INTERSECTING LINES OUTPUT\n");
	scanf("%d", &n);
	while (n--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		if ((x3 - x1) * (y3 - y2) == (y3 - y1) * (x3 - x2) && (x4 - x1) * (y4 - y2) == (y4 - y1) * (x4 - x2))
		{
			printf("LINE\n");
		}
		else if ((x2 - x1) * (y4 - y3) == (y2 - y1) * (x4 - x3))
		{
			printf("NONE\n");
		}
		else
		{
			double a = x2 - x1, b = y2 - y1, c = x4 - x3, d = y4 - y3, x, y;
			if (a == 0)
			{
				x = x1;
				y = (x1 - x3) * d / c + y3;
			}
			else if (c == 0)
			{
				x = x3;
				y = (x3 - x1) * b / a + y1;
			}
			else
			{
				x = (y3 - y1 + b * x1 / a - d * x3 / c) / (b / a - d / c);
				y = (x - x1) * b / a + y1;
			}
			printf("POINT %.2f %.2f\n", x, y);
		}
	}
	printf("END OF OUTPUT");
	return 0;
}

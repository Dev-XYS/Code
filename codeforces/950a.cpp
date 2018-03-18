// Problem Name: Left-handers, Right-handers and Ambidexters
// Source: Codeforces Round #469 (Div. 2), Problem A

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	int l, r, a;
	scanf("%d%d%d", &l, &r, &a);
	if (l > r)
	{
		swap(l, r);
	}
	if (a >= r - l)
	{
		printf("%d\n", r * 2 + ((a - (r - l)) & -2));
	}
	else
	{
		printf("%d\n", (l + a) * 2);
	}
	return 0;
}

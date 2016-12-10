#include <cstdio>

using namespace std;

int main()
{
	int n, f[50];
	scanf("%d", &n);
	f[1] = 1;
	f[2] = 1;
	for (int i = 3; i <= n; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
	printf("%d", f[n]);
	return 0;
}

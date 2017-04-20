// Problem Name: 谁能赢呢?
// Source: [中山市选]

#include <cstdio>

using namespace std;

int main()
{
	int n;
	while (true)
	{
		scanf("%d", &n);
		if (n == 0) break;
		printf("%s\n", (n & 1) == 0 ? "Alice" : "Bob");
	}
	return 0;
}

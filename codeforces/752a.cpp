#include <cstdio>

using namespace std;

int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	printf("%d %d %c", (k - 1) / (m * 2) + 1, ((k - (m * 2) * ((k - 1) / (m * 2))) + 1) / 2, (k & 1) == 0 ? 'R' : 'L');
	return 0;
}

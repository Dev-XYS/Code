#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, s[100010], t[100010];
bool has[100010];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &s[i]);
	}
	memcpy(t, s, sizeof(s));
	sort(t, t + n);
	int p = n - 1;
	for (int i = 0; i < n; i++)
	{
		has[s[i]] = true;
		if (s[i] == t[p])
		{
			while (has[t[p]] == true)
			{
				printf("%d ", t[p--]);
			}
		}
		printf("\n");
	}
	return 0;
}

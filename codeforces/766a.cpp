#include <cstdio>
#include <cstring>

using namespace std;

char a[100010], b[100010];

int main()
{
	scanf("%s%s", a, b);
	int la = strlen(a), lb = strlen(b);
	if (la != lb) printf("%d", la > lb ? la : lb);
	else printf("%d", strcmp(a, b) == 0 ? -1 : la);
	return 0;
}

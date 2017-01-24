#include <cstdio>
#include <algorithm>

using namespace std;

int n, d[500010];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &d[i]);
    }
    sort(d, d + n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", d[i]);
    }
    return 0;
}

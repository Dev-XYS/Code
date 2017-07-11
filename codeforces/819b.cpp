#include <cstdio>

using namespace std;

class array
{
private:
	int con[2000010], base;
	
public:
	void inc(int p) { con[p - base]++; }
	void dec(int p) { con[p - base]--; }
	void shl(int o) { base -= o; }
	void shr(int o) { base += o; }
}cnt;

int n, P[1000010], ans, ansp, res, base = 0;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &P[i]);
		cnt.inc(P[i] - i);
	}
	ans = res;
	ansp = 1;
	for (int i = n; i > 1; i--)
	{
		

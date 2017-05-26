// Problem Name: JOIOJI
// Source: JOI 2013~2014 春季training合宿 竞技3 By PoPoQQQ

#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

struct event
{
	int d1, d2;
	event(int _d1 = 0, int _d2 = 0) : d1(_d1), d2(_d2) { }
};

int n, cnt[3];
char s[200010];
map<event, int> M;

inline void check_max(int &x, int y)
{
	if (y > x) x = y;
}

inline bool operator < (const event &x, const event &y)
{
	if (x.d1 == y.d1) return x.d2 < y.d2;
	return x.d1 < y.d1;
}

int main()
{
	scanf("%d%s", &n, s + 1);
	int len = strlen(s + 1), ans = 0;
	M[event(0, 0)] = 0;
	for (int i = 1; i <= len; i++)
	{
		if (s[i] == 'J') cnt[0]++;
		else if (s[i] == 'O') cnt[1]++;
		else cnt[2]++;
		int d1 = cnt[1] - cnt[0], d2 = cnt[2] - cnt[1];
		if (M.count(event(d1, d2)) == 0) M[event(d1, d2)] = i;
		else check_max(ans, i - M[event(d1, d2)]);
	}
	printf("%d\n", ans);
	return 0;
}

#include <cstdio>

using namespace std;

struct node
{
	int x, y, ord;
	node(int _x = 0, int _y = 0, int _ord = 0) : x(_x), y(_y), ord(_ord) { }
};

class queue
{
public:
	node con[500010];
	int hp, tp;
	queue() : hp(0), tp(0) { }
	inline node back() { return con[tp - 1]; }
	inline node subback() { return con[tp - 2]; }
	inline node front() { return con[hp]; }
	inline node subfront() { return con[tp + 1]; }
	inline void push_back(node u) { con[tp++] = u; }
	inline void push_front(node u) { con[--hp] = u; }
	inline void pop_back() { tp--; }
	inline void pop_front() { hp++; }
	inline int size() { return tp - hp; }
	inline void clear() { hp = tp = 0; }
}Q;

int n, m, s[500010], dp[500010];

int main()
{
	while (scanf("%d%d", &n, &m) > 0)
	{
		Q.clear();
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &s[i]);
			s[i] += s[i - 1];
		}
		dp[0] = 0;
		dp[1] = s[1] * s[1] + m;
		Q.push_back(node(0, 0, 0));
		Q.push_back(node(s[1] * 2, dp[1] + s[1] * s[1], 1));
		for (int i = 2; i <= n; i++)
		{
			while (Q.size() >= 2)
			{
				node u = Q.front();
				Q.pop_front();
				node v = Q.front();
				if ((v.y - u.y) > s[i] * (v.x - u.x))
				{
					Q.push_front(u);
					break;
				}
			}
			int ord = Q.front().ord;
			dp[i] = dp[ord] + (s[i] - s[ord]) * (s[i] - s[ord]) + m;
			int x = s[i] * 2, y = dp[i] + s[i] * s[i];
			while (Q.size() >= 2)
			{
				node u = Q.back();
				Q.pop_back();
				node v = Q.back();
				if ((y - u.y) * (u.x - v.x) > (u.y - v.y) * (x - u.x))
				{
					Q.push_back(u);
					Q.push_back(node(x, y, i));
					break;
				}
			}
			if (Q.size() == 1) Q.push_back(node(x, y, i));
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}

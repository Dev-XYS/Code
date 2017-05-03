// Problem Name: Picnic Planning
// Source: East Central North America 2000

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define INF 1000000000

using namespace std;

struct input_edge
{
	string u, v;
	int w;
	input_edge(string _u, string _v, int _w) : u(_u), v(_v), w(_w) { }
};

struct raw_edge
{
	int u, v, w;
	raw_edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) { }
};

int iec, deg, id, dis[21][21], fa[21];
vector<input_edge> I;
map<string, int> B;
vector<raw_edge> R;

void init_dsu()
{
	for (int i = 0; i < (int)B.size(); i++)
	{
		fa[i] = i;
	}
}

int getrt(int x)
{
	if (fa[x] == x) return x;
	return getrt(fa[x]);
}

int merge(int x, int y)
{
	int rtx = getrt(x), rty = getrt(y);
	if (rtx == rty) return 0;
	fa[rtx] = rty;
	return 1;
}

inline bool _raw_edge_w_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.w < y.w;
}

int main()
{
	cin >> iec;
	string u, v;
	int w;
	B["Park"] = 0;
	for (int i = 0; i < iec; i++)
	{
		cin >> u >> v >> w;
		I.push_back(input_edge(u, v, w));
		if (B.count(u) == 0) B[u] = ++id;
		if (B.count(v) == 0) B[v] = ++id;
	}
	cin >> deg;
	for (int i = 0; i < (int)B.size(); i++)
	{
		for (int j = 0; j < (int)B.size(); j++)
		{
			dis[i][j] = INF;
		}
	}
	for (int i = 0; i < iec; i++)
	{
		R.push_back(raw_edge(B[I[i].u], B[I[i].v], I[i].w));
		if (R[i].w < dis[R[i].u][R[i].v]) dis[R[i].u][R[i].v] = dis[R[i].v][R[i].u] = R[i].w;
	}
	sort(R.begin(), R.end(), _raw_edge_w_cmp_);
	int ans = INF;
	for (int _i = (1 << (B.size() - 1)) - 1; _i > 0; _i--)
	{
		int i = _i << 1;
		int c = 0;
		for (int j = 1; j < (int)B.size(); j++)
		{
			if ((i & (1 << j)) != 0 && dis[0][j] != INF) c++;
		}
		if (c > deg || c == 0) continue;
		int wsum = 0, con = 0;
		init_dsu();
		for (int j = 1; j < (int)B.size(); j++)
		{
			if ((i & (1 << j)) != 0 && dis[0][j] != INF)
			{
				int t = merge(0, j);
				con += t;
				wsum += dis[0][j] * t;
			}
		}
		int k = 0;
		while (con < (int)B.size() - 1 && k < iec)
		{
			if (R[k].u == 0 || R[k].v == 0)
			{
				k++;
				continue;
			}
			int t = merge(R[k].u, R[k].v);
			con += t;
			wsum += R[k].w * t;
			k++;
		}
		if (con == (int)B.size() - 1 && wsum < ans) ans = wsum;
	}
	cout << "Total miles driven: " << ans << endl;
	return 0;
}

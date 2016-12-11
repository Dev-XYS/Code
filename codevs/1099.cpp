#include <iostream>
#include <string>
#include <map>

using namespace std;

struct qnode
{
	string s;
	int layer;
	qnode(string _s = "", int _layer = 0) : s(_s), layer(_layer) { }
}Q1[1000000], Q2[1000000];

string S, T, trans[6][2];
int hp1, tp1, hp2, tp2, c;

string transform(string s, int offset, int len, string oth)
{
	string res = "";
	for (int i = 0; i < offset; i++)
	{
		res += s[i];
	}
	for (unsigned int i = offset; i < offset + oth.length(); i++)
	{
		res += oth[i - offset];
	}
	for (unsigned int i = offset + oth.length(); i < s.length() - len + oth.length(); i++)
	{
		res += s[i - oth.length() + len];
	}
	return res;
}

void BFS1()
{
	Q1[tp1++] = qnode(S, 0);
	while (hp1 != tp1)
	{
		qnode u = Q1[hp1++];
		if (u.layer == 5)
		{
			break;
		}
		string s = u.s;
		for (unsigned int i = 0; i < s.length(); i++)
		{
			for (int j = 0; j < c; j++)
			{
				for (unsigned int k = 0; k < trans[j][0].length(); k++)
				{
					if (s[i + k] != trans[j][0][k])
					{
						goto END;
					}
				}
				Q1[tp1++] = qnode(transform(s, i, trans[j][0].length(), trans[j][1]), u.layer + 1);
			END:;
			}
		}
	}
}

void BFS2()
{
	Q2[tp2++] = qnode(T, 0);
	while (hp2 != tp2)
	{
		qnode u = Q2[hp2++];
		if (u.layer == 5)
		{
			break;
		}
		string s = u.s;
		for (unsigned int i = 0; i < s.length(); i++)
		{
			for (int j = 0; j < c; j++)
			{
				for (unsigned int k = 0; k < trans[j][1].length(); k++)
				{
					if (s[i + k] != trans[j][1][k])
					{
						goto END;
					}
				}
				Q2[tp2++] = qnode(transform(s, i, trans[j][1].length(), trans[j][0]), u.layer + 1);
			END:;
			}
		}
	}
}

int main()
{
	cin >> S >> T;
	while (cin >> trans[c][0] >> trans[c][1])
	{
		c++;
	}
	BFS1();
	BFS2();
	map<string, int> g;
	for (int i = tp2 - 1; i >= 0; i--)
	{
		g[Q2[i].s] = Q2[i].layer;
	}
	int ans = 100;
	for (int i = 0; i < tp1; i++)
	{
		int _g = g[Q1[i].s];
		if (_g != 0)
		{
			int newans = Q1[i].layer + _g;
			if (newans < ans)
			{
				ans = newans;
			}
		}
	}
	if (ans > 10)
	{
		cout << "NO ANSWER!";
	}
	else
	{
		cout << ans;
	}
	return 0;
}

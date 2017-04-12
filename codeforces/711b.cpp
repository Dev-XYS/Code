// Problem Name: Chris and Magic Square
// Source: Codeforces Round #369 (Div. 2), Problem B

#include <iostream>

typedef long long ll;

using namespace std;

int n, zx, zy;
ll grid[510][510];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 0) zx = i, zy = j;
		}
	}
	if (n == 1)
	{
		cout << "1";
		return 0;
	}
	int vx;
	if (zx == 0) vx = 1;
	else vx = zx - 1;
	ll value = 0;
	for (int i = 0; i < n; i++)
	{
		value += grid[vx][i];
	}
	ll _value = 0;
	for (int i = 0; i < n; i++)
	{
		_value += grid[zx][i];
	}
	if (value - _value <= 0) goto NO_ANSWER;
	grid[zx][zy] = value - _value;
	_value = 0;
	for (int i = 0; i < n; i++)
	{
		_value += grid[i][i];
	}
	if (_value != value) goto NO_ANSWER;
	_value = 0;
	for (int i = 0; i < n; i++)
	{
		_value += grid[i][n - i - 1];
	}
	if (_value != value) goto NO_ANSWER;
	for (int i = 0; i < n; i++)
	{
		_value = 0;
		for (int j = 0; j < n; j++)
		{
			_value += grid[i][j];
		}
		if (_value != value) goto NO_ANSWER;
		_value = 0;
		for (int j = 0; j < n; j++)
		{
			_value += grid[j][i];
		}
		if (_value != value) goto NO_ANSWER;
	}
	cout << grid[zx][zy];
	return 0;
NO_ANSWER:
	cout << "-1";
	return 0;
}

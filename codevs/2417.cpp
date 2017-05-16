// Problem Name: 股票交易
// Source: [SCOI2010]

#include <cstdio>

#define INF 1000000000

using namespace std;

template <typename T>
class queue
{
private:
	T d[2017], md[2017];
	int hp, tp, mhp, mtp;

public:
	queue();
	void enqueue(T x);
	T dequeue();
	T get_max();
	size_t size();
	bool empty();
};

template <typename T>
queue<T>::queue()
{
	hp = tp = 0;
	mhp = mtp = 0;
}

template <typename T>
void queue<T>::enqueue(T x)
{
	while (mtp - mhp > 0 && md[mtp - 1] < x) mtp--;
	md[mtp++] = x;
	d[tp++] = x;
}

template <typename T>
T queue<T>::dequeue()
{
	if (md[mhp] == d[hp]) mhp++;
	return d[hp++];
}

template <typename T>
T queue<T>::get_max()
{
	return md[mhp];
}

template <typename T>
size_t queue<T>::size()
{
	return tp - hp;
}

template <typename T>
bool queue<T>::empty()
{
	return size() == 0;
}

template <typename T>
inline T min(T x, T y)
{
	return x < y ? x : y;
}

template <typename T>
inline T max(T x, T y)
{
	return x < y ? y : x;
}

int T, MaxP, W, AP[2010], BP[2010], AS[2010], BS[2010], dp[2010][2010];

int main()
{
	scanf("%d%d%d", &T, &MaxP, &W);
	for (int i = 0; i < T; i++)
	{
		scanf("%d%d%d%d", &AP[i], &BP[i], &AS[i], &BS[i]);
	}
	for (int j = 0; j <= AS[0]; j++)
	{
		dp[0][j] = -j * AP[0];
	}
	for (int j = AS[0] + 1; j <= MaxP; j++)
	{
		dp[0][j] = -INF;
	}
	for (int i = 1; i < T; i++)
	{
		for (int j = 0; j <= AS[i]; j++)
		{
			dp[i][j] = max(dp[i - 1][j], -j * AP[i]);
		}
		for (int j = AS[i] + 1; j <= MaxP; j++)
		{
			dp[i][j] = dp[i - 1][j];
		}
		/* dp[i][j] = max{dp[i - W - 1][k] - (j - k) * AP[i]} */
		/* dp[i][j] = max{dp[i - W - 1][k] + k * AP[i] - j * AP[i] */
		if (i - W - 1 >= 0)
		{
			queue<int> Q;
			for (int j = 1; j <= MaxP; j++)
			{
				Q.enqueue(dp[i - W - 1][j - 1] + (j - 1) * AP[i]);
				if (Q.size() > (size_t)AS[i]) Q.dequeue();
				dp[i][j] = max(dp[i][j], Q.get_max() - j * AP[i]);
			}
		}
		/* dp[i][j] = max{dp[i - W - 1][k] + (k - j) * BP[i]} */
		/* dp[i][j] = max{dp[i - W - 1][k] + k * BP[i] - j * BP[i] */
		if (i - W - 1 >= 0)
		{
			queue<int> Q;
			for (int j = MaxP - 1; j >= 0; j--)
			{
				Q.enqueue(dp[i - W - 1][j + 1] + (j + 1) * BP[i]);
				if (Q.size() > (size_t)BS[i]) Q.dequeue();
				dp[i][j] = max(dp[i][j], Q.get_max() - j * BP[i]);
			}
		}
	}
	printf("%d\n", dp[T - 1][0]);
	return 0;
}

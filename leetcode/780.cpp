class Solution {
public:
	bool reachingPoints(int sx, int sy, int tx, int ty) {
		while (tx >= sx && ty >= sy)
		{
			if (tx < ty)
			{
				if (sx == tx)
				{
					return (ty - sy) % tx == 0;
				}
				else
				{
					ty %= tx;
				}
			}
			else
			{
				if (sy == ty)
				{
					return (tx - sx) % ty == 0;
				}
				else
				{
					tx %= ty;
				}
			}
		}
		return false;
	}
};

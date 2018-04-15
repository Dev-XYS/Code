// Problem Name: Race Car

class Solution {
public:
	struct queue_node {
		int cnt, pos, speed, dir;
		queue_node(int _cnt, int _pos, int _speed, int _dir) : cnt(_cnt), pos(_pos), speed(_speed), dir(_dir) { }
	};

	int racecar(int target) {
		static bool vis[80001][32];
		memset(vis, 0, sizeof(vis));
		queue<queue_node> Q;
		Q.push(queue_node(0, 0, 0, 1));
		while (true)
		{
			queue_node u = Q.front();
			Q.pop();
			if (abs(u.pos) > 40000) continue;
			if (abs(u.speed) > 15) continue;
			if (vis[u.pos + 40000][u.speed + (u.dir < 0 ? 16 : 0)]) continue;
			vis[u.pos + 40000][u.speed + (u.dir < 0 ? 16 : 0)] = true;
			if (u.pos == target)
			{
				return u.cnt;
			}
			Q.push(queue_node(u.cnt + 1, u.pos + u.dir * (1 << u.speed), u.speed + 1, u.dir));
			Q.push(queue_node(u.cnt + 1, u.pos, 0, -u.dir));
		}
	}
};

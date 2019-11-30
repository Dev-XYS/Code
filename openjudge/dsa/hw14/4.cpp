#include <cstdio>
#include <set>

using namespace std;

int main() {
	int n;
	long long a = 0;
	multiset<int> S;
	scanf("%d", &n);
	while (n--) {
		int c;
		scanf("%d", &c);
		while (c--) {
			int x;
			scanf("%d", &x);
			S.insert(x);
		}
		a += *(--S.end()) - *(S.begin());
		S.erase(S.begin());
		S.erase(--S.end());
	}
	printf("%lld\n", a);
	return 0;
}

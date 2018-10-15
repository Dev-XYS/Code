// Problem Name: 迭代法解方程
// OpenJudge Global No.: 1699

#include <stdio.h>

int n;
double a, b;

double f(double x) {
	return x * x * x + x + a;
}

int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%lf%lf", &a, &b);
		double l = -a, r = a;
		while (r - l >= b) {
			double mid = (l + r) / 2;
			double fx = f(mid);
			if (fx > 0) {
				r = mid;
			}
			else if (fx < 0) {
				l = mid;
			}
			else {
				break;
			}
		}
		double x = (l + r) / 2;
		printf("%lf %lf\n", x, f(x));
	}
	return 0;
}

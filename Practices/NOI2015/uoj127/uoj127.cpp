#include <cstdio>

using namespace std;

int getInt()
{
	int res = 0, pre = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			pre = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		res *= 10;
		res += ch - '0';
		ch = getchar();
	}
	return pre * res;
}
#include <vector>
struct EQ {
	int a, b;
	int op;
} eqs[100050];
vector<int> numbers;
int fa[200050];

inline int find(int a)
{
	return (a == fa[a]) ? a : (fa[a] = find(fa[a]));
}

inline void uni(int a, int b)
{
	fa[find(a)] = find(b);
}

inline bool eq(int a, int b)
{
	return find(a) == find(b);
}

#include <algorithm>

int tmain()
{
	int N = getInt();
	numbers.clear();
	for (int i = 1; i <= N; i++) {
		eqs[i].a = getInt();
		eqs[i].b = getInt();
		eqs[i].op = getInt();
		numbers.push_back(eqs[i].a);
		numbers.push_back(eqs[i].b);
	}
	sort(numbers.begin(), numbers.end());
	int n = unique(numbers.begin(), numbers.end()) - numbers.begin();
	numbers.erase(numbers.begin() + n, numbers.end());
	for (int i = 0; i <= n; i++) {
		fa[i] = i;
	}
	for (int i = 1; i <= N; i++) {
		eqs[i].a = lower_bound(numbers.begin(), numbers.end(), eqs[i].a) - numbers.begin() + 1;
		eqs[i].b = lower_bound(numbers.begin(), numbers.end(), eqs[i].b) - numbers.begin() + 1;
		if (eqs[i].op == 1) {
			uni(eqs[i].a, eqs[i].b);
		}
	}
	for (int i = 1; i <= N; i++) {
		if (eqs[i].op == 0) {
			if (eq(eqs[i].a, eqs[i].b)) {
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	return 0;
}

int main()
{
	int T = getInt();
	while (T--) {
		tmain();
	}
	return 0;
}


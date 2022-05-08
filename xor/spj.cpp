#include <cstdio>
#include <cassert>
using namespace std;
const int N = 1e5 + 10;
bool vis[N];
int n, m, w[N];

int main ()
{
	FILE *in = fopen("xor4.in", "r"), *out = fopen("xor.out", "r"), *ans = fopen("xor4.out", "r");
	fscanf(in, "%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		char s[10], t[10];
		fscanf(out, "%s", s);
		fscanf(ans, "%s", t);
		vis[i] = s[0] == 'Y';
		assert(s[0] == t[0]);
	}
	for (int i = 1; i <= n; i++)
		fscanf(out, "%d", &w[i]), w[i] ^= w[i - 1];
	for (int i = 1; i <= m; i++)
	{
		int l, r, x;
		fscanf(in, "%d%d%d", &l, &r, &x);
		assert(!vis[i] || (w[r] ^ w[l - 1]) == x);
	}
	return 0;
}
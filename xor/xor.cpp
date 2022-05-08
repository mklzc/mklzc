#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int s[N], fa[N], v[N], ans, flag;
struct Node
{
    int to;
    int cost;
};
vector<Node> G[N];
int get(int x)
{
    if (fa[x] != x) return fa[x] = get(fa[x]);
    return fa[x];
}
void get_path(int x, int ANS, int END)
{
    if (flag) return;
    if (x == END) return void(flag = 1), void(ans ^= ANS);
    for (auto a : G[x])
    {
        int y = a.to, z = a.cost;
        if (v[y]) continue;
        v[y] = 1;
        get_path(y, ANS ^ z, END);
    }
}
int main()
{
    freopen("xor3.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    int n, m, l, r, x;;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    while (m--)
    {
        scanf("%d%d%d", &l, &r, &x);
        if (get(l - 1) == get(r))
        {
            memset(v, 0, sizeof(v));
            ans = 0, flag = 0;
            get_path(l - 1, 0, r), flag = 0;
            get_path(r, 0, l - 1);
            if (ans != x)
                {puts("No");continue;}
        }
        puts("Yes");
        Node a = {to: l - 1, cost: x}, b = {to: r, cost: x};
        G[l - 1].push_back(b), G[r].push_back(a);
        fa[get(l - 1)] = get(r);
    }
    s[0] = 0;
    for (int i = 0; i <= n; i++)
        for (auto a : G[i])
            if (a.to > i) s[a.to] = s[i] ^ a.cost;
    for (int i = 1; i <= n; i++)
        printf("%d ", s[i] ^ s[i - 1]);
    printf("\n");
    return 0;
}
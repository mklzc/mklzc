#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int s[N];
int fa[N], v[N];
struct Node
{
    int to;
    int cost;
};
vector<Node> G[N];
void add(int x, int y, int z)
{
    Node a;
    a.to = y, a.cost = z;
    G[x].push_back(a);
}
int get(int x)
{
    if (fa[x] != x)
        return fa[x] = get(fa[x]);
    return fa[x];
}

int ans, flag;
void find_circle(int x, int ANS, int END)
{
    if (flag) return;
    if (x == END)
        return void(flag = 1), void(ans ^= ANS);
    for (int i = 0; i < G[x].size(); i++)
    {
        int y = G[x][i].to, z = G[x][i].cost;
        if (v[y]) continue;
        v[y] = 1;
        find_circle(y, ANS ^ z, END);
    }
}
int main()
{
    freopen("in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    while (m--)
    {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        if (get(l - 1) == get(r))
        {
            memset(v, 0, sizeof(v));
            ans = 0, flag = 0;
            find_circle(l - 1, 0, r), flag = 0;
            find_circle(r, 0, l - 1);
            if (ans != x)
                {puts("No");continue;}
        }
        puts("Yes");
        // cout << l - 1 << " " << r << endl;
        add(l - 1, r, x);
        add(r, l - 1, x);
        fa[get(l - 1)] = get(r);
    }
    s[0] = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < G[i].size(); j++)
        {
            int y = G[i][j].to, z = G[i][j].cost;
            if (y <= i) continue;
            // cout << i << " " << y << " " << z << endl;
            s[y] = s[i] ^ z;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", s[i] ^ s[i - 1]);
    printf("\n");
    return 0;
}
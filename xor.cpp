#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int s[N];
int fa[N], v[N];
int ver[N], head[N], Next[N], edge[N], idx;
void add(int x, int y, int z)
{
    ver[++idx] = y;
    edge[idx] = z;
    Next[idx] = head[x];
    head[x] = idx;
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
    for (int i = head[x]; ~i; i = Next[i])
    {
        int y = ver[i];
        if (v[y]) continue;
        v[y] = 1;
        find_circle(y, ANS ^ edge[i], END);
    }
}
int main()
{
    freopen("in", "r", stdin);
    memset(head, -1, sizeof(head));
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
        cout << l - 1 << " " << r << endl;
        add(l - 1, r, x);
        add(r, l - 1, x);
        fa[get(l - 1)] = get(r);
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = head[i]; ~j; j = Next[j])
        {
            cout << i << " " <<  ver[i] << " " << edge[i] << endl;
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

namespace FastIO
{
    char gc()
    {
        static char buf[1 << 24], *is = buf, *it = buf;
        if (is == it)
            is = buf, it = is + fread(buf, 1, 1 << 24, stdin);
        return is == it ? EOF : *is++;
    }
    char out[1 << 24];
    int len;
    void flush() { fwrite(out, 1, len, stdout), len = 0; }
    void pc(char x)
    {
        if (len == 1 << 24)
            flush();
        out[len++] = x;
    }
    struct Flusher
    {
        ~Flusher() { flush(); }
    } Fls;
    // #define gc() getchar()
    // #define pc(X) putchar(X)
    template <class T>
    inline void read(T &x)
    {
        char c, flag = 0;
        while ((c = gc()) < '0' || c > '9')
            flag |= c == '-';
        x = c & 15;
        while ((c = gc()) >= '0' && c <= '9')
            x = (x << 3) + (x << 1) + (c & 15);
        if (flag)
            x = ~x + 1;
    }
    template <class T, class... T1>
    inline void read(T &x, T1 &...x1) { read(x), read(x1...); }
    template <class T>
    inline void _put(T x)
    {
        if (x > 9)
            _put(x / 10);
        pc((x % 10) | 48);
    }
    template <class T>
    inline void write(T x)
    {
        if (x < 0)
            pc('-'), x = ~x + 1;
        _put(x);
    }
    template <>
    inline void write(char x) { pc(x); }
    template <class T, class... T1>
    inline void write(T x, T1... x1) { write(x), write(x1...); }
}
using FastIO::read;
using FastIO::write;

const int N = 1e5 + 5;
int c[N];
vector<int> G[N];
queue<int> q;
int f[N][22], depth[N], t;
void bfs(int rt)
{
    q.push(rt);
    depth[rt] = 1;
    while (q.size())
    {
        int x = q.front();
        q.pop();
        for (auto y : G[x])
        {
            if (depth[y])
                continue;
            f[y][0] = x, depth[y] = depth[x] + 1;
            for (int j = 1; j <= t; j++)
                f[y][j] = f[f[y][j - 1]][j - 1];
            q.push(y);
        }
    }
}
int lca(int x, int y)
{
    if (depth[x] > depth[y])
        swap(x, y);
    for (int i = t; i >= 0; i--)
        if (depth[f[y][i]] >= depth[x])
            y = f[y][i];
    if (x == y)
        return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    int n, d, k;
    read(n, d, k);
    for (int i = 1; i <= n; i++)
        read(c[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    bfs(1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (depth[i] + depth[j] - 2 * depth[lca(i, j)] == d && abs(c[i] - c[j]) <= k) cnt++;
            
    write(cnt, '\n');
    return 0;
}

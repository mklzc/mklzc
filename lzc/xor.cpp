#include <bits/stdc++.h>
using namespace std;

namespace FastIO {
    char gc() {
        static char buf[1 << 24], *is = buf, *it = buf;
        if (is == it) is = buf, it = is + fread(buf, 1, 1 << 24, stdin);
        return is == it ? EOF : *is ++;
    }
    char out[1 << 24];
    int len;
    void flush() { fwrite(out, 1, len, stdout), len = 0; }
    void pc(char x) {
        if (len == 1 << 24) flush();
        out[len ++] = x;
    }
    struct Flusher {
        ~Flusher() { flush(); }
    } Fls;
    // #define gc() getchar()
    // #define pc(X) putchar(X)
    template <class T>
    inline void read(T &x)
    {
        char c, flag = 0;
        while ((c = gc()) < '0' || c > '9') flag |= c == '-';
        x = c & 15;
        while ((c = gc()) >= '0' && c <= '9')
            x = (x << 3) + (x << 1) + (c & 15);
        if (flag) x = ~x + 1;
    }
    template <class T, class ...T1>
    inline void read(T &x, T1 &...x1) { read(x), read(x1...); }
    template <class T>
    inline void _put(T x)
    {
        if (x > 9) _put(x / 10);
        pc((x % 10) | 48);
    }
    template <class T>
    inline void write(T x) {
        if (x < 0) pc('-'), x = ~x + 1;
        _put(x);
    }
    template <> inline void write(char x) { pc(x); }
    template <class T, class ...T1>
    inline void write(T x, T1 ...x1) { write(x), write(x1...); }
}
using FastIO::read;
using FastIO::write;

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
void dfs(int x)
{
    for (auto a : G[x])
    {
        int y = a.to, z = a.cost;
        if (v[y]) continue;
        v[y] = 1;
        s[y] = s[x] ^ z;
        dfs(y);
    }
}
int main()
{
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    int n, m, l, r, x;
    read(n, m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    while (m--)
    {
        read(l, r, x);
        if (get(l - 1) == get(r))
        {
            memset(v, 0, sizeof(v));
            ans = 0, flag = 0;
            get_path(l - 1, 0, r), flag = 0;
            get_path(r, 0, l - 1);
            for (auto a : G[l - 1])
                if (a.to == r) ans = a.cost;
            if (ans != x)
                {write('N', 'o', '\n');continue;}
        }
        write('Y', 'e', 's', '\n');
        Node a = {to: l - 1, cost: x}, b = {to: r, cost: x};
        G[l - 1].push_back(b), G[r].push_back(a);
        fa[get(l - 1)] = get(r);
    }
    memset(v, 0, sizeof(v));
    for (int i = 0; i <= n; i++)
        if(!v[i]) dfs(i);
    for (int i = 1; i <= n; i++)
        s[i] ^= s[0];
    s[0] = 0;
    for (int i = 1; i <= n; i++)
        write(s[i] ^ s[i - 1], ' ');
    write('\n');
    return 0;
}
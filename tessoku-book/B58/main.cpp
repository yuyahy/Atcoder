// TODO: マクロや共通関数は別ファイルに定義し、埋め込む様にする
// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif

#define REP(i, n) for (int i = 0; (i) < (int)(n); ++(i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++(i))
#define REP_R(i, n) for (int i = (int)(n)-1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

// TODO ここは設問の条件によって変更する必要がある
ll op(ll x, ll y) { return max({x, y}); }
ll e() { return 0; }

int main() {
    // TODO: 解説に以下のアドバイスがあったので、一旦10章 or A76まで解いてから再チャレンジする
    // ・A76は似た問題だが、この問題よりは比較的簡単
    // ・本書を最初から読んでいる人は10章まで読破してから解くことを推奨

    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), L(0), R(0);
    cin >> N >> L >> R;
    vector<ll> X(N, 0);
    REP(i, N) cin >> X[i];
    dump(X);

    segtree<ll, op, e> seg(N);  // 長さ N 、要素すべて e で初期化

    // 1. テーブル定義:
    vector<vector<ll>> DP(N + 1, vector<ll>(N + 1, 1e10));
    // TODO 以下とセグメント木の使用の検討
    // 2. 初期状態:
    // 3. 遷移
}

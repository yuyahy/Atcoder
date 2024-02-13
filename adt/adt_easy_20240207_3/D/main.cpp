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
#define REP3R(i, m, n) for (int i = (int)(m)-1; (i) >= (int)(n); --(i))

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef unsigned long long ll;
typedef pair<int, int> pii;

// mint
constexpr ll MOD = 1e18;
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void solve1(const int MAX, const vector<ll>& A) {
    // 2のi乗を前計算
    map<ll, ll> mul_map;
    mul_map[0] = 1;
    REP3(i, 1, MAX) mul_map[i] = mul_map[i - 1] * 2;
    dump(mul_map);

    ll res(0);
    REP(i, MAX) { res += mul_map[i] * A[i]; }
    cout << res << endl;
}

void solve2(const int MAX, const vector<ll>& A) {
    ll result(0);
    for (ll i = 0; i < MAX; i++) {
        result += A[i] << i;
    }
    cout << result << endl;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    // Note: long long intの最大値は2^63 - 1なので本問題では足りない
    //       signed long long intなら問題ない

    const int MAX = 64;
    vector<ll> A(MAX, 0);
    REP(i, MAX) cin >> A[i];

    // solve1(MAX, A);
    solve2(MAX, A);
}

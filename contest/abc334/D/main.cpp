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

// nCk、組み合わせを求める関数
//
// usage:
// vector<vector<ll> > v(n + 1, vector<ll>(n + 1, 0));
// comb(v);
// v[n][k]が求めるnCkの値
void comb(vector<vector<ll> >& v) {
    for (ll i = 0; i < (ll)v.size(); i++) {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (ll k = 1; k < (ll)v.size(); k++) {
        for (ll j = 1; j < k; j++) {
            v[k][j] = (v[k - 1][j - 1] + v[k - 1][j]);
        }
    }
}

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    // Note: 本番中に手をつけられなかったので、後で解いたら簡単だった。。。
    //       理想のムーブとしては、Bを途中で捨ててこの問題をやるべきだった
    ll N(0), Q(0);
    cin >> N >> Q;
    vector<ll> necessary_reindeer(N + 1, 0);
    ll tmp(0);
    REP3(i, 1, N + 1) {
        cin >> tmp;
        necessary_reindeer[i] = tmp;
    }
    // 可能な限り多くのソリを引くためには、貪欲に必要なトナカイが少ないソリ
    // を使っていけば良いので、昇順にソート
    sort(necessary_reindeer.begin(), necessary_reindeer.end());

    // 必要なトナカイの累積和
    vector<ll> accum_reindeer(N + 1, 0);
    REP3(i, 1, N + 1) {
        accum_reindeer[i] = accum_reindeer[i - 1] + necessary_reindeer[i];
    }
    dump(necessary_reindeer);
    dump(accum_reindeer);

    ll query(0);
    REP(i, Q) {
        cin >> query;
        // 二分探索で与えられたトナカイの頭数で引ける累積和+1を求める
        auto itr =
            upper_bound(accum_reindeer.begin(), accum_reindeer.end(), query);
        // 一個前のインデックスまでが与えられた頭数で引ける上限
        auto result = prev(itr, 1);
        cout << distance(accum_reindeer.begin(), result) << endl;
    }
}

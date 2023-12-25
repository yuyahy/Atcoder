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
    ll N(0), K(0);
    cin >> N >> K;

    // まず、同じ色のペアが作れる物が最もコストが低くなるので、
    // 優先的に使用する

    // 同じ色のペアがない場合は、|i-j|が最も小さくなる様な選び方をする必要がある
    // また、(2N-K/2)が奇数の場合は、ペアにすると最もコストが高くなる靴下はペアを作らないべき

    vector<ll> A(K, 0);
    ll tmp(0);
    REP(i, K) {
        cin >> tmp;
        A[i] = tmp;
    }
    dump(A);
    // Note: 実は直感通り、余った靴下は隣合ったペアを作るのが最適らしい
    //       ただし、奇数の場合はどれを余らせるのが最適か？は単純にコスト最大のを除外するだけでは
    //       無理なので、全探索して前方からの累積和と後方からの累積和の内、小さい方を採用する
    //       なお、奇数の場合どの靴下を除外するか？を新たに追加されるペアと除外するペアを試す方針でもいけるらしい(公式生放送より)

    vector<ll> pre_accum(K + 1, 0), suffix_accum(K + 1, 0);
    // 左からi番目まで隣合った靴下を取った際の前方からの累積和
    REP3(i, 1, K + 1) {
        pre_accum[i] = pre_accum[i - 1];
        if (i % 2 == 0) {
            pre_accum[i] += A[i - 1] - A[i - 2];
        }
    }
    // 右(後方)からK/2-i番目までの累積和
    REP_R(i, K) {
        dump(i);
        suffix_accum[i] = suffix_accum[i + 1];
        if ((K - i) % 2 == 0) {
            suffix_accum[i] += A[i + 1] - A[i];
        }
    }
    dump(pre_accum);
    dump(suffix_accum);

    ll ans(1e10);
    // 両側からの累積和の和を取ることで、ある靴下を選ばないケースがO(N)で全探索できる
    for (int i = 0; i < K + 1; i += 2) {
        ans = min(ans, pre_accum[i] + suffix_accum[i]);
    }
    cout << ans << endl;
}

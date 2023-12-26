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
void comb(vector<vector<ll>>& v) {
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

bool isNthBitSet(int num, int N) {
    // 1をNビット左シフトして、numとの論理積をとる
    // 結果が0でなければ、N桁目が立っている
    return (num & (1 << N)) != 0;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0), Q(0);
    cin >> N >> Q;
    // 穴がiの次の穴を管理する
    vector<int> A(N, 0);
    REP(i, N) {
        auto tmp(0);
        cin >> tmp;
        A[i] = tmp;
    }
    dump(A);

    // ダブリング・・・全部でN個の要素それぞれについて、1回遷移した時の移動先が与えられているとする
    //              K回遷移した時の到達点を愚直に求めると、O(K)かかるが、O(NlogK)で求められる

    // 1. テーブルを更新していく
    // テーブル定義: DP[i][j]:j番目の要素から2^i回遷移した時の到達地点
    // 初期状態: DP[0][j] = Ai
    // 遷移: DP[i][j] = DP[i-1][｛DP[i-1][j]｝]
    //       →DP[i][j]は定義より、j番目の要素が2^i-1回遷移した時の到達地点から更に2^i-1回
    //        遷移する事でも求められる

    // Yの上限が1e9なので、2^30=1073741824まで求めれば充分
    constexpr int max = 30;
    vector<vector<int>> DP(max, vector<int>(N + 1, 0));
    // 初期状態
    REP3(j, 1, N + 1) DP[0][j] = A[j - 1];
    // 遷移
    REP3(i, 1, max) REP3(j, 1, N + 1) DP[i][j] = DP[i - 1][DP[i - 1][j]];
    dump(DP);

    // 2.テーブルを用いてクエリを処理
    // (Kの2進数表現) = 2^C1 + 2^C2 + 2^C3 + ....+2^Ck(0<=C1<=C2...Ck)とした時、
    // C1から順に答えAをA=[Cl][A]と更新していく事で目的の遷移に辿り着く(1<=l<=k)
    auto calc_destination = [&](const int start, const int num_move) {
        int ans = start;
        REP_R(i, max) {
            if (isNthBitSet(num_move, i)) ans = DP[i][ans];
        }
        return ans;
    };

    int X(0), Y(0);
    REP(i, Q) {
        cin >> X >> Y;
        cout << calc_destination(X, Y) << endl;
    }
}
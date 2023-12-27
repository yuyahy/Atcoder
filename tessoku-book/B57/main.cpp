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

bool isNthBitSet(int num, int N) {
    // 1をNビット左シフトして、numとの論理積をとる
    // 結果が0でなければ、N桁目が立っている
    return (num & (1 << N)) != 0;
}

ll sum_digits(const ll num) {
    // 入力値の各桁の数字の和を返す
    auto tmp = num;
    ll sum(0);
    while (tmp) {
        sum += tmp % 10;
        tmp /= 10;
    }
    return sum;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);
    ll N(0), K(0);
    cin >> N >> K;

    // Note: テーブル定義のiとjを反対に考えてしまっていたので、注意！
    // テーブル定義・・・整数j(1,2...N)に以下の操作を2^i回行った後の整数
    // ・十進法で表したときの各位の数字の和を、自身から引く。
    // ※制約より、2^30>1e9程度まで計算すればOK
    constexpr ll MAX = 30;
    vector<vector<ll>> DP(MAX, vector<ll>(N + 1, 0));
    // 初期状態・・・明らかに以下
    REP3(i, 1, N + 1) DP[0][i] = i - sum_digits(i);
    dump(DP);
    // 遷移・・・DP[i][j] = DP[i-1][DP[i-1][j]]
    // 整数jから2^i-1回操作を行った後の値はDP[i-1][j]、この値に対して更に2^i-1回
    // 操作を行った時の値はここに入っている
    REP3(i, 1, MAX) REP3(j, 1, N + 1) DP[i][j] = DP[i - 1][DP[i - 1][j]];

    auto calc_destination = [&](const ll start, const ll num_operation) {
        ll ans = start;
        REP_R(i, MAX) {
            if (isNthBitSet(num_operation, i)) ans = DP[i][ans];
        }
        return ans;
    };

    // 操作をK回行った時の計算
    REP3(i, 1, N + 1) { cout << calc_destination(i, K) << endl; }
}
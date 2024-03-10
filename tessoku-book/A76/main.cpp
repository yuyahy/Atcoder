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

typedef long long ll;
typedef pair<int, int> pii;

// mint
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

mint op(mint x, mint y) { return x + y; }
mint e() { return 0; }

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), W(0), L(0), R(0);
    cin >> N >> W >> L >> R;
    vector<ll> X(N + 2, 0);
    REP3(i, 1, N + 1) {
        ll tmp(0);
        cin >> tmp;
        X[i] = tmp;
    }
    X[N + 1] = W;
    dump(X);

    // 動的計画法と二分探索と累積和を組み合わせる

    // i番目の足場にたどり着く手段の数を管理するDPテーブル
    vector<mint> DP(N + 2);
    // 初期状態
    DP[0] = 1;
    vector<mint> sum(N + 2, 0);
    sum[0] = 1;
    REP3(i, 1, N + 2) {
        // 1. Xに対して二分探索し、Rだけジャンプする事でギリギリ届く最も離れた足場を求める
        auto farthest_pos = lower_bound(X.begin(), X.end(), X[i] - R);
        auto farthest_idx = distance(X.begin(), farthest_pos);
        // 2. Xに対して二分探索し、Lだけジャンプする事で最小のジャンプで届く最も近い足場を求める
        auto nearest_pos = lower_bound(X.begin(), X.end(), X[i] - L + 1);
        auto nearest_idx = distance(X.begin(), nearest_pos);
        nearest_idx--;
        dump(X[i], farthest_idx, nearest_idx);

        // 3. DPを更新
        if (nearest_idx == -1) DP[i] = 0;
        else DP[i] = sum[nearest_idx];
        if (farthest_idx >= 1) DP[i] -= sum[farthest_idx - 1];

        // 4. 累積和を更新
        sum[i] = sum[i - 1] + DP[i];
    }

    // Note: おそらく動的計画法の代わりにセグメント木でも解けると思うのだが、なぜかサンプルケースしか通らない
    // REP3(i, 2, N + 2) {
    //     // 1. Xに対して二分探索し、Rだけジャンプする事でギリギリ届く最も離れた足場を求める
    //     auto farthest_pos = lower_bound(X.begin(), X.end(),
    //                                     std::clamp(X[i] - R, (ll)0, X[i] - R));
    //     auto farthest_idx = distance(X.begin(), farthest_pos);
    //     // 2. Xに対して二分探索し、Lだけジャンプする事で最小のジャンプで届く最も近い足場を求める
    //     auto nearest_pos = lower_bound(
    //         X.begin(), X.end(), std::clamp(X[i] - L + 1, (ll)0, X[i] - L + 1));
    //     auto nearest_idx = distance(X.begin(), nearest_pos);
    //     if (nearest_idx > 0) nearest_idx--;

    //     dump(X[i], farthest_idx, nearest_idx);
    //     dump(seg.prod(farthest_idx, nearest_idx + 1).val());

    //     // 3. 区間[1., 2.]の総和を求める
    //     result.push_back(seg.prod(farthest_idx, nearest_idx + 1));
    //     seg.set(i, seg.prod(farthest_idx, nearest_idx + 1));
    // }

    cout << DP[N + 1].val() << endl;
}

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

// 最小長さがmid以上になる切り方は存在するか
bool isOK(ll mid, ll N, ll K, ll L, const vector<ll>& A) {
    ll left(0), right(0);
    ll cut_cnt(0);
    // REP(i, N) {
    //     if (A[i] - left >= mid && L - A[i] >= mid) {
    //         cut_cnt++;
    //         left = A[i];
    //     }
    // }
    while (true) {
        dump(mid, N, K, right, left, cut_cnt);
        if (A[right] - left >= mid && L - A[right] >= mid) {
            // 切る位置が見つかった
            left = A[right];
            right++;
            cut_cnt++;
        } else {
            // まだ短いので探索範囲を広げる
            right++;
        }
        if (right >= N) break;
    }
    // // K分割以上にできるか？
    return cut_cnt >= K;
}
/**
 * @brief 二分探索のテンプレート(めぐる式)
 *
 * @param key   比較対象の値(a[index] >= key という条件の探索対象)
 * @param ok    条件を満たす最大の初期値
 * @param ng    条件を満たさない最小の初期値
 * @return ll
 * @note 現状は条件を満たす最小の値を求めているが、設問によっては条件を満たす最大の値を返すパターンもある
 *       その場合は調べて改造して使用する必要がある
 */
ll binary_search(const ll N, const ll K, const ll L, ll ok, ll ng,
                 const vector<ll>& A) {
    // ok と ng のどちらが大きいかわからないことを考慮
    while (abs(ok - ng) > 1) {
        ll mid = (ok + ng) / 2;
        // 今見ているmidが条件を満たせば、右側の探索範囲を半分にする
        // そうでなければ左側の探索範囲を半分にする
        if (isOK(mid, N, K, L, A)) ok = mid;
        else ng = mid;
    }
    // 答えはwhileを抜けた時のokの値
    return ok;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), K(0), L(0);
    cin >> N >> L;
    cin >> K;
    vector<ll> A(N, 0);
    REP(i, N) cin >> A[i];
    auto result = binary_search(N, K, L, 0, 2e10, A);
    cout << result << endl;
}

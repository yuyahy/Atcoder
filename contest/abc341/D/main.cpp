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

// index が条件を満たすかどうか
bool isOK(ll mid, ll key, ll m, ll n) {
    auto calc_only_divide_one_side = [&](const ll x, const ll m,
                                         const ll n) -> ll {
        auto lcm = std::lcm(m, n);
        return (x / m) + (x / n) - 2 * (x / lcm);
    };
    ll result = calc_only_divide_one_side(mid, m, n);
    dump(result);
    if (result >= key) return true;
    else return false;
}

// 汎用的な二分探索のテンプレ
ll aa_binary_search(ll key, ll ok, ll ng, ll m, ll n) {
    // //「index = 0」が条件を満たすこともあるので、初期値は -1
    // int ng = -1;
    // // 「index = a.size()-1」が条件を満たさないこともあるので、初期値は a.size()
    // int ok = (int)a.size();
    /* ok と ng のどちらが大きいかわからないことを考慮 */
    while (abs(ok - ng) > 1) {
        ll mid = (ok + ng) / 2;
        dump(key, ok, ng, mid);
        dump(mid);

        if (isOK(mid, key, m, n)) ok = mid;
        else ng = mid;
    }
    dump(ok);
    return ok;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), M(0), K(0);
    cin >> N >> M >> K;

    // 愚直にやると、以下の様にN or Mの小さい方から、+1していき、
    // 現在の整数がN or Mのどちらかだけで割り切れる場合をカウントし、
    // Kになった所で打ち切りという方針になるが、今回はKのMAXが10^10なのでTLE

    // K番目の整数が何かを直接求めるのは上記の方法でないと難しいので視点を変える
    // ・ある整数Xが与えられた時に、その中に含まれるN or Mの一方でしか割り切れない整数はいくつあるか？
    // これは、F(X, N, M) = 床関数(X/N) + 床関数(X/M) - 2*床関数(X/LCM(N, M))で求められる
    // →ベン図をイメージすると、排他的論理和(XOR)に等しい
    // また、明らかにXが増加すれば、その中に含まれる条件を満たす整数の個数は増加するため、単調増加性がある。
    //
    // つまり今回の問題は、以下を満たす最小のXを求める事と言い換えられる
    // ・{ある整数Xが与えられた時に、その中に含まれるN or Mの一方でしか割り切れない整数の個数} ≧ K
    // そしてこれを求めるためには、二分探索を用いると、O(log(N))で解ける。
    // 1. 探索領域を[L, R] = [0, 10^18]とする
    // 2. F(mid, N, M)を求める、※mid = 床関数((L+R)/2)
    // 3-1. F(mid, N, M) = K であれば、この時のmidが答え(終了)
    // 3-2. F(mid, N, M) < K であれば、L_next = midとし、2.に戻る
    // 3-3. F(mid, N, M) > K であれば、R_next = midとし、2.に戻る

    // 整数XまでのN or Mでしか割り切れない整数の個数を求めるラムダ式
    // ※ 論理積の部分はlcmを求めた上で引く必要がある事に注意。
    //   e.g. M=10、N=6の場合、N*M=60だが、実際に求めたいのは30
    auto calc_only_divide_one_side = [&](const ll x, const ll m,
                                         const ll n) -> ll {
        auto lcm = std::lcm(m, n);
        return (x / m) + (x / n) - 2 * (x / lcm);
    };

    ll left(0), right(2e18), cnt(-1);
    ll result = aa_binary_search(K, right, left, M, N);
    cout << result << endl;

    // 以下はめぐる式ではなく、自前の実装(基本的な二分探索を繰り返して、探索範囲を半分にしていくのは同じ)
    // while (true) {
    //     auto mid = (left + right) / 2;
    //     dump(left, mid, right);

    //     cnt = calc_only_divide_one_side(mid, M, N);
    //     dump(cnt);
    //     bool b_div1 = (mid % N == 0);
    //     bool b_div2 = (mid % M == 0);
    //     if (cnt == K && (b_div1 ^ b_div2)) {
    //         cout << mid << endl;
    //         return 0;
    //     } else if (cnt < K) {
    //         left = mid;
    //     } else {
    //         right = mid;
    //     }
    // }
}

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

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0);
    cin >> N;
    vector<int> A(N, 0);
    REP(i, N) cin >> A[i];

    bool b_different_ans(true);

    if (b_different_ans) {
        // 別解
        // ソートせずに和の差分から欠けている数を求める
        // Aの中の最小値をA_minとすると、
        // ・(落とす前の手持ちの整数の和) = A_min + A_min+1 + A_min_2 + ...A_min+N
        // から落とした後の手持ちの整数の和を引くと、落とした整数が求められる。
        // ※A_minを[A_min, A_min+N]までの整数から引くと、[0, N]に変換できるので、これをインデックスとして
        //  利用し、vector<bool> (手持ちにi番目の整数があるかを管理する配列)に記録していく方針もあり
        // Note: 最小値はstd::ranges::min(A);で求められる

        // N個探索し総和を求める
        int A_min(INT_MAX / 2), sum(0);
        for (const auto& elem : A) {
            A_min = std::min(A_min, elem);
            sum += elem;
        }
        // 1からnまでの整数の和を求めるラムダ式
        auto calc_sum = [&](const int n) -> int { return n * (n + 1) / 2; };
        // A_minかAmin+Nまでの和を求める
        // →(1からAmin+Nまでの和) - (1からAmin-1までの和)
        int sum_expected = calc_sum(A_min + N) - calc_sum(A_min - 1);
        dump(sum_expected);
        cout << sum_expected - sum << endl;
    } else {
        // 本番提出解法
        // 昇順にソートしてから、欠けている数字を探す
        sort(A.begin(), A.end());

        auto check_num(A[0]);

        REP(i, N) {
            if (check_num != A[i]) {
                break;
            } else {
                check_num++;
            }
        }
        cout << check_num << endl;
    }
}

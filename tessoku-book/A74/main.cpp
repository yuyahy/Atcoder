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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    // 1. 各Kの座標を求める
    // 2. 行に着目し、現在の[K1, K2,...Kk]から[1, 2,...K]にするための最小手数を求める
    //    →転倒数を求める
    // 3. 列に着目し、同様に現在の状態から、[1, 2,...K]にするための最小手数を求める
    // 4. 行と列の転倒数の和が答え(行と列は独立しているので、3.の時に2.の状態を考慮する必要はない)

    // オーダー: O(2 * N^2)

    // 1. 各Kの座標を求める
    ll N(0);
    cin >> N;
    // <整数K, Kの座標>
    map<ll, pair<ll, ll>> number_pos;
    REP(i, N) REP(j, N) {
        ll P(0);
        cin >> P;
        if (P) number_pos[P] = {i, j};
    }

    // 2. 行に着目し、現在の[K1, K2,...Kk]から[1, 2,...K]にするための最小手数を求める
    //    →転倒数を求める
    // 転倒数を計算するためのラムダ式
    // ※転倒数→配列の左から順番に、「自分より左にいるのに自分より大きい数」の個数を足していった時の総和
    auto calc_inv_num = [](const int size, const auto& array) {
        auto result(0);
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (array[i] > array[j]) result++;
            }
        }
        return result;
    };
    vector<ll> current_column(N);
    REP(i, N) current_column[i] = number_pos[i + 1].first;
    auto cnt_column = calc_inv_num(N, current_column);

    // 3. 列に着目し、同様に現在の状態から、[1, 2,...K]にするための最小手数を求める
    vector<ll> current_row(N);
    REP(i, N) current_row[i] = number_pos[i + 1].second;
    auto cnt_row = calc_inv_num(N, current_row);

    cout << cnt_column + cnt_row << endl;
}

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

#define YESNO(T)               \
    if (T) {                   \
        cout << "YES" << endl; \
    } else {                   \
        cout << "NO" << endl;  \
    }
#define yesno(T)               \
    if (T) {                   \
        cout << "yes" << endl; \
    } else {                   \
        cout << "no" << endl;  \
    }
#define YesNo(T)               \
    if (T) {                   \
        cout << "Yes" << endl; \
    } else {                   \
        cout << "No" << endl;  \
    }

#define COUT(x) cout << (x) << endl
#define SCOUT(x) cout << (x) << " "
#define ENDL cout << endl

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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

// アルファベット(小文字大文字)
const string lower_alphabet = "abcdefghijklmnopqrstuvwxyz";
const string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 数字
const string integers = "0123456789";

ull floor(ull x, ull m) {
    // x を m で割った余りを計算し、m との合同を取ることで非負の余りに変換する
    ull r = (x % m + m) % m;

    // x から余りを引いて、m で割ることで商を計算する
    return (x - r) / m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 結果がかなり大きそうだが、大丈夫か？
    // - unsigned long long intで計算する(最大値: 18446744073709551615)
    // - 最悪で[1,10^9]を全て処理しないと行けないので、愚直は間に合わない
    // - [1, N]までの総和はN*(N+1)/2でO(1)で求められる
    // - 総和から{A or Bで割り切れる数の総和}を引いてみる？
    //      - {A or Bで割り切れる数の総和}はメモ化再帰で高速に求められる？
    //      -  [1, N]までのXの倍数からなる数列は初項X、交差X、項数floor(N, X)
    // - AとBの最小公倍数からなる等差数列分は足してあげないと、ダブって引き算する事になりそう

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 整数[1,N]の総和は公式を使ってO(1)で求められるという考察
    //      - 「A, Bの倍数でない物の和」を求めるより、「1からNの和からA, Bの倍数の和を引き、A, Bの最小公倍数の和を足す」という言い換え
    // - 改善点
    //      - 特になし

    ull N(0), A(0), B(0);
    cin >> N >> A >> B;

    // 初項:first、末項:整数max以下の等差数列の和を求めるラムダ式
    auto calc_arithmetic_sequence = [&](const ull first, const ull max) {
        ull n = floor(max, first);
        return n * (2 * first + (n - 1) * first) / 2;
    };

    auto all = N * (N + 1) / 2;
    auto a_multi_sum = calc_arithmetic_sequence(A, N);
    auto b_multi_sum = calc_arithmetic_sequence(B, N);
    auto lcm_multi_sum = calc_arithmetic_sequence(lcm(A, B), N);

    dump(a_multi_sum);
    dump(b_multi_sum);
    dump(lcm_multi_sum);

    // ※ド・モルガンの法則に注意し、積集合の部分をダブって引き算しない様にする(そのために最小公倍数の和を足している)
    COUT(all - a_multi_sum - b_multi_sum + lcm_multi_sum);
}

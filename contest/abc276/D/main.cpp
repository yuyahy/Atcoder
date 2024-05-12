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
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(m) - 1; (i) >= (int)(n); --(i))

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - N <= 1000なので制約は小さい
    // - シミュレーションで達成可否と最小手数を求めるというよりは、「達成可否は事前に判定」、「達成できる場合は最小手数を求める」？
    // - 互いに素なペアがあると絶対に目標を達成できない
    // - BFSでもいける？
    //      - サンプルは通ったが本番でTLE & WAした

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 解説を読みそのまま理解できたので、知識面は十分だったと考えられる
    // - 考察: {不十分}
    //      -  各整数が2^xi * 3^yi * {2でも3でも割り切れない整数: zi}で表せる事は思いついたが、
    //         そこから、{達成不可能なケース}、｛最小の手数の求め方｝が思いつかなかった。
    //      - 今回可能な操作(2 or 3の次数を1減らす)を考察すると、{達成不可能なケース}は分かったかもしれない
    // - 実装: {十分}
    //      - 解説を読んでから、自力で実装できたため
    //      - あえて言うなら、GCDであらかじめ配列全体の最大公約数を求めておくと処理が簡潔になる
    //        →GCD = 2^x_min * 3^y_min * {2でも3でも割り切れない整数: zi}なので、この値で各要素を割っておくと
    //         2と3を使って1まで割り切れるかを各要素でチェックするだけで良くなるため

    ll N(0);
    cin >> N;
    vector<ll> a(N, 0);
    for (auto& elem : a) cin >> elem;

    // 各整数は以下の様に表現できる
    // 2^xi * 3^yi * {2でも3でも割り切れない整数: zi}
    // 今回できる操作はxi、yiを1減らす操作だけなので、
    // zi ≠ zj となる様な組が一つでも存在すれば達成不可能である。
    // 一方、達成可能なケースの最小手数について考えてみると、
    // 手数を最小にするためには、xi, yiの最小値と一致する様に他の要素を割っていく必要がある。
    // このために必要な手数は、{xj, yj} - {xi, yiの最小値}の総和で求められる。
    auto extract_2_or_3 = [&](const ll num) {
        auto n = num;
        // 2のべき乗を計算
        ll power_of_2 = 0;
        while (n % 2 == 0) {
            ++power_of_2;
            n /= 2;
        }
        // 3のべき乗を計算
        ll power_of_3 = 0;
        while (n % 3 == 0) {
            ++power_of_3;
            n /= 3;
        }
        // 残りの整数
        ll remaining = n;

        return vector<ll>{power_of_2, power_of_3, remaining};
    };

    vector<vector<ll>> extract_A(N, vector<ll>(3, 0));
    REP(i, N) extract_A[i] = extract_2_or_3(a[i]);
    dump(extract_A);

    // zi ≠ zjの組がないかチェック
    REP(i, N - 1) REP3(j, i + 1, N) {
        if (extract_A[i][2] != extract_A[j][2]) {
            COUT(-1);
            return 0;
        }
    }

    // 最小手数を求める
    // 本設問では2 or 3で割る操作はそれぞれ独立に行えるので、単純にそれぞれの最小値を求めればOK
    // 1. 目的のxmin, yminを求める
    ll x_min(INF), y_min(INF);
    for (const auto& elem : extract_A) {
        x_min = min(x_min, elem[0]);
        y_min = min(y_min, elem[1]);
    }
    // 2. xmin, yminにするために必要な手数の合計を求める
    ll sum(0);
    for (const auto& elem : extract_A) {
        sum += (elem[0] - x_min) + (elem[1] - y_min);
    }
    COUT(sum);
}

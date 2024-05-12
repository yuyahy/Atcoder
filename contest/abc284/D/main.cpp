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
    // - 2変数の内、片方を固定するパターン？
    // - p = √(N/q) と式変形すると、Nは入力で与えられるので、√(N/q) = X^2になる様に二分探索？
    // - q = N / p^2と式変形したほうが平方根がでてこないので、楽かも
    //      - qは1以上なのでpmax = √Nmax = 3 * 10^9
    //      - しかしこの範囲の探索はTLEになりそう

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {不十分}
    //      - 素因数分解のアルゴリズムとして√Nまでの試し割りは知っていたが、その仕組は理解していなかった
    // - 考察: {不十分}
    //      - min(p, q) <= 3乗根(N)が成り立つので、3乗根(N)まで割ればp, qどちらかが分かるという発想がなかった
    //      - これは試し割りのアルゴリズムの仕組を理解していなかったのが原因と考えられる
    //      - 整数問題では素数判定をベースに、約数列挙や素因数分解が頻出だが、そのアルゴリズムの仕組を理解し、考察に使用する事が肝要
    //      - cf. https://qiita.com/drken/items/a14e9af0ca2d857dad23#4-%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3
    //      - ※素因数分解すると、ある整数は素因数を用いてどの様な表現ができるか、元の整数の制約から各素因数にはどの様な制約があるか...etcを考察する材料になる
    // - 実装: {十分}
    //      - 解説を読んでから自力で実装できたため

    ll T(0);
    cin >> T;
    REP(j, T) {
        ll tmp(0);
        cin >> tmp;

        for (ll i = 2; i * i * i <= tmp; i++) {
            if (tmp % i == 0) {
                if (tmp % (i * i) == 0) {
                    dump(i);
                    cout << i << " " << tmp / (i * i) << endl;
                } else {
                    cout << sqrt(tmp / i) << " " << i << endl;
                }
                break;
            }
        }
    }
}

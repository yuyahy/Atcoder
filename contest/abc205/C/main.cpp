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

#define ALL(a) (a).begin(), (a).end()

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

// 自前コード(logを使って比較)
// 一応ACのするが浮動小数点の比較演算を行っているので、精度によっては危ないコードかもしれない
ll solve1(ll A, ll B, ll C) {
    // std::log(0)は処理できないので事前にチェックする
    if (A == 0 and B == 0) {
        COUT("=");
        return 0;
    } else if (A == 0 and B != 0) {
        if (B > 0) {
            COUT("<");
            return 0;
        } else {
            if (C % 2 == 0) {
                COUT("<");
            } else {
                COUT(">");
            }
            return 0;
        }
    } else if (A != 0 and B == 0) {
        if (A > 0) {
            COUT(">");
            return 0;
        } else {
            if (C % 2 == 0) {
                COUT(">");
            } else {
                COUT("<");
            }
            return 0;
        }
    }

    auto calc_log = [&](const ll x, const ll c) {
        if (x > 0) return log(x);

        if (c % 2 == 0) return log(abs(x));
        else return -log(abs(x));
    };

    auto log_AC = calc_log(A, C);
    auto log_BC = calc_log(B, C);
    dump(log_AC);
    dump(log_BC);

    if (log_AC < log_BC) {
        COUT("<");
        return 0;
    } else if (log_AC > log_BC) {
        COUT(">");
        return 0;
    } else {
        COUT("=");
        return 0;
    }
}

// 別解(logを使わず整数で比較)
ll solve2(ll A, ll B, ll C) {
    // CはA、Bで同じだが、A or Bが負の値の場合はCの偶奇によって大小関係が変わる
    bool b_even = (C % 2 == 0);

    // Cが偶数の場合はA、Bの正負に関係なくpow()の結果は非負の整数値になる
    if (b_even) {
        A = abs(A);
        B = abs(B);
    }

    // Cが奇数の場合は、pow()の前後でA、Bの正負は変わらないのでそのまま計算可能
    if (A > B) COUT(">");
    else if (A < B) COUT("<");
    else COUT("=");

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 実際に値を計算すると64bit整数には収まらない: 10^9の10^9まであるので

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 一般的な大学受験でよくでるlogによる大小比較を知っていた
    //      - 0や負の場合のサンプルケースにないパターンも自分でテストして修正してから提出できた
    // - 改善点
    //      - 受験数学に引っ張られすぎた。solve2()の実装の様に更に考察すると浮動小数点を使わないですむ & 簡潔なコードにできる

    ll A(0), B(0), C(0);
    cin >> A >> B >> C;
    //solve1(A, B, C);
    solve2(A, B, C);
}

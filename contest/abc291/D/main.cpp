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
using mint = static_modint<998244353>;
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
    // - DP?
    //      - テーブル定義: 1からiまでのカードを裏返す or 裏返さなかった時に全ての隣り合うカードの向いている面に書かれている数が相異なる組の数
    //      - 遷移: DP[i+1] = DP[i] + ()
    //          - i+1番目のカードの表がi番目のカード

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 隣り合うカードのみに着目すればOK & bit全探索やグラフではない→DPという発想ができた
    //      - テーブル定義の考察は手書き2次元テーブルを書いて考察した
    // - 改善点

    ll N(0);
    cin >> N;
    vector<pll> cards(N, {0, 0});
    for (auto& elem : cards) cin >> elem.first >> elem.second;
    dump(cards);

    // テーブル定義: DP[i][2] = {i番目のカードをj(0: 表、1: 裏)にした時の隣り合うカードの向いている面に書かれている数が相異なる組の数}
    vector DP(N, vector<mint>(2, 0));
    // 初期状態:
    DP[0][0] = 1;
    DP[0][1] = 1;

    dump(DP[0][0].val());
    dump(DP[0][1].val());

    // 遷移:
    //          - i番目のカードの表 ≠ i+1番目のカードの表 → DP[i+1][0] += DP[i][0]
    //          - i番目のカードの裏 ≠ i+1番目のカードの表 → DP[i+1][0] += DP[i][1]
    //          - i番目のカードの表 ≠ i+1番目のカードの裏 → DP[i+1][1] += DP[i][0]
    //          - i番目のカードの裏 ≠ i+1番目のカードの裏 → DP[i+1][1] += DP[i][1]
    REP(i, N - 1) {
        dump(DP[i][0].val());
        dump(DP[i][1].val());

        // できれば組み合わせっぽく書いてコードの重複を減らしたい
        if (cards[i + 1].first != cards[i].first) {
            DP[i + 1][0] += DP[i][0];
        }
        if (cards[i + 1].first != cards[i].second) {
            DP[i + 1][0] += DP[i][1];
        }
        if (cards[i + 1].second != cards[i].first) {
            DP[i + 1][1] += DP[i][0];
        }
        if (cards[i + 1].second != cards[i].second) {
            DP[i + 1][1] += DP[i][1];
        }
        dump(DP[i + 1][0].val());
        dump(DP[i + 1][1].val());
    }

    // ※mint
    auto result = DP[N - 1][0] + DP[N - 1][1];
    COUT(result.val());
}

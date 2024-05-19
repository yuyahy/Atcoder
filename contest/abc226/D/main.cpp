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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - Nmax=500で制約は小さい
    // - iからjへ一回で移動する方法は{(xj - xi), (yj - yi)} とその符号を逆転した2種類
    // - ただし、同じ魔法を何回も使用できるので、他の移動魔法の倍数となる物は除外する

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 最大公約数(gcd)は知っていた
    // - 考察: {不十分}
    //      - 一通り列挙した後に他の移動魔法の倍数となる物は除外する方針しか思いつかなかった
    //          - 後から除外ではなく、std::setに挿入時に(X, Y)が互いに素の状態にしておくと多重ループが不要になる
    //      - つまり、「全列挙後に除外」だけでなく「列挙時に予め除外 or 最小単位にして挿入」という引き出しが必要
    //      - また、今回は実際に２次元座標にプロットした方が考察しやすかったかも
    // - 実装: {十分}
    //      - 方針を理解すれば何も見なくても実装できた
    // - メモ:
    /*
        負の値が混じっていてもstd::gcd()は絶対値を取って最大公約数を返す
        なので0除算や負の除算は考慮しなくて良い
        ※返り値は符号つき整数なので、答えがめちゃくちゃ大きいとオーバーフローして負の整数が返ってくる事があるらしい(by 公式ドキュメント)
        [dump] gcd(10, 0) => 10
        [dump] gcd(-12, -6) => 6
        [dump] gcd(12, -6) => 6
     */

    ll N(0);
    cin >> N;
    vector<pll> xy(N, {0, 0});
    for (auto& elem : xy) cin >> elem.first >> elem.second;

    set<pll> magics;
    REP(i, N - 1) REP3(j, i + 1, N) {
        auto magic_X = xy[i].first - xy[j].first;
        auto magic_Y = xy[i].second - xy[j].second;
        auto d = gcd(magic_X, magic_Y);

        magics.insert({magic_X / d, magic_Y / d});
        magics.insert({-magic_X / d, -magic_Y / d});
    }
    dump(magics);
    dump(gcd(10, 0));
    dump(gcd(-12, -6));
    dump(gcd(12, -6));
    COUT(magics.size());
}

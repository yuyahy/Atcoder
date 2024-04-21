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

    ll K(0);
    cin >> K;

    // 方針1: 充分そうと思われるX番目までの321-like numberを全列挙
    //       →Kのサイズが不明なのでこの方針で間に合うのか分からない

    // 方針2: 性質を利用して、N番目をO(1)で求める

    // Note:
    // - 解説AC
    // - 全列挙する方針はあっていた
    // - 0,1,2,3,...,9までの数字をそれぞれ一回使う or 使わないという選択しかできないので、実はKに関係なく高々1024通りしか作れない
    //   また、x >0という条件がかるので0と{}の何も使わないパターンは除外され、合計1024-2 = 1022通り

    // 重要な性質:
    //  - 同じ数字は一回しか出現しない
    //  - 使う数字が決まると、そこから作られる321-numberは一通りしか存在しない

    // どうすれば解けたか？
    // - 知識: 充分。bit全探索や考え方は納得できる物だった。
    // - 考察: 不十分。
    //        - 条件を満たす整数が幾つくらいできそうかという見積もりが全くできていなかった。
    //        - 逆に見積もるためには、上記の性質を考察する必要があり、この考え方があればbit全探索の方針は自然。

    // bit全探索で2^10 -2 = 1022通りを全列挙する
    // {0, 1, ..., n-1} の部分集合の全探索
    int n = 10;
    vector<ll> like_numbers;
    for (int bit = 0; bit < (1 << n); ++bit) {
        /* bit で表される集合の処理を書く */

        /* きちんとできていることを確認してみる */
        // bit の表す集合を求める
        ll num(0);
        REP_R(i, n) {
            if (bit & (1 << i)) {  // i が bit に入るかどうか
                num *= 10;
                num += i;
            }
        }
        if (bit > 0) like_numbers.push_back(num);
    }
    sort(like_numbers.begin(), like_numbers.end());
    dump(like_numbers);
    cout << like_numbers[K] << endl;
}

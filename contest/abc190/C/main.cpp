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
    // - 貪欲？
    // - K: [1,16]なのでbit全探索でいけそう(0: Ciに置く、1: Diに置くという様に対応づける)

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 最初貪欲を疑ったが、選択肢がC or Dのいずれかの2通りしかない事、Kの制約が小さい事からbit全探索を思いついた
    //        →2つの選択肢しかない系問題はまずbit全探索でいけないか考えるのはあり(ただしN<=20でないと無理)
    // - 改善点
    //      - 解法は合っていたが探索のインデックスミスで1ペナ。よろしくない

    ll N(0), M(0);
    cin >> N >> M;

    // 以下の様に予め配列長を指定しておけば、範囲ベースfor文で一時変数を作らずにループできる
    vector<pair<ll, ll>> conditions(M, {0, 0});
    for (auto& [A, B] : conditions) cin >> A >> B;

    ll K(0);
    cin >> K;
    vector<pair<ll, ll>> person(K, {0, 0});
    for (auto& [C, D] : person) cin >> C >> D;

    // {0, 1, ..., n-1} の部分集合の全探索
    ll satisfy_cnt(-1);
    for (int bit = 0; bit < (1 << K); ++bit) {
        /* bit で表される集合の処理を書く */
        vector<ll> dishes(N, 0);
        // bit の表す集合を求める
        for (int i = 0; i < K; ++i) {
            if (bit & (1 << i)) {  // i が bit に入るかどうか
                dishes[person[i].first - 1] = 1;
            } else {
                dishes[person[i].second - 1] = 1;
            }
        }
        // 条件を満たしている物をカウントする
        ll cnt(0);
        for (const auto& [A_cond, B_cond] : conditions) {
            if (dishes[A_cond - 1] && dishes[B_cond - 1]) cnt++;
        }
        satisfy_cnt = std::max(satisfy_cnt, cnt);
    }
    COUT(satisfy_cnt);
}

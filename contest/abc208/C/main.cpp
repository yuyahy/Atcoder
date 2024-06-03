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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 全員に配れる個数は K//Nで求められる
    // - 全員に配れない場合は、aiの小さい順に、K'個配れる

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 愚直だとTLEなので、周期性というか先に配れるだけ配ってしまう→余りを番号の小さい順に配るという方針が直ぐ思いついた
    // - 改善点
    //      - mapを初期化するのを忘れており、加算が行われない実装をしてしまった
    //      - sortしたAを使いまわしており、最後の結果出力が元の配列と順番が変わってしまっていた
    // - メモ
    //      - std::iota()を使うと、指定された値から始まる整数列を1行で生成できる
    //        cf. https://cpprefjp.github.io/reference/numeric/iota.html

    ll N(0), K(0);
    cin >> N >> K;
    vll A(N, 0);
    for (auto& elem : A) cin >> elem;

    auto A_sorted = A;
    sort(ALL(A_sorted));

    // <国民番号、配られたお菓子の数>
    map<ll, ll> provide_cnt;
    for (const auto elem : A_sorted) provide_cnt[elem] = 0;
    while (true) {
        if (K >= N) {
            // 全員に配れる場合
            ll can_provide = K / N;
            dump(can_provide);
            for (auto& pair : provide_cnt) {
                pair.second += can_provide;
            }
            K -= N * can_provide;
            dump(K);
        } else {
            // K'人しか配れない場合
            REP(i, K) { provide_cnt[A_sorted[i]]++; }
            break;
        }
    }
    for (const auto& elem : A) COUT(provide_cnt[elem]);
}

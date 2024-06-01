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
    // - N,Mmax=10^5なので全てのAiに対して互いに素なKを愚直に列挙する事はできない
    // - M以下の素数を全列挙する
    //      - エラトステネスの篩？
    // - Aに含まれている物を除外する

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 整数問題はまず素因数分解してみる、というアプローチを取れた
    //      - いつぞやの整数問題の失敗を踏まえ、有名アルゴリズム(素数列挙、約数列挙、エラトステネスの篩...etc)の原理を思い出し、
    //         エラトステネスの篩と似たアイデアで解けるとわかった
    // - 改善点
    //      - 何も整数問題の性質を調べる事もなく解けると良い

    ll N(0), M(0);
    cin >> N >> M;
    vector<ll> A(N, 0);
    for (auto& elem : A) cin >> elem;

    // Aiの約数を列挙する　O(N√N)
    // 約数の集合
    set<ll> divisors;
    for (const auto& elem : A) {
        for (long long i = 1; i * i <= elem; ++i) {
            if (elem % i == 0) {
                divisors.insert(i);
                // 重複しないならば i の相方である elem/i も push
                if (elem / i != i) divisors.insert(elem / i);
            }
        }
    }
    dump(divisors);

    // エラトステネスの篩に似た考え方で、
    // M以下の整数の中で、divisorsを約数に持たない整数を列挙する
    vector<bool> common_primes(M + 1, true);
    common_primes[0] = common_primes[1] = true;
    for (const auto elem : divisors) {
        // 判定済み
        if (elem == 0 or elem == 1 or !common_primes[elem]) continue;
        // pを含むpの倍数から素数ラベルを剥奪
        // ※今回は素数列挙ではないので、エラトステネスの篩とは異なり、p自身も除外する必要がある
        for (int q = elem; q <= M; q += elem) {
            common_primes[q] = false;
        }
    }
    dump(common_primes);

    ll count_true = std::count(ALL(common_primes), true);
    COUT(count_true - 1);
    REP3(i, 1, M + 1) {
        if (common_primes[i]) COUT(i);
    }
}

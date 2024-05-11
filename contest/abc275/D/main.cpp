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

ll floor(ll x, ll m) {
    // x を m で割った余りを計算し、m との合同を取ることで非負の余りに変換する
    ll r = (x % m + m) % m;

    // x から余りを引いて、m で割ることで商を計算する
    return (x - r) / m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - N=[0, 10^18]と非常に大きい
    // - いかにもメモ化再帰っぽい問題

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 問題の制約や形式からABC340-Cで学んだ事を思い出し、メモ化再帰で対応できた
    // - 改善点
    //      - 答えをメモする所を実装し忘れて1ペナ。非常に勿体ないので、メモ化再帰のときは一旦過去ソースを参照してから対応する。
    //      - メモ化再帰が有効な問題の特徴として、「再帰関数に与える引数のバリエーションが少ない(log2N程度)」という物がある。
    //          - バリエーションが大きいとメモした答えを再利用できる機会が少なくなり、高速化に寄与しにくいという理解。
    //          - 本設問では[N/2^x3^y]が引数のバリエーション。雑に3^yの部分を無視すると、2^x→x=log2N程度しか存在しない事が見積もれる

    ll N(0);
    cin >> N;

    // 答えをメモするmap
    map<ll, ll> memo;
    // ベース
    memo[0] = 1;
    auto func = [&](auto self, const ll k) -> ll {
        // 既に計算済みの引数の場合はそれを返す
        if (memo.count(k)) return memo[k];
        // 一回求めた答えはメモしておく
        memo[k] = self(self, floor(k, 2)) + self(self, floor(k, 3));
        return memo[k];
    };

    COUT(func(func, N));
}

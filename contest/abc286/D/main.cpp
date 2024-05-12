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
    // - 既視感(鉄則？)
    // - 大きい硬貨から貪欲に消費しておけばOK？
    //      - 駄目でした
    // - 半分全列挙だったら間に合うか？
    //      - 集合を2つに分ければもう一方はX - 現在注目している数をもう一方の集合で二分探索できる
    // - しかし今回は硬貨を使う/使わないだけでなく、使う場合は何枚使うかを考える必要がある
    // - BFS、DFSで実装してみたが、いずれもTLEになったのでDPで実装した

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - BFS、DFSで上手くいかなかったのでDPに方針転換した所上手くいった
    // - 改善点
    //      - DPに至る思考の過程が言語化できていない
    //      - 精進だったのでBFS、DFSで上手くいかない→DPを試すができたが、本番ではそこまでの時間はないため、
    //        なるべく早く正しい方針に着手 & 実装できる様になる必要がある

    ll N(0), X(0);
    cin >> N >> X;

    vector<pair<ll, ll>> AB(N, {0, 0});
    for (auto& elem : AB) cin >> elem.first >> elem.second;

    // テーブル定義: DP[i][j] i番目までの硬貨を使ってその和をちょうどjにできるか
    const ll max = 10000;
    vector DP(N, vector<ll>(X + 1, 0));
    // 初期値
    REP(i, N) DP[i][0] = 1;
    // 漸化式
    // DP[i-1][j - AB[i].first*AB[i].second] = 1 or j == AB[i].first*AB[i].second
    REP(i, N) REP(j, X + 1) {
        REP(k, AB[i].second + 1) {
            // dump(j - AB[i].first * k);
            DP[i][j] |= (j == AB[i].first * k);
            if (i - 1 >= 0 and j - AB[i].first * k >= 0) {
                DP[i][j] |= (DP[i - 1][j - AB[i].first * k]);
            }
        }
    }

    bool result(false);
    REP(i, N) result |= DP[i][X];
    dump(DP);
    YesNo(result);
}
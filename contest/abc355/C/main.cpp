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
    // unordered_set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 特別な知識は必要ない問題だった
    // - 考察: {不十分}
    //      - ダメ元でビンゴの集合を生成、シミュレーションしてみたがTLE(計算量が厳しいことは分かっていたが)
    //      - 素直に各行、列、斜め×2の印を付けたマスの数をカウントするだけで良かった
    //          - あるマスが斜めの列に属しているかのチェックは注意が必要
    //              - 右上→左下はx==yの時
    //              - 左上→右下はx+y == N-1
    //      - 愚直ループはできないが、O(N) * 定数倍(今回だとMAX=行、列、斜めをいれた4通り)だと解けるタイプの問題
    // - 実装: {十分}
    //      - 方針がわかれば簡単

    ll N(0), T(0);
    cin >> N >> T;
    vector<ll> A(T, 0);
    for (auto& elem : A) cin >> elem;

    vector<ll> row(N, 0), column(N, 0), slants(2, 0);
    ll result(0);
    for (auto elem : A) {
        result++;
        auto x = (elem - 1) % N;
        auto y = (elem - 1) / N;

        // 縦
        row[x]++;
        if (row[x] == N) {
            COUT(result);
            return 0;
        }
        // 横
        column[y]++;
        if (column[y] == N) {
            COUT(result);
            return 0;
        }
        // 斜め1(左上→右下)
        if (x == y) {
            slants[0]++;
            if (slants[0] == N) {
                COUT(result);
                return 0;
            }
        }
        // 斜め2(右上→左下)
        if (N - x - 1 == y) {
            slants[1]++;
            if (slants[1] == N) {
                COUT(result);
                return 0;
            }
        }
    }
    COUT(-1);
}

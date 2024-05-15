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
    // - 10^5なのでbit全探索によるシミュレーションはできない
    // - 操作Gの結果は元の数の倍数 e.g. 2なら[0,2,4,6,8]のいずれか
    // - 操作の構造はstack
    // - アプローチが思いつかない(シミュレーションを高速化できるのか、数学的な考察でO(1)とかで解けるのか)

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 動的計画法は知識としては知っていたので十分
    // - 考察: {不十分}
    //      - 正直とっかかりが思いつかなかった
    //      - 例えばbit全探索だと解けないが、DPだと計算量が減って解けるケースがどういうケースなのかが分かっておらず
    //        解法の引き出しにない状態
    //      - 直前 or 直後の結果のみ参照すれば情報として十分な問題はDPが使えそう(e.g. 2^Xがとてつもなく大きくなるケース)
    //      - bit全探索は文字通り全ての操作を列挙する事ができる
    //      - DPは最終的な解にしか興味がない
    // - 実装: {不十分}
    //      - DPの遷移の実装でバグらせた
    //      - mintを使うのを忘れて1ペナ

    ll N(0);
    cin >> N;
    vector<ll> A(N, 0);
    for (auto& elem : A) cin >> elem;

    // テーブル定義: DP[i][j] 左からi番目までを処理した時点で、その時点の一番左の要素をjにする方法は何通りあるか
    vector DP(N, vector<mint>(10, 0));
    // 初期値
    DP[0][A[0]] = 1;
    // dump(DP);
    // 遷移:
    // - 操作F→DP[i][(j+A[i])%10] += DP[i][j];
    // - 操作G→DP[i][(j*A[i])%10] += DP[i][j];

    REP3(i, 0, N - 1) {
        REP(j, 10) {
            DP[i + 1][(j + A[i + 1]) % 10] += DP[i][j];
            DP[i + 1][(j * A[i + 1]) % 10] += DP[i][j];
        }
    }

    dump(DP[N - 1]);

    for (const auto& elem : DP[N - 1]) COUT(elem.val());
}

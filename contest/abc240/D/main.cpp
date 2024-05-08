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
    // - 普通にstackでシミュレーションすれば良さそう
    // - 愚直にやっても最大で各球の出し入れが一回ずつ行われるだけなので間に合う
    // - そのままstackに個数分詰めると、消去後の連続している個数の管理が面倒
    // - ランレングス圧縮っぽくpairで持つ

    // Note:
    // - 結果: 自力AC(1ペナ)
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 計算量的にstackで愚直にシミュレーションできる事が分かった
    //      - 1ペナ後に愚直にボールをstackに積むよりもpairで管理した方が簡単な事に気がついた
    // - 改善点
    //      - 当初の解法が嘘解法だったが提出するまでロジックの穴に気がつく事ができなかった
    //      - 提出時に若干これでいいのかな？と思いながら提出してしまったので、立ち止まるべきだった

    ll N(0);
    cin >> N;
    // <数字、連続している個数>
    stack<pair<ll, ll>> balls;

    ll current_num(-1), cnt(0);
    REP(i, N) {
        ll a(0);
        cin >> a;

        cnt++;

        if (balls.empty()) {
            balls.push({a, 1});
        } else {
            // 同じボールが連続している場合
            if (balls.top().first == a) {
                balls.top() = {balls.top().first, balls.top().second + 1};
                // ボール:KがK個連続している場合
                if (balls.top().first == balls.top().second) {
                    cnt -= balls.top().second;
                    balls.pop();
                }
            } else {
                balls.push({a, 1});
            }
        }
        COUT(cnt);
    }
}

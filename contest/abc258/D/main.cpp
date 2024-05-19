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
    // i回目の選択肢
    //      - 既にクリアしたステージのゲームプレイのみを行う(B分間、最小値で良い)
    //      - 新たなステージ２のストーリー映像とゲームプレイの両方を行う(A+B分間)
    // - 貪欲で最適解を求めるのは難しそうなので、何等かの形で全探索
    // - DP?
    //      - テーブル定義: DP[i][j] : i回目にj番目までのステージをクリアした時にかかる最小の時間
    //      - 答えDP[X-1][j]の最小値
    //      - よくよく考えるとXmax=10^9なのでインデックスには使えない

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - Xが大きいのでDPの添字に含むことはできないが、i番目までのステージをクリアした際の最小のゲームプレイ時間がわかれば
    //        実際にシミュレーションする必要はない事に気がつけた
    //      - ステージiにいる時にできる事は？という考察が良かったのかもしれない
    // - 改善点

    ll N(0), X(0);
    cin >> N >> X;
    vector<pll> AB(N, {0, 0});
    for (auto& elem : AB) cin >> elem.first >> elem.second;

    // 「i回ステージ目まで順番にプレイし、残った回数をその時点のゲームプレイ時間が最小のステージで消費する」
    // を試して最小値を探す
    ll sum_min(INF), play_min(INF), accum_stage_clear_time(0);
    REP(i, N) {
        accum_stage_clear_time += AB[i].first + AB[i].second;
        play_min = min(play_min, AB[i].second);
        auto time = accum_stage_clear_time + (X - i - 1) * play_min;
        sum_min = min(sum_min, time);
    }
    COUT(sum_min);
}

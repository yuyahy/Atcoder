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

// 自前実装(DFS)
void solve1(const ll X, const vector<ll>& A, const set<ll>& B) {
    // その段が既に訪問済みかを表現する
    // Note: この訪問済みかの情報を使わないといくつかのケースでTLEする。
    //       基本的に再帰関数を書く時はこの様な情報を持ち、再度同じパラメータで再帰しない様に実装する方が安全かも
    const ll MAX =
        1e6;  // X-1段目に到達し、そこからAmax移動してX段目を飛び越すケースが到達しうる最大の段数
    vector<bool> seen(MAX, false);
    auto dfs = [&](auto self, const ll current_step,
                   vector<bool>& seen) -> bool {
        // 訪問済みの段として記録
        seen[current_step] = true;
        // モチ or 行き過ぎたらNG
        if (B.count(current_step) || current_step > X) return false;
        // ちょうどX段目ならOK
        if (current_step == X) return true;

        // 現在注目している段から行ける段について再帰的に探索
        bool result(false);
        for (const auto& step : A) {
            auto next_step = current_step + step;
            if (seen[next_step]) continue;
            result = self(self, next_step, seen);
            if (result) break;
        }
        return result;
    };

    YesNo(dfs(dfs, 0, seen));
}

// 解説実装(DP)
void solve2(const ll X, const vector<ll>& A, const set<ll>& B) {
    // 1. テーブル定義: DP[i]: {i段目に到達できるか(到達できる場合は1)}
    vector<ll> DP(X + 1, 0);
    // 2. 初期状態:
    DP[0] = 1;
    // 3. 遷移: DP[i-Aの全ての要素]の内一つでも1があれば1, それ以外は0

    REP(i, X + 1) {
        // モチの段は到達不可
        if (B.count(i)) continue;
        for (const auto& elem : A) {
            // Note: i - A[i]は負になる可能性もある
            // 「少なくとも一つTrueになるか？」はデフォルト値をfalseとし、or演算を使うと中間変数が不要になる
            DP[i] |= (i - elem >= 0 and DP[i - elem]);
        }
    }
    YesNo(DP[X]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 「N通りの上がり方(A1,A2...An)を選択し、Bi段を避けてX段目に到達できるか？」
    // - DPで判定？
    // - DFSでもできそう
    //  - O(N+M) = O(Xmax+Amin) = O(2*10^5)程度？

    // Note:
    // - 結果: 自力AC(TLEで1ペナ)
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - DFSによる言い換えができた点
    //      - DFSを色々書いて、適応範囲が広くなったのが良い
    // - 改善点
    //      - 最初の提出時はseen[]による同じパラメータでの再帰を防止する機構を省いてTLEした
    //          - この機構はDFS時には必ず実装しておく方が安全かもしれない
    //      - 最初に浮かんできたDPは自信がないのでDFSにしたが、いつかはDPもできる様にならないといけない

    ll N(0), M(0), X(0);
    cin >> N;
    vector<ll> A(N, 0);
    for (auto& elem : A) cin >> elem;
    cin >> M;
    set<ll> B;
    REP(i, M) {
        ll b(0);
        cin >> b;
        B.insert(b);
    }
    cin >> X;

    // solve1(X, A, B);
    solve2(X, A, B);
}

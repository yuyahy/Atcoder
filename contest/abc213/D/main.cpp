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
    // - vector<priority_queue<ll>> でグラフ構造作ってDFS?
    // - O(N+M) = O(4 * 10^5)程度

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 設問を読んで「これDFSの訪問順が昇順になっているだけじゃん」とすぐ理解できたため
    // - 改善点
    //      - 特になしだが、強いて言えばpriority_queueはデフォルトが降順なので注意(std::sort()の逆)

    ll N(0);
    cin >> N;

    vector<priority_queue<ll, vll, greater<ll>>> non_directed_graph(N);

    REP(i, N - 1) {
        ll A(0), B(0);
        cin >> A >> B;
        A--;
        B--;

        non_directed_graph[A].push(B);
        non_directed_graph[B].push(A);
    }

    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self,
                   vector<priority_queue<ll, vll, greater<ll>>>& Graph,
                   const ll vertex, vector<bool>& seen) -> void {
        // 訪問済みの頂点として記録
        seen[vertex] = true;

        SCOUT(vertex + 1);

        // 現在注目している頂点と隣接している頂点に対して再帰
        while (!Graph[vertex].empty()) {
            auto next_vertex = Graph[vertex].top();
            Graph[vertex].pop();
            if (seen[next_vertex]) continue;
            self(self, Graph, next_vertex, seen);

            SCOUT(vertex + 1);
        }
    };

    vector<bool> seen(N, false);
    dfs(dfs, non_directed_graph, 0, seen);
    ENDL;
}

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
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))

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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    // TODO: これを解いてから挑戦→adt/adt_easy_20240118_3/E/main.cpp

    // ※グラフが連結→どの頂点も行き来可能という事

    int N(0), M(0);
    cin >> N >> M;

    // 無向グラフを表現する隣接リスト
    vector<vector<int>> non_directed_graph(N);
    int A(0), B(0);
    REP(i, M) {
        cin >> A >> B;
        non_directed_graph[A - 1].push_back(B - 1);
        non_directed_graph[B - 1].push_back(A - 1);
    }
    dump(non_directed_graph);

    // その頂点が既に訪問済みかを表現する
    vector<bool> seen(N, false);

    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, const vector<vector<int>>& Graph,
                   const int vertex, vector<bool>& seen) -> void {
        // 訪問済みの頂点として記録
        seen[vertex] = true;
        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            if (seen[next_vertex]) continue;
            self(self, Graph, next_vertex, seen);
        }
    };

    // 行きがけ順(親 -> 左の子 -> 右の子): 左ノードから順に探索していき、最初に見つかった順番
    // 帰り順(左の子 -> 右の子 -> 親): 左ノードから順に探索していき、子ノードの探索が完了した物の順番

    // DFSでグラフ全体が連結しているかチェックする
    dfs(dfs, non_directed_graph, 0, seen);
    bool b_connected(true);
    REP(i, N) {
        if (!seen[i]) {
            b_connected = false;
            break;
        }
    }
    auto result =
        b_connected ? "The graph is connected." : "The graph is not connected.";
    cout << result << endl;
}

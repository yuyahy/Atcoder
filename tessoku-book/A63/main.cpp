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

    // BFSで各頂点の頂点1からの最短経路を出力する

    // BFSのためのデータ構造
    // 頂点1からの最短経路を記録するリスト
    vector<int> shortest_distance(N, -1);
    // 現在見つかっていて未訪問の頂点のリスト
    queue<int> next_verticies;

    shortest_distance[0] = 0;
    next_verticies.push(0);

    // BFS(幅優先探索)、計算量O(N+M)→各頂点と各辺がそれぞれ1回ずつ処理されるため
    while (!next_verticies.empty()) {
        auto current_vertex = next_verticies.front();
        next_verticies.pop();

        for (const auto& next_vertex : non_directed_graph[current_vertex]) {
            if (shortest_distance[next_vertex] != -1) continue;
            // 最短距離を更新
            // 辺の重み=1なので、隣接している頂点までは、現在注目している頂点+1の経路でアクセスできる
            shortest_distance[next_vertex] =
                shortest_distance[current_vertex] + 1;
            next_verticies.push(next_vertex);
        }
    }

    for (const auto& dist : shortest_distance) cout << dist << endl;
}

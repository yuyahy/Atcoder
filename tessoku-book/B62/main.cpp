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
                   const int vertex, vector<bool>& seen, const int goal_vertex,
                   stack<int>& path, bool& b_find) -> void {
        // 訪問済みの頂点として記録
        seen[vertex] = true;
        // 頂点Nに到達した場合
        if (vertex == goal_vertex) {
            path.push(vertex + 1);
            b_find = true;
            return;
        }
        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            if (seen[next_vertex]) continue;
            self(self, Graph, next_vertex, seen, goal_vertex, path, b_find);
            // 既に頂点Nに到達していた場合は、往路を記録
            // とりあえずstackに訪問した頂点を積んでいき、行き止まりだった場合は最後に積んだ頂点を削除する
            // 方針でも解ける
            if (b_find) {
                path.push(vertex + 1);
                return;
            }
        }
    };

    // 経路を記録するためのstack
    stack<int> path;
    // 頂点Nに到達したか
    bool b_find(false);
    dfs(dfs, non_directed_graph, 0, seen, N - 1, path, b_find);

    dump(path);

    while (!path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
}

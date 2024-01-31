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

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0);
    cin >> N;

    // 有向グラフを表現する隣接リスト
    vector<vector<int>> non_directed_graph(N);
    int A(0);
    REP3(i, 1, N) {
        cin >> A;
        non_directed_graph[A - 1].push_back(i);
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

    dump(shortest_distance);

    // 最短距離が大きい物から順番に部下の数をカウントする
    vector<bool> is_checked(N, false);
    vector<int> result(N, 0);

    // 優先度付きキューで降順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<int, int>& left,
                          const pair<int, int>& right) {
        if (left.first == right.first) {
            return left.second < right.second;
        } else {
            return left.first < right.first;
        }
    };
    // <頂点1からの距離, 頂点番号>を降順で管理する優先度付きキュ＝
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   decltype(custom_comp)>
        current_max_dist(custom_comp);
    REP(i, N) current_max_dist.push({shortest_distance[i], i});
    // 距離が大きい順にたどっていく
    while (!current_max_dist.empty()) {
        auto tmp = current_max_dist.top();
        auto& [dist, current_vertex] = tmp;
        dump(current_max_dist.top());
        current_max_dist.pop();

        int sum(0);
        for (const auto& elem : non_directed_graph[current_vertex]) {
            // 自身の直属の部下が持つ部下の人数
            sum += result[elem];
            // 自身の直属の部下の人数
            sum++;
        }
        result[current_vertex] = sum;
    }
    for (const auto& elem : result) cout << elem << " ";
    cout << endl;
}

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

// 優先度付きキューで昇順ソートするための比較関数
// bool custom_comp(const pair<int, int>& left, const pair<int, int>& right) {
//     if (left.second == right.second) {
//         return left.first < right.first;
//     } else {
//         return left.second < right.second;
//     }
// }

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0), M(0);
    cin >> N >> M;

    // 無向グラフを表現する隣接リスト
    vector<vector<int>> non_directed_graph(N);
    // 頂点をつなぐ辺の重み
    map<pair<int, int>, int> edge_weight;
    int A(0), B(0), C(0);
    REP(i, M) {
        cin >> A >> B >> C;
        non_directed_graph[A - 1].push_back(B - 1);
        non_directed_graph[B - 1].push_back(A - 1);
        edge_weight[{A - 1, B - 1}] = C;
        edge_weight[{B - 1, A - 1}] = C;
    }
    dump(non_directed_graph);
    dump(edge_weight);

    // ダイクストラ法で頂点1からkまでの最短経路長を求める
    // ※ダイクストラ法は辺の重みが非負の場合しか使えない

    // 優先度付きキューで昇順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<int, int>& left,
                          const pair<int, int>& right) {
        if (left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first > right.first;
        }
    };

    // 最短距離を保持するリスト
    constexpr int MAX = 1e8;
    vector<int> min_results(N, MAX);
    // <現在注目している頂点の頂点1からの最小距離, 頂点の番号>
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   decltype(custom_comp)>
        current_min_dist(custom_comp);
    current_min_dist.push({0, 0});
    min_results[0] = 0;

    // TODO: check TLEとWA→まずはアルゴリズムの理解を試みる
    while (!current_min_dist.empty()) {
        auto [min_dist, current_vertex] = current_min_dist.top();
        current_min_dist.pop();
        // 現在注目している頂点の最短距離を確定する
        min_results[current_vertex] =
            min(min_results[current_vertex], min_dist);

        for (const auto& next_vertex : non_directed_graph[current_vertex]) {
            if (min_results[next_vertex] != MAX) continue;
            auto next_vertex_dist = min_results[current_vertex] +
                                    edge_weight[{current_vertex, next_vertex}];

            // 現在注目している頂点に隣接している頂点を候補としてキューに追加
            current_min_dist.push({next_vertex_dist, next_vertex});
        }
    }

    for (const auto& dist : min_results) cout << dist << endl;

    // current_min_dist.push({3, 4});
    // current_min_dist.push({5, 6});

    // current_min_dist.push({1, 2});

    // dump(current_min_dist);
    // while (!current_min_dist.empty()) {
    //     dump(current_min_dist.top());
    //     current_min_dist.pop();
    // }
}

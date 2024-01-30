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

    ll N(0), M(0);
    cin >> N >> M;

    // 無向グラフを表現する隣接リスト
    vector<vector<ll>> non_directed_graph(N);
    // 頂点をつなぐ辺の重み
    map<pair<ll, ll>, ll> edge_weight;
    ll A(0), B(0), C(0);
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
    // 計算量はO(MlogM): 全頂点の次数(頂点に接続する辺の数)はそれぞれ2なので、合計2Mになり、優先度付きキューに頂点を追加するのにlogMかかるため

    // 優先度付きキューで昇順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<ll, ll>& left, const pair<ll, ll>& right) {
        if (left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first > right.first;
        }
    };

    constexpr ll MAX = 1e12;
    // 最短距離を保持するリスト
    vector<ll> min_results(N, MAX);
    // 既に最短距離が確定済みの頂点かの情報を保持するリスト
    vector<bool> is_checked(N, false);
    // <現在注目している頂点の頂点1からの最小距離, 頂点の番号>の優先度付きキュー
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(custom_comp)>
        current_min_dist(custom_comp);
    current_min_dist.push({0, 0});
    min_results[0] = 0;

    // <自身の頂点番号, 頂点1からの最短経路で、自身の一個前の頂点の番号>
    map<ll, ll> route_map;

    while (!current_min_dist.empty()) {
        // 探索候補の中で頂点1から距離が最短の物を取り出す
        auto [min_dist, current_vertex] = current_min_dist.top();
        current_min_dist.pop();
        if (is_checked[current_vertex]) continue;
        // 現在注目している頂点の最短距離を確定する
        is_checked[current_vertex] = true;
        // 隣接している頂点をチェック
        for (const auto& next_vertex : non_directed_graph[current_vertex]) {
            auto next_vertex_dist = min_results[current_vertex] +
                                    edge_weight[{current_vertex, next_vertex}];
            // 最短距離を更新できない場合は以降の処理は不要
            if (min_results[next_vertex] < next_vertex_dist) continue;
            // 現在注目している頂点に隣接している頂点を次の探索候補として優先度付きキューに追加
            current_min_dist.push({next_vertex_dist, next_vertex});
            min_results[next_vertex] = next_vertex_dist;
            // 経路を保存
            route_map[next_vertex] = current_vertex;
        }
    }

    // 終点から始点までの経路を復元
    auto current_vertex = N - 1;
    stack<ll> route;
    route.push(N);
    while (current_vertex != 0) {
        route.push(route_map[current_vertex] + 1);
        current_vertex = route_map[current_vertex];
    }
    while (!route.empty()) {
        cout << route.top() << " ";
        route.pop();
    }
    cout << endl;
}

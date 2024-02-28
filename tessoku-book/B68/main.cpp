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

/**
 * @brief i番目の頂点からと繋がる辺の情報
 *
 * @note ダイクストラ法などで辺の情報を管理するのに使う
 */
struct FlowEdge {
    // (残余グラフ上の)i番目の頂点とこの辺で結ばれている頂点の番号
    ll to;

    // (残余グラフ上の)辺の残容量
    ll cap;

    // 「i番目の頂点とこの辺で結ばれている頂点」からi番目の頂点へ向かう辺(toの逆辺)
    // がnon_directed_graph[non_directed_graph[u][i].to]の何番目に存在するか
    ll rev;
};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), M(0);
    cin >> N >> M;
    // グラフを表現する隣接リスト
    // 駅数 + 始点 & 終点の合計N+2頂点
    vector<vector<FlowEdge>> non_directed_graph(N + 2);
    // 各駅を特急駅にした時の損益を格納する
    vector<ll> costs(N, 0);
    REP(i, N) cin >> costs[i];

    // 特急駅同士の依存関係を得る
    // vector<vector<ll>> dependencies(N);
    vector<pair<ll, ll>> dependencies(M);
    REP(i, M) {
        ll A(0), B(0);
        cin >> A >> B;
        A--;
        B--;
        dump(A, B, M);
        dependencies[i] = {A, B};
        // dependencies[A].push_back(B);
        // dependencies[B].push_back(A);
    }

    dump(costs, dependencies);

    auto create_edge = [&](const ll weight, const ll vertex,
                           const ll other_vertex) {
        // FlowEdge.revを求めるために、現時点の頂点に隣接している辺の数を保持しておく
        auto current_edge1_size = non_directed_graph[vertex].size();
        auto current_edge2_size = non_directed_graph[other_vertex].size();
        // vertex→other_vertexの方向の辺
        FlowEdge flow_edge_1 = {other_vertex, weight, current_edge2_size};
        non_directed_graph[vertex].push_back(flow_edge_1);
        // other_vertex→vertexの方向の辺
        FlowEdge flow_edge_2 = {vertex, 0, current_edge1_size};
        non_directed_graph[other_vertex].push_back(flow_edge_2);
    };

    // グラフを作る
    // TODO: 始点→インデックスN、終点→インデックスN+1でいける？
    ll offset(0);
    REP(i, N) {
        // 1.始点→i番目の駅の辺を張る
        auto cost_from_start_to_station = costs[i] > 0 ? costs[i] : 0;
        create_edge(cost_from_start_to_station, N, i);
        offset += cost_from_start_to_station;
        // 2.i番目の駅→終点の辺を張る
        auto cost_from_station_to_end = costs[i] > 0 ? 0 : (costs[i] * -1);
        dump(cost_from_station_to_end);
        create_edge(cost_from_station_to_end, i, N + 1);
    }

    // 3.i番目の駅が他のj番目の駅と依存関係がある場合は辺を張る
    for (const auto& [vertex, other_vertex] : dependencies) {
        create_edge(INF, vertex, other_vertex);
    }

    // 最大フロー問題

    // 「各経路について、流せるだけ流してみる」という方針だと、
    // 経路の処理する順番によって局所最適解に陥る可能性がある。
    // この問題を解決するために「残余グラフ」という概念を導入する
    // ・残余グラフ: 残り容量を順方向の辺とし、使用済みの容量を逆方向の辺として追加する
    // この概念を追加する事で、過去に流したフローを戻せ(逆方向の辺を移動し、流量をその分減らす事に相当)、
    // 局所最適解に陥らずに真の最適解を求める事ができる様になる

    // 最大フロー問題はFord-Fulkerson法というアルゴリズムで解く事ができる
    // そのアルゴリズムの詳細は以下の通り。
    // 1. 残余グラフ上の容量0の辺を通らない、頂点1からNまでのパスを見つける
    // 2. パスにおける容量の最小値をFとするとき、パス上に流量Fだけ流す(このFがそのパスで流せるMAXの流量に相当する)
    //    ここで逆方向の辺は、元々のグラフの流量をFだけ減らす事に注意する
    // 3. 手順1のパスがなくなるまで、手順1、2を繰り返す

    // Note
    //      ・順方向の辺と逆方向の辺を区別せずに処理する事で、過去に流したフローも含めて流量の増減が実現でき、
    //       結果的に全体での最適解を求める事ができる
    //      ・最小カット問題というタイプの問題

    // DFSのためのラムダ関数(最大フロー問題用)
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, vector<vector<FlowEdge>>& Graph, const ll vertex,
                   const ll goal_vertex, vector<bool>& seen, ll flow) -> ll {
        seen[vertex] = true;
        if (vertex == goal_vertex) {
            return flow;
        }
        // 現在注目している頂点と隣接している頂点に対して再帰
        for (auto& next_vertex : Graph[vertex]) {
            // 残りの容量が0 or 既に訪問済みの頂点の場合はスキップ
            if (next_vertex.cap < 1 || seen[next_vertex.to]) continue;
            auto route_flow = self(self, Graph, next_vertex.to, goal_vertex,
                                   seen, std::min(flow, next_vertex.cap));
            // まだ流せる場合は、流量の更新を行う
            if (route_flow < 1) continue;
            // 流せる残量は減り、流量はその分増える
            next_vertex.cap -= route_flow;
            Graph[next_vertex.to][next_vertex.rev].cap += route_flow;
            return route_flow;
        }
        // 全ての辺を探索したが、パスが見つからなかった場合
        return 0;
    };

    ll sum_flow(0);
    while (true) {
        // その頂点が既に訪問済みかを表現する
        vector<bool> seen(N, false);
        ll max_flow = 1e12;
        // ※始点をインデックス:N、終点をN+1に格納している点に注意
        auto flow = dfs(dfs, non_directed_graph, N, N + 1, seen, max_flow);
        // 流せる流量が0になった=もう流せる経路がない
        if (!flow) break;
        sum_flow += flow;
    }
    dump(offset, sum_flow);
    cout << offset - sum_flow << endl;
}
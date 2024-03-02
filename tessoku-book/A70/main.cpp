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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), M(0);
    cin >> N >> M;
    // vector<ll> A(N, 0);
    vector<vector<ll>> Query(M, vector<ll>(3, 0));
    string init_state;
    REP(i, N) {
        char tmp;
        cin >> tmp;
        dump(tmp);
        init_state += tmp;
    }
    dump(init_state);
    REP(i, M) {
        ll tmp1(0), tmp2(0), tmp3(0);
        cin >> tmp1 >> tmp2 >> tmp3;
        Query[i] = {tmp1, tmp2, tmp3};
    }
    dump(Query);

    // 1. N=[3,10]なのでMAX=2^10なので、ライトの点灯パターンを全列挙し、それを頂点番号とする
    // 2. 各頂点からM通りの操作で遷移できる頂点に辺を張る
    // 3. 始点を設問で与えられた初期状態とし、終点を全てのbitが立っている状態、頂点: 2^Nとする
    // 4. BFSで探索する、終点に辿りつけないケースがある事に注意する

    // 有向グラフを表現する隣接リスト
    auto graph_size(1);
    REP(i, N) graph_size <<= 1;
    dump(graph_size);
    vector<vector<int>> directed_graph(graph_size);

    // 各頂点からM通りの操作で遷移できる頂点に辺を張る
    constexpr auto bits = 24;
    REP(i, graph_size) {
        for (const auto& elem : Query) {
            std::bitset<bits> binary_vertex(i);
            // 指定bitを反転させる
            // ※bitsetは右から0番目であることに注意
            binary_vertex.flip(N - elem[0]);
            binary_vertex.flip(N - elem[1]);
            binary_vertex.flip(N - elem[2]);
            directed_graph[i].push_back(binary_vertex.to_ullong());
        }
    }

    // 始点の10進数表現の値を求める
    std::bitset<bits> binary_start_vertex(init_state);
    const auto start_vertex = binary_start_vertex.to_ullong();

    // BFSのためのデータ構造
    // 初期状態からの最短経路を記録するリスト
    vector<ll> shortest_distance(graph_size, -1);
    // 現在見つかっていて未訪問の頂点のリスト
    queue<ll> next_verticies;
    // 初期状態
    // 今回は入力で与えられたライトの点灯状態からスタート
    shortest_distance[start_vertex] = 0;
    next_verticies.push(start_vertex);

    // BFS(幅優先探索)、計算量O(N+M)→各頂点と各辺がそれぞれ1回ずつ処理されるため
    while (!next_verticies.empty()) {
        auto current_vertex = next_verticies.front();
        next_verticies.pop();

        for (const auto& next_vertex : directed_graph[current_vertex]) {
            if (shortest_distance[next_vertex] != -1) continue;
            // 最短距離を更新
            // 辺の重み=1なので、隣接している頂点までは、現在注目している頂点+1の経路でアクセスできる
            shortest_distance[next_vertex] =
                shortest_distance[current_vertex] + 1;
            next_verticies.push(next_vertex);
        }
    }
    // ※始点から終点に到達できないケースはshortest_distanceの初期値が出力される
    cout << shortest_distance[graph_size - 1] << endl;
}

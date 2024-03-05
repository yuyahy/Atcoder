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
struct Edge {
    // i番目の頂点とこの辺で結ばれている頂点の番号
    ll to;

    // 辺のコスト
    ll cost;

    // 木の本数
    ll tree_cnt;
};

// 自前: tupleのソートを使った解法
// ※ただしソートの大小の部分が自分の意図と反しているが、ACになったので偶々動作しているだけかも
void solve1(const int N, const vector<vector<Edge>>& stage_graph) {
    auto custom_comp = [](const tuple<ll, ll, ll>& left,
                          const tuple<ll, ll, ll>& right) {
        // まず最初の要素で昇順に比較
        if (get<0>(left) != get<0>(right)) return get<0>(left) > get<0>(right);

        // 最初の要素が同じ場合は2番目の要素で降順に比較
        if (get<1>(left) != get<1>(right)) return get<1>(left) > get<1>(right);

        // 2番目の要素も同じ場合は3番目の要素で昇順に比較
        return get<2>(left) < get<2>(right);
    };

    // 最短距離を保持するリスト
    vector<pair<ll, ll>> min_results(N, {INF, 0});
    // 既に最短距離が確定済みの頂点かの情報を保持するリスト
    vector<bool> is_checked(N, false);
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>,
                   decltype(custom_comp)>
        current_min_dist(custom_comp);

    current_min_dist.push({0, 0, 0});
    min_results[0] = {0, 0};

    // ダイクストラ法でステージNへの最短秒数を求める
    while (!current_min_dist.empty()) {
        // 探索候補の中で頂点1から距離が最短の物を取り出す
        auto [min_dist, trees, current_vertex] = current_min_dist.top();
        current_min_dist.pop();
        if (is_checked[current_vertex]) continue;
        // 現在注目している頂点の最短距離を確定する
        is_checked[current_vertex] = true;
        dump(min_dist, current_vertex);
        // 隣接している頂点をチェック
        for (const auto& next_vertex : stage_graph[current_vertex]) {
            auto next_vertex_dist =
                min_results[current_vertex].first + next_vertex.cost;
            auto next_vertex_tree =
                min_results[current_vertex].second + next_vertex.tree_cnt;
            // 最短距離を更新できない場合は以降の処理は不要
            if (min_results[next_vertex.to].first < next_vertex_dist) continue;
            // 現在注目している頂点に隣接している頂点を次の探索候補として優先度付きキューに追加
            current_min_dist.push(
                {next_vertex_dist, next_vertex_tree, next_vertex.to});
            min_results[next_vertex.to] = {next_vertex_dist, next_vertex_tree};
        }
    }
    cout << min_results[N - 1].first << " " << min_results[N - 1].second
         << endl;
}

// 解説の解法
// 木がある道路を優先させるために、距離が同じ場合は、木がある道路を誤差程度短くすることで、
// ダイクストラ法で先に処理する様にする
// ただし誤差分引いた値の総和が1を上回ってしまうと、本来は最も合計距離が短いルートではなく、
// 木の数が最も多いが実際は合計距離が最も短くないルートが最短経路として検出されてしまうため、
// 誤差は充分小さくする必要がある。目安: 誤差σ * M < 1.0 程度(これは全ての道路は高々一回しか通らないため)
void solve2(const int N, vector<vector<Edge>>& stage_graph) {
    constexpr double per = 0.000001;
    constexpr int add = 1;
    constexpr int multi = add / per;

    for (auto& current_vertex : stage_graph) {
        for (auto& next_vertex : current_vertex) {
            next_vertex.cost *= multi;
            if (next_vertex.tree_cnt) {
                // 木がある場合は誤差の範囲で短くする
                next_vertex.cost -= add;
            }
        }
    }

    // 最短距離を保持するリスト
    vector<ll> min_results(N, INF);
    // 既に最短距離が確定済みの頂点かの情報を保持するリスト
    vector<bool> is_checked(N, false);
    // <現在注目している頂点の頂点1からの最小距離, 頂点の番号>の優先度付きキュー
    // 以下の様にstd::greaterでもOK
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
        current_min_dist;
    current_min_dist.push({0, 0});
    min_results[0] = 0;
    // ダイクストラ法でステージNへの最短秒数を求める
    while (!current_min_dist.empty()) {
        // 探索候補の中で頂点1から距離が最短の物を取り出す
        auto [min_dist, current_vertex] = current_min_dist.top();
        current_min_dist.pop();
        if (is_checked[current_vertex]) continue;
        // 現在注目している頂点の最短距離を確定する
        is_checked[current_vertex] = true;
        dump(min_dist, current_vertex);
        // 隣接している頂点をチェック
        for (const auto& next_vertex : stage_graph[current_vertex]) {
            auto next_vertex_dist =
                min_results[current_vertex] + next_vertex.cost;
            // 最短距離を更新できない場合は以降の処理は不要
            if (min_results[next_vertex.to] < next_vertex_dist) continue;
            // 現在注目している頂点に隣接している頂点を次の探索候補として優先度付きキューに追加
            current_min_dist.push({next_vertex_dist, next_vertex.to});
            min_results[next_vertex.to] = next_vertex_dist;
        }
    }
    // 木の数 = {誤差分を引いた上での木の総和を小数点以下を切り上げた物 / multi} * multi - 誤差分を引いた上での木の総和
    cout << std::ceil(min_results[N - 1] * per) << " "
         << std::ceil(min_results[N - 1] * per) * multi - min_results[N - 1]
         << endl;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), M(0);
    cin >> N >> M;

    vector<vector<Edge>> stage_graph(N);
    ll A(0), B(0), C(0), D(0);
    REP(i, M) {
        cin >> A >> B >> C >> D;
        dump(i, A, B, C, D);
        A--;
        B--;
        // 交差点 Ai → Bi
        Edge edge_i_1 = {B, C, D};
        stage_graph[A].push_back(edge_i_1);
        // 交差点 Bi → Ai
        Edge edge_X_i = {A, C, D};
        stage_graph[B].push_back(edge_X_i);
    }
    dump(stage_graph);
    // solve1(N, stage_graph);
    solve2(N, stage_graph);
}

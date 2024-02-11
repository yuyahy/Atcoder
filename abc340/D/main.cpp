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

    // ステージiにたどりつくまでの最小の秒数を管理するDP
    // vector<ll> DP(N, 0);
    //

    ll N(0);
    cin >> N;

    // 無向グラフを表現する隣接リスト
    vector<vector<ll>> stage_graph(N);
    // 頂点をつなぐ辺の重み
    map<pair<ll, ll>, ll> edge_weight;
    ll A(0), B(0), X(0);
    REP(i, N - 1) {
        cin >> A >> B >> X;
        dump(i, A, B, X);
        // A--;
        // B--;
        X--;
        // ステージ i → i+1
        stage_graph[i].push_back(i + 1);
        // stage_graph[i + 1].push_back(i);
        edge_weight[{i, i + 1}] = A;
        // edge_weight[{i + 1, i}] = A;
        // ステージ i → Xi
        stage_graph[i].push_back(X);
        // stage_graph[X].push_back(i);
        edge_weight[{i, X}] = B;
        // edge_weight[{X, i}] = B;
    }
    dump(stage_graph);
    dump(edge_weight);

    // 優先度付きキューで昇順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<ll, ll>& left, const pair<ll, ll>& right) {
        if (left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first > right.first;
        }
    };

    // 最短距離を保持するリスト
    vector<ll> min_results(N, INF);
    // 既に最短距離が確定済みの頂点かの情報を保持するリスト
    vector<bool> is_checked(N, false);
    // <現在注目している頂点の頂点1からの最小距離, 頂点の番号>の優先度付きキュー
    // priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(custom_comp)>
    //     current_min_dist(custom_comp);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
        current_min_dist;
    current_min_dist.push({0, 0});
    min_results[0] = 0;

    // TODO: 一部のケースでWAになっているので、公式解説を聞いてから再チャレンジ

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
            auto next_vertex_dist = min_results[current_vertex] +
                                    edge_weight[{current_vertex, next_vertex}];
            // 最短距離を更新できない場合は以降の処理は不要
            if (min_results[next_vertex] < next_vertex_dist) continue;
            // 現在注目している頂点に隣接している頂点を次の探索候補として優先度付きキューに追加
            current_min_dist.push({next_vertex_dist, next_vertex});
            min_results[next_vertex] = next_vertex_dist;
        }
    }
    dump(is_checked);
    dump(min_results);
    cout << min_results[N - 1] << endl;
}

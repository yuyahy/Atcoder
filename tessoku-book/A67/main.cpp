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

    ll N(0), M(0);
    cin >> N >> M;

    // 最小全域木
    // 優先度つきキューとUnionFindを利用する
    // Note: 優先度つきキューで実装したが、途中で一回だけソートすれば十分なので、
    //       単純に配列に全部要素をつめてから一回ソートする方がシンプル

    // 優先度付きキューで昇順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<ll, ll>& left, const pair<ll, ll>& right) {
        if (left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first > right.first;
        }
    };
    // <辺の長さ, M番目の辺>
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(custom_comp)>
        edges(custom_comp);
    // 経路を管理するUnionFind
    dsu union_find(N);

    ll A(0), B(0), C(0);
    // i番目の辺 = <辺1, 辺2>を表現する配列
    vector<pair<ll, ll>> graph(M, {0, 0});

    REP(i, M) {
        cin >> A >> B >> C;
        A--;
        B--;
        edges.push({C, i});
        graph[i] = {A, B};
    }

    // 以下の条件を満たす辺を選択し、最小全域木を求める
    // 1. 優先度付きキューから距離が最も小さい辺を取得
    // 2. UnionFindよりその辺の経路が確定していないかチェックする
    // 3. 確定していなかった場合は、UnionFindに登録 & 辺の総和に加算する

    ll result(0);
    dump(graph);
    while (!edges.empty()) {
        auto [shortest_edge, edge_index] = edges.top();
        edges.pop();
        auto [vertex, other_vertex] = graph[edge_index];
        dump(edge_index, vertex, other_vertex);
        if (union_find.same(vertex, other_vertex)) continue;

        union_find.merge(vertex, other_vertex);
        result += shortest_edge;
    }
    cout << result << endl;
}

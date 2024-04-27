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

#define YESNO(T)               \
    if (T) {                   \
        cout << "YES" << endl; \
    } else {                   \
        cout << "NO" << endl;  \
    }
#define yesno(T)               \
    if (T) {                   \
        cout << "yes" << endl; \
    } else {                   \
        cout << "no" << endl;  \
    }
#define YesNo(T)               \
    if (T) {                   \
        cout << "Yes" << endl; \
    } else {                   \
        cout << "No" << endl;  \
    }

#define COUT(x) cout << (x) << endl
#define SCOUT(x) cout << (x) << " "
#define ENDL cout << endl

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

// アルファベット(小文字大文字)
const string lower_alphabet = "abcdefghijklmnopqrstuvwxyz";
const string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 数字
const string integers = "0123456789";

struct Edge {
    // i番目の頂点とこの辺で結ばれている頂点の番号
    ll to;

    // 辺のコスト
    ll cost;
};

// 自前実装(DFS)
void solve1() {
    ll N(0), M(0);
    cin >> N >> M;

    // 無向グラフを表現する隣接リスト
    vector<vector<Edge>> non_directed_graph(N);
    REP(i, M) {
        ll v1(0), v2(0);
        cin >> v1 >> v2;
        v1--;
        v2--;
        non_directed_graph[v2].push_back(Edge{v1, 1});
        non_directed_graph[v1].push_back(Edge{v2, 1});
    }

    // その頂点が既に訪問済みかを表現する
    vector<bool> seen(N, false);
    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, const vector<vector<Edge>>& Graph,
                   const int vertex, const int prev_vertex,
                   vector<bool>& seen) -> void {
        // 訪問済みの頂点として記録
        seen[vertex] = true;
        // 辺の数は1 or 2のいずれか
        if (Graph[vertex].size() != 1 && Graph[vertex].size() != 2) {
            COUT("No");
            exit(0);
        }
        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            // 閉路が存在する場合はパスグラフではない
            // Note: 1回前の再帰で通った頂点は現在注目している頂点と接続しているのでノーカン
            if (next_vertex.to != prev_vertex && seen[next_vertex.to]) {
                COUT("No");
                exit(0);
            }
            if (seen[next_vertex.to]) continue;
            self(self, Graph, next_vertex.to, vertex, seen);
        }
    };

    dfs(dfs, non_directed_graph, 0, -1, seen);

    // 全頂点を通ったか確認する
    ll seen_cnt(0);
    for (const auto& elem : seen)
        if (elem) seen_cnt++;

    bool res = seen_cnt == N;
    YesNo(res);
}

// 自前実装2(Union-Find)
void solve2() {
    ll N(0), M(0);
    cin >> N >> M;
    // 辺の本数をチェック
    if (M != N - 1) {
        COUT("No");
        return;
    }

    // 無向グラフを表現する隣接リスト
    vector<vector<Edge>> non_directed_graph(N);
    // 閉路が存在しないかチェック
    dsu uf(N);
    REP(i, M) {
        ll v1(0), v2(0);
        cin >> v1 >> v2;
        v1--;
        v2--;
        non_directed_graph[v2].push_back(Edge{v1, 1});
        non_directed_graph[v1].push_back(Edge{v2, 1});
        // merge前にv1、v2が同じ親を持っている = v1、v2に辺を張ると閉路になる
        if (uf.same(v1, v2)) {
            COUT("No");
            return;
        }
        uf.merge(v1, v2);
    }

    // 次数をチェック
    for (const auto& vertex : non_directed_graph) {
        if (vertex.size() != 1 && vertex.size() != 2) {
            COUT("No");
            return;
        }
    }

    COUT("Yes");
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - パスグラフ = 一直線の様な形のグラフ
    // - 両端以外は次数=2, 両端は次数=1
    // - 全ての頂点を通る必要あり
    // - どれか一個の頂点から探索を始める
    //      - 頂点を探索済みとして保存
    //      - 辺の数をカウントし、1 or 2でなければfalse
    //      - 既に探索済みの頂点がでてきたら閉路があるのでfalse
    //      - 全ての辺を通らなかったらfalse

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - パスグラフの特徴に着目し、必要十分条件を正しく考察する事ができた
    // - 改善点
    //      - DFS実装でバグらせた。辺の本数のチェックはDFSの前にやっておき、可能な限り再帰で書く実装を減らすべきかもしれない
    //      - 無効グラフの場合、閉路検出はUnionFindで実装すると簡潔に書ける

    //solve1();
    solve2();
}

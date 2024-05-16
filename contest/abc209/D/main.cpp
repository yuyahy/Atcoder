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
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(m) - 1; (i) >= (int)(n); --(i))

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 街は全てつながっている
    // - 双方向に移動可能
    // - 道路(辺)は同じ長さ
    // - 2人とも街からスタート
    // - 奇数回の移動で2人ともRoad, 偶数回でTown
    // - ci→diへ移動する頂点の個数が奇数ならRoad
    // - ci→diへ移動する頂点の個数が偶数ならTown
    // - N個の街とN-1本の道路、どの街からも任意の街へ行けるので、サイクルはない一本道
    //      - よく見たらサンプル1の時点で一本道ではなかった。。。

    // - BFSだとO(N+M) = 10^5位かかる
    // - 事前にある街からある街へ移動する際の頂点の個数がわかれば良い？

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      -
    // - 改善点
    //      - 最初必ず一本道のグラフになると勘違いし、方針を誤った。少なくともサンプルが自分の想定した条件になっているかは
    //        手を動かす前に確認すべし
    //      - 木(グラフが連結であり、サイクルを持たない)場合は最短経路は一意に決まる

    ll N(0), Q(0);
    cin >> N >> Q;
    // 無向グラフ
    vector<vector<ll>> non_directed_graph(N);
    REP(i, N - 1) {
        ll a(0), b(0);
        cin >> a >> b;
        a--;
        b--;
        non_directed_graph[a].push_back(b);
        non_directed_graph[b].push_back(a);
    }
    dump(non_directed_graph);

    // BFSのためのデータ構造
    // 頂点1からの最短経路を記録するリスト
    vector<ll> shortest_distance(N, -1);
    // 現在見つかっていて未訪問の頂点のリスト
    queue<ll> next_verticies;
    // 初期化
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

    REP(i, Q) {
        ll c(0), d(0);
        cin >> c >> d;
        c--;
        d--;
        auto result = abs(shortest_distance[c] - shortest_distance[d]) % 2 == 0
                          ? "Town"
                          : "Road";
        COUT(result);
    }
}

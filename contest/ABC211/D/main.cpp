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
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
    // - BFSで最短経路に行くための移動回数を求める
    // - DFSで経路を全列挙し上記で求めた移動回数の経路の数をカウントする
    //  - ※mint

    ll N(0), M(0);
    cin >> N >> M;
    vector<vector<ll>> non_directed_graph(N);
    REP(i, M) {
        ll A(0), B(0);
        cin >> A >> B;
        A--;
        B--;
        non_directed_graph[A].push_back(B);
        non_directed_graph[B].push_back(A);
    }

    mint result;

    // BFSで最短経路を求める
    // BFSのためのデータ構造
    // 頂点1からの最短経路を記録するリスト
    vector<ll> shortest_distance(N, -1);
    vector<mint> shortest_count(N, 0);
    // 現在見つかっていて未訪問の頂点のリスト
    queue<ll> next_verticies;

    shortest_count[0] = 1;

    // TODO: 理解

    shortest_distance[0] = 0;
    next_verticies.push(0);
    while (!next_verticies.empty()) {
        auto current_vertex = next_verticies.front();
        next_verticies.pop();

        for (const auto& next_vertex : non_directed_graph[current_vertex]) {
            // if (shortest_distance[next_vertex] != -1) continue;
            // 最短距離を更新
            // 辺の重み=1なので、隣接している頂点までは、現在注目している頂点+1の経路でアクセスできる
            // shortest_distance[next_vertex] =
            //     shortest_distance[current_vertex] + 1;
            // if (shortest_distance[next_vertex] <
            //     shortest_distance[current_vertex] + 1) {
            if (shortest_distance[next_vertex] == -1) {
                shortest_distance[next_vertex] =
                    shortest_distance[current_vertex] + 1;
                shortest_count[next_vertex] = shortest_count[current_vertex];

                next_verticies.push(next_vertex);

            } else if (shortest_distance[next_vertex] ==
                       shortest_distance[current_vertex] + 1) {
                shortest_count[next_vertex] += shortest_count[current_vertex];
                // shortest_count[next_vertex] %= MOD;
            }
            dump(shortest_count[next_vertex].val());
        }
    }
    dump(shortest_distance[N - 1]);

    // DFSのためのデータ構造
    // その頂点が既に訪問済みかを表現する
    vector<bool> seen(N, false);
    // auto dfs = [&](auto self, const vector<vector<ll>>& graph,
    //                vector<bool> seen, ll current_vertex,
    //                ll route_count) -> void {
    //     seen[current_vertex] = true;
    //     //
    //     if (current_vertex == N - 1) {
    //         if (route_count == shortest_distance[N - 1]) result++;
    //         return;
    //     }
    //     for (const auto next_vertex : graph[current_vertex]) {
    //         if (seen[next_vertex] || route_count + 1 > shortest_distance[N - 1])
    //             continue;
    //         self(self, graph, seen, next_vertex, route_count + 1);
    //     }
    // };
    // dfs(dfs, non_directed_graph, seen, 0, 0);

    //  - ※mint
    //COUT(result.val());
    COUT(shortest_count[N - 1].val());
}

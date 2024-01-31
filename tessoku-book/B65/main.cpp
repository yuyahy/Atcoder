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

    int N(0), T(0);
    cin >> N >> T;
    int A(0), B(0);
    // 有向グラフを表現する隣接リスト
    vector<vector<int>> non_directed_graph(N);
    REP(i, N - 1) {
        cin >> A >> B;
        non_directed_graph[A - 1].push_back(B - 1);
        non_directed_graph[B - 1].push_back(A - 1);
    }

    // その頂点が既に訪問済みかを表現する
    vector<bool> seen(N, false);
    vector<int> ranks(N, 0);
    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, const vector<vector<int>>& Graph,
                   const int vertex, vector<bool>& seen,
                   vector<int>& ranks) -> int {
        // 訪問済みの頂点として記録
        seen[vertex] = true;
        // 現在注目している頂点と隣接している頂点に対して再帰
        int max(0), staff_cnt(0);
        for (const auto next_vertex : Graph[vertex]) {
            if (seen[next_vertex]) continue;
            max = std::max(max, self(self, Graph, next_vertex, seen, ranks));
            staff_cnt++;
        }
        // 部下がいない場合は階級:0, それ以外の場合は直属の部下の最大値に+1した値が自身の階級になる
        ranks[vertex] = staff_cnt == 0 ? 0 : max + 1;
        return ranks[vertex];
    };
    dfs(dfs, non_directed_graph, T - 1, seen, ranks);

    dump(ranks);

    for (const auto& elem : ranks) cout << elem << " ";
    cout << endl;
}

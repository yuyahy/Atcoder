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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), M(0);
    cin >> N >> M;

    vector<ll> A(M, 0), B(M, 0);
    REP(i, M) cin >> A[i];
    REP(i, M) cin >> B[i];

    // 無向グラフを表現する隣接リスト
    vector<vector<Edge>> non_directed_graph(N);
    REP(i, M) {
        A[i]--;
        B[i]--;

        Edge edge1 = {A[i], 1};
        non_directed_graph[B[i]].push_back(edge1);
        Edge edge2 = {B[i], 1};
        non_directed_graph[A[i]].push_back(edge2);
    }

    // 考察メモ
    // - 計算量的にビット全探索はできない
    // - 0 or 1かというより、矛盾しない様に２つのグループに分けれられるか？という問題な気がする
    // - Union-Findで2つのグループを作れるか？
    // - 「ペアの内少なくとも片方が既にどちらかのグループに分けれられている」ケースは簡単
    // - しかし、「ペアの両方がまだどちらのグループにも分けれられていない」ケースは？
    // - 「自分と一緒のグループにしてはいけないインデックス」を調べるのは最悪O(N)程度かかる

    // Note:
    // - 結果: 解説AC
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: 不十分
    //      - 二部グラフは知っていたが中身を理解していなかった
    // - 考察: 不十分
    //      - 2つのグループに分けれられるか？というのはいい線行っていた
    //      - 「2部グラフか？」と思って調べたが撤退してしまった(多分理解不足で避けたかったのだと思う)
    // - 実装: 不十分
    //      - 解説ACする際にバグ取りでハマった。。。

    // 二部グラフかを判定する問題に帰着できる

    // 頂点の訪問情報
    // 1. 未訪問: -1
    // 2. 訪問済みかつ1にする: 1
    // 3. 訪問済みかつ0にする: 0

    vector<int> seen(N, -1);
    auto result(true);
    dump(seen);

    auto dfs = [&](auto self, const vector<vector<Edge>>& Graph,
                   const int vertex, const int next_value,
                   vector<int>& seen) -> void {
        // 訪問済みの頂点として隣接する既に値が決まった頂点と被らない様に値を割り振る
        seen[vertex] = next_value;
        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            dump(vertex, next_vertex.to);
            // 隣接頂点が未訪問であれば自身と違う値を割り振る
            if (seen[next_vertex.to] == -1) {
                self(self, Graph, next_vertex.to, (next_value == 1 ? 0 : 1),
                     seen);
            } else if (seen[vertex] == seen[next_vertex.to]) {
                // 隣接頂点が訪問済みかつ、自身と同じ値が割り振られていた場合は2部グラフにはできない
                result = false;
                break;
            }
        }
    };

    // Note: 全ての頂点が辺で繋がっているとは限らないので、各頂点に対してDFSする必要あり
    REP(i, N) {
        if (seen[i] == -1) dfs(dfs, non_directed_graph, i, 0, seen);
    }
    YesNo(result);
}

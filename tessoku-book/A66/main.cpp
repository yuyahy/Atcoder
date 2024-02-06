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

// Note: 以下のUnionFindには経路圧縮の処理は含まれていない
class UnionFind {
   private:
    /**
     * @brief ある頂点の親ノードを返す
     *
     * @param vertex 対象の頂点
     * @return ll vertexの親ノードの番号
     */
    ll retrieve_parent(const ll vertex) { return m_vertex_parents[vertex]; }
    /**
     * @brief ある頂点が属するグループの根を返す関数
     *
     * @param vertex 対象の頂点
     * @return ll vertexが属するグループの根
     */
    ll retrieve_root(const ll vertex) {
        auto current_vertex = vertex;
        while (retrieve_parent(current_vertex) != -1) {
            current_vertex = retrieve_parent(current_vertex);
        }
        // 経路圧縮するならここで調べた頂点の親を根に変更する
        return current_vertex;
    }

   public:
    /**
     * @brief Construct a new Union Find object
     *
     * @param N 頂点の個数
     */
    UnionFind(const ll N) : m_vertex_parents(N), m_group_sizes(N) {
        // 初期状態では全ての頂点が別々のグループに属するため、
        // ・各頂点の親ノードなし
        // ・各グループのサイズは1
        for (auto& parent : m_vertex_parents) parent = -1;
        for (auto& size : m_group_sizes) size = 1;
    }
    /**
     * @brief 2頂点が属するグループを同じグループに統合する
     *
     * @param vertex 対象の頂点1
     * @param other_vertex 対象の頂点2
     */
    void unite(const ll vertex, const ll other_vertex) {
        auto root = retrieve_root(vertex);
        auto other_root = retrieve_root(other_vertex);
        // 既に同じグループに属していないかチェックする
        if (root == other_root) return;

        auto size = m_group_sizes[root];
        auto other_size = m_group_sizes[other_root];
        // ※大きい方のグループの根に対して小さい方のグループの根を付ける様にすると
        // 頂点の根を求める処理の計算量がlog(N)になる
        if (size > other_size) {
            m_vertex_parents[other_root] = root;
            m_group_sizes[root] = size + other_size;
        } else {
            m_vertex_parents[root] = other_root;
            m_group_sizes[other_root] = size + other_size;
        }
    }
    /**
     * @brief 2頂点が同じグループに属しているかを判定する関数
     *
     * @param vertex 対象の頂点1
     * @param other_vertex 対象の頂点2
     * @return true 2頂点が同じグループに属している
     * @return false 2頂点が同じグループに属していない
     */
    bool is_same_group(const ll vertex, const ll other_vertex) {
        return (retrieve_root(vertex) == retrieve_root(other_vertex));
    }

   private:
    // i番目の頂点の親ノード
    vector<ll> m_vertex_parents;
    // 各グループに属する頂点の数
    vector<ll> m_group_sizes;
};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), Q(0);
    cin >> N >> Q;

    bool b_use_atcoder_lib(true);
    dsu uf(N);
    UnionFind union_find(N);
    ll u(0), v(0), query(0);
    REP(i, Q) {
        cin >> query >> u >> v;
        u--;
        v--;
        if (query == 1) {
            // 頂点u, vの間に辺を張る
            if (b_use_atcoder_lib) uf.merge(u, v);
            else union_find.unite(u, v);
        } else {
            // 頂点u, vが同じ連結成分に属しているかを判定する
            if (b_use_atcoder_lib)
                cout << (uf.same(u, v) ? "Yes" : "No") << endl;
            else
                cout << (union_find.is_same_group(u, v) ? "Yes" : "No") << endl;
        }
    }
}

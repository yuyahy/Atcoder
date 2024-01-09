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

class SegmentTree {
   public:
    SegmentTree(const ll N) {
        // m_sizeはN以上の最小の2^kとする
        int size(1);
        while (N > size) {
            size = size << 1;
            // dump(size);
        }
        m_size = size;
        dump(size);
        // 末端ノード(葉)×2を要素数とすれば充分
        m_cells.assign(m_size * 2, 0);
    }

    void update(const ll update_idx, const ll value) {
        // update_idxとその親ノードを更新していく
        auto pos = update_idx + m_size - 1;
        dump(update_idx);

        dump(m_size);

        dump(pos);
        m_cells[pos] = value;
        while (pos >= 2) {
            pos /= 2;
            // 子ノード×2から和を求める
            m_cells[pos] = m_cells[pos * 2] + m_cells[pos * 2 + 1];
        }
        dump(m_cells);
    }

    /**
     * @brief
     *
     * @param current_cell      現在見ているセルのインデックス
     * @param right             求めたい区間[left, right)
     * @param left              求めたい区間[left, right)
     * @param cell_right        今見ているセルの半開区間[cell_left, cell_right)
     * @param cell_left         今見ているセルの半開区間[cell_left, cell_right)
     * @return ll
     * @note 半開区間であることに注意
     */
    ll calc_extreme_value(const ll current_cell, const ll left, const ll right,
                          const ll cell_left, const ll cell_right) {
        // current_cellの一部 or 全体が半開区間[left, right)の外にある場合
        dump(left);
        dump(right);
        dump(cell_left);
        dump(cell_right);

        // 範囲外の場合は結果に影響しないような値を返す必要がある
        // e.g. 最大値を求める場合は、限りなく小さい値、総和を求める場合は0など
        if (right <= cell_left || cell_right <= left) return 0;

        // current_cellの全体が半開区間[left, right)の中にある場合
        if (left <= cell_left && cell_right <= right) {
            return m_cells[current_cell];
        }
        // 再帰しながら総和を求める
        auto mid = (cell_left + cell_right) / 2;
        auto left_result =
            calc_extreme_value(current_cell * 2, left, right, cell_left, mid);
        auto right_result = calc_extreme_value(current_cell * 2 + 1, left,
                                               right, mid, cell_right);
        return (left_result + right_result);
    }

    ll size() { return m_size; }

   private:
    // 末端ノード(葉の数)
    ll m_size;
    // セグメント木を一次元配列で表現した物
    vector<ll> m_cells;
};

ll op(ll x, ll y) { return x + y; }
ll e() { return 0; }

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0), Q(0);
    cin >> N >> Q;
    vector<int> A(N, 0);

    dump(N);
    dump(Q);

    segtree<ll, op, e> seg(N);  // 長さ N 、要素すべて e で初期化

    // Note:
    // クエリ2だけであれば、累積和で解答できるが、今回はクエリ1で特定のインデックスの値が
    // 更新されるため、その都度そのインデックス以降の累積和を計算し直す必要があり、TLEになる。
    // したがって、今回はセグメント木を用いる。セグメント木の特徴は以下。
    //
    // ・各区間の最大値 or 最小値(これは設問による)を二分木で保持する(詳細は後述)
    // ・特定の区間の最大値や最小値をlog(N)で求められる
    // ・特定のインデックスの更新と、それに伴う最大値 or 最小値の更新がlog(N)で行える

    SegmentTree segtree = SegmentTree(N);

    ll query(0);
    // Note: 以下は自分で実装したSegmentTreeクラスを用いた解法と、ACLのsegtreeを用いた解法の両方を記載している
    auto b_use_acl(false);
    REP(i, Q) {
        cin >> query;
        dump(query);
        if (query == 1) {
            ll pos(-1), value(-1);
            cin >> pos >> value;
            if (b_use_acl) {
                seg.set(pos - 1, value);
            } else {
                segtree.update(pos, value);
            }
        } else {
            ll left(-1), right(-1);
            cin >> left >> right;
            // dump(left);
            // dump(right);
            ll result(0);
            if (b_use_acl) {
                result = seg.prod(left - 1, right - 1);
            } else {
                result = segtree.calc_extreme_value(1, left, right, 1,
                                                    segtree.size() + 1);
            }
            cout << result << endl;
        }
    }
}

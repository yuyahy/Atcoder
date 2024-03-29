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

int op(int x, int y) { return x + y; }
int e() { return 0; }

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    // Note:
    // 愚直に各iに対してj(i<j)かを全探索すると、O(N^2)になり間に合わない
    // そこで以下の様な配列を導入する事を考える。
    // ・num_encounter[i] = 現時点で整数iが何回出現したか
    // これにより、整数A[i]に対してA[i] < A[j]となる様なjの個数は以下の計算で求められる
    // ・整数A[i]に対してA[i] < A[j]となる様なjの個数 = num_encounter[A[i]+1] + num_encounter[A[i]+2]+...num_encounter[N]
    // ただし、上記の方針をそのまま実装すると、この和を求める計算でO(N)かかり、全体としてO(N^2)のままなので、
    // 単純な配列ではなく、セグメント木を使用すると、和を求める計算がO(logN)になり、全体としてO(N*logN)で求められる

    // Note:
    // 本問題は、先頭から順番に、「自分以降のインデックスの要素で、自分より小さい物がいくつあるか？」という
    // のがまず思いつくが、これは言い換えると、「自分より前のインデックスの要素で、自分より大きい物がいくつあるか？」という
    // 風に捉えることもでき、以下の実装はそのアイデアで実装されている。
    // そして、最初の考え方の場合は、配列の後から逆に探索していき、自分より小さい物をカウントする事で解答できるはず。
    //
    // また、ある整数の出現回数を、整数=インデックス、出現回数=配列の該当するインデックスの値と考えるのはよく使う方法なので
    // 引き出しとして持っておくこと。

    int N(0);
    cin >> N;
    vector<int> A(N, 0);
    REP(i, N) cin >> A[i];
    dump(A);

    segtree<int, op, e> num_encounter(N);  // 長さ N 、要素すべて e で初期化

    SegmentTree segtree = SegmentTree(N);

    bool b_reverse(true);
    if (b_reverse) reverse(begin(A), end(A));

    // ※ llにしないとWAがでる
    ll sum(0);
    for (const auto& current_A : A) {
        auto product_begin_idx(-1), product_end_idx(-1);
        if (b_reverse) {
            // 今見ているインデックスより後の要素に対して、自分より小さい物をカウントする考え方
            product_begin_idx = 0;
            product_end_idx = current_A;
        } else {
            //  今見ているインデックスより前の要素に対して、自分より大きい物をカウントする考え方
            product_begin_idx = current_A;
            product_end_idx = N;
        }

        // i < jとなる様なjの個数を求める
        sum += num_encounter.prod(product_begin_idx, product_end_idx);

        // 出現をカウントする(今回は[1, N]の順列で同じ整数が複数回出現する事はないので、決め打ちで1で更新しても問題ない想定)
        auto cnt = num_encounter.get(current_A - 1);
        num_encounter.set(current_A - 1, cnt + 1);
    }

    cout << sum << endl;
}

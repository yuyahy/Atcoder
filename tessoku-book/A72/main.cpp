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

    ll H(0), W(0), K(0);
    cin >> H >> W >> K;
    vector<vector<char>> grids(H, vector<char>(W));
    dump(H, W, K);
    REP(i, H) {
        string str;
        cin >> str;
        REP(j, W) grids[i][j] = str[j];
    }
    dump(grids);

    // Note: 以下の方針でやったが、嘘解法だった。
    // ・嘘解法
    // K回、「その時点で最も白色のマスが多い行 or 列を全て黒色に塗る」操作をした時の計算量は
    // K * (最も白色のマスが多い行 or 列を特定する処理の計算量) * (黒色に塗る処理の計算量)
    // O(K) * O(HW) * O(H or W)
    // 最悪のケースで考えると、
    // O(K * H * W * W) = O(10 * 10 * 100 * 100) = O(10^6)
    // よって実際にシミュレーションを行う
    //
    // e.g. 以下のケースだと、1行目→2行目→3行目を塗るとsum=15にできるが、
    //      以下のロジックだと1列目→1行目→2行目を塗ることになり、sum=14になってしまう
    // H= 4 W=4 K=3
    // [ '.', '.', '.', '#' ],
    // [ '.', '.', '#', '.' ],
    // [ '.', '#', '.', '.' ],
    // [ '.', '#', '#', '#' ]

    auto retrieve_max_while_rows = [&](const vector<vector<char>>& grids)
        -> std::priority_queue<pair<ll, ll>> {
        // 列を調べる
        // <白マスの数、対応する列の番号>の優先度つきキュー
        std::priority_queue<pair<ll, ll>> row_priority;
        REP(i, W) {
            ll white_cnt(0);
            REP(j, H) if (grids[j][i] == '.') white_cnt++;
            row_priority.push({white_cnt, i});
        }
        return row_priority;
    };

    auto paint_column_or_row = [&](vector<vector<char>>& grids,
                                   const bool is_column, ll paint_idx) {
        if (is_column) REP(i, W) grids[paint_idx][i] = '#';
        else REP(i, H) grids[i][paint_idx] = '#';
    };

    // Note: 本設問では以下に着目する
    // 1. Hmax=10なので行の選び方は高々2^10=1024通りなので全列挙できる
    // 2. 行の選び方を決めると、最適な列の選び方も決められる: 白マスの多い列から操作回数が残っている限り埋める
    // 特に大きなヒントは1.で、問題の制約よりHは全列挙できるがWは全列挙できない事が分かる
    // つまり、いくつかのパラメータがあり、愚直な全探索はできないケースだとしても、以下の様な特徴があると全列挙が可能。
    // 1. どちらか一方のパラメータだけであれば全探索できる
    // 2. 片方のパラメータの値が決まると、もう一方のパラメータの値の最適解や選び方が決定される
    // 2変数の全探索で、片方を固定してもう一方をO(1) or O(logN)で求めるケースに似ているかも

    // 行の選び方を全列挙する
    // 制約より10bitあれば充分
    constexpr auto bits = 10;
    ll max_cnt(-1);
    for (int bit = 0; bit < (1 << H); ++bit) {
        auto tmp_grids = grids;
        std::bitset<bits> binary_selection(bit);
        // 操作回数がK回を超えている物は不可能
        ll bit_cnt = binary_selection.count();
        if (bit_cnt > K) continue;
        // 選択した行を塗る
        REP(i, binary_selection.size()) {
            if (binary_selection[i]) paint_column_or_row(tmp_grids, true, i);
        }
        // 選択した行に対して最善の列の塗り方: 白マスが多い物から順に塗る
        // 残っている白マスが多い列番号を格納した優先度付きキュー
        auto priority_rows = retrieve_max_while_rows(tmp_grids);
        REP(i, K - bit_cnt) {
            auto [tmp, row_idx] = priority_rows.top();
            priority_rows.pop();
            paint_column_or_row(tmp_grids, false, row_idx);
        }
        // 最終的な黒マスの個数をカウント
        ll cnt_black(0);
        REP(i, H) REP(j, W) if (tmp_grids[i][j] == '#') cnt_black++;
        max_cnt = std::max(max_cnt, cnt_black);
    }
    cout << max_cnt << endl;
}

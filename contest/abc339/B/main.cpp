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

const int dir[4] = {1, 1, 1, 1};

void calc_next_direction(int& x, int& y, int& current_direction,
                         const bool b_clockwise = true) {
    if (b_clockwise) {
        // 時計回りに90度
        current_direction++;
    } else {
        // 反時計回りに90度
        current_direction += 3;
    }
    current_direction %= 4;
    y += dy_4[current_direction];
    x += dx_4[current_direction];
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int H(0), W(0), N(0);
    cin >> H >> W >> N;
    vector<vector<char>> grids(H, vector<char>(W));
    REP(i, H) REP(j, W) grids[i][j] = '.';
    dump(grids);

    int move_cnt(0);
    int x(0), y(0);
    int current_direction(0);
    while (move_cnt != N) {
        string next;
        bool b_clockwise = (grids[y][x] == '.');
        if (b_clockwise) next += '#';
        else next += '.';
        grids[y][x] = next[0];
        calc_next_direction(x, y, current_direction, b_clockwise);
        // Note: 以下のコメントアウトは本番提出コード。
        //       現在のコードは次の方向を決める処理を関数化 & 反時計回りの処理を簡潔化している

        // if (grids[y][x] == '.') {
        //     // 時計回りに90度
        //     current_direction++;
        //     next += '#';
        // } else {
        //     // 反時計回りに90度
        //     // Note: 反時計回りについて、本番は以下の様に減算する方式にしたが、負の場合の扱いが面倒。
        //     //       +=3して余りを取ると場合分けが不要になり、より簡潔なコードになる

        //     // current_direction--;
        //     // if (current_direction < 0) current_direction = 3;
        //     current_direction += 3;
        //     next += '.';
        // }
        // current_direction %= 4;
        // grids[y][x] = next[0];
        // y += dy_4[current_direction];
        // x += dx_4[current_direction];

        // トーラスなので負 or グリッド外の場合は反対側に戻る
        if (x < 0) x = W - 1;
        else if (x > W - 1) x = 0;
        if (y < 0) y = H - 1;
        else if (y > H - 1) y = 0;

        dump(current_direction);
        dump(y);
        dump(x);

        move_cnt++;
    }
    dump(grids);

    REP(i, H) {
        REP(j, W) { cout << grids[i][j]; }
        cout << endl;
    }
}

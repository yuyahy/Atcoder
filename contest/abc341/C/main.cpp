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

    ll H(0), W(0), N(0);
    cin >> H >> W >> N;

    vector<vector<char>> grids(H, vector<char>(W));
    string direction;
    cin >> direction;
    REP(i, H) {
        string row;
        cin >> row;
        REP(j, W) grids[i][j] = row[j];
    }
    dump(grids);
    dump(direction);

    set<pair<int, int>> position;
    REP(i, H) {
        REP(j, W) {
            // 海は無視
            if (grids[i][j] == '#') continue;
            // 順番に移動できるかを確認する
            auto current_X(j), current_Y(i);
            bool b_rearch(true);
            REP(k, N) {
                if (grids[current_Y][current_X] == '#') {
                    b_rearch = false;
                    break;
                }
                int dir(-1);
                if (direction[k] == 'L') {
                    // 左に一マス移動
                    dir = 3;
                } else if (direction[k] == 'R') {
                    // 右に一マス移動
                    dir = 1;
                } else if (direction[k] == 'U') {
                    // 上に一マス移動
                    dir = 0;
                } else {
                    // 下
                    dir = 2;
                }
                current_X += dx_4[dir];
                current_Y += dy_4[dir];
            }
            if (b_rearch && grids[current_Y][current_X] != '#')
                position.insert({current_Y, current_X});
        }
    }
    dump(position);
    cout << position.size() << endl;
}

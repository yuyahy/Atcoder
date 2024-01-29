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

// 4近傍
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int R(0), C(0);
    cin >> R >> C;
    int start_X(0), start_Y(0), goal_X(0), goal_Y(0);
    cin >> start_Y >> start_X;
    cin >> goal_Y >> goal_X;

    // 座標を0始まりにしておく
    start_X--;
    start_Y--;
    goal_X--;
    goal_Y--;

    vector<string> grids(R);
    REP(i, R) cin >> grids[i];

    dump(grids);

    // BFSで各頂点のスタート地点からの最短経路を出力する

    // BFSのためのデータ構造
    // 頂点1からの最短経路を記録するリスト
    vector<vector<int>> shortest_distance(R, vector<int>(C, -1));
    // 現在見つかっていて未訪問の頂点のリスト
    queue<pair<int, int>> next_verticies;

    shortest_distance[start_Y][start_X] = 0;
    next_verticies.push({start_Y, start_X});

    while (!next_verticies.empty()) {
        auto [current_Y, current_X] = next_verticies.front();
        next_verticies.pop();

        // 現在注目している頂点の4近傍をチェック
        REP(i, 4) {
            int new_Y = current_Y + dy_4[i];
            int new_X = current_X + dx_4[i];
            // グリッドの中に収まっているかチェック
            if (new_Y != std::clamp(new_Y, 0, R) ||
                new_X != std::clamp(new_X, 0, C)) {
                continue;
            }
            // 壁 or チェック済みでないかチェック
            if (grids[new_Y].at(new_X) == '#' ||
                shortest_distance[new_Y][new_X] != -1)
                continue;
            // 最短距離を更新
            shortest_distance[new_Y][new_X] =
                shortest_distance[current_Y][current_X] + 1;

            next_verticies.push({new_Y, new_X});
        }
    }

    cout << shortest_distance[goal_Y][goal_X] << endl;
}
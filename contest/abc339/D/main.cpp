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

    ll N(0);
    cin >> N;

    vector<vector<char>> grids(N, vector<char>(N));
    vector<pair<ll, ll>> starts;
    REP(i, N) {
        string tmp;
        cin >> tmp;
        REP(j, N) {
            grids[i][j] = tmp[j];
            if (tmp[j] == 'P') starts.push_back({i, j});
        }
    }
    dump(grids);
    dump(starts);

    // 探索する座標
    struct point {
        ll x;
        ll y;
    };
    // BFSのための2人の次の探索位置を管理するキュー
    queue<pair<point, point>> next_position;
    point p1({starts[0].second, starts[0].first}),
        p2({starts[1].second, starts[1].first});
    next_position.push({p1, p2});

    // 2人の初期位置(X1, Y1, X2, Y2)からある座標(i1, j1, i2, j2)に移動するための最短経路を管理する配列
    // Note:
    // この考え方が盲点だった。
    // 2人がそれぞれ初期位置から移動できる座標を列挙し、その中で、
    // 2人が集まれる座標の内、初期位置から最短で行ける所を探せば良い、という言い換えが必要だった。
    vector<vector<vector<vector<ll>>>> shortest_distance(
        N, vector(N, vector(N, vector(N, INF))));
    shortest_distance[starts[0].second][starts[0].first][starts[1].second]
                     [starts[1].first] = 0;

    // BFSで2人の初期位置(X1, Y1, X2, Y2)からある座標(i, j, i, j)で集まるための最短経路を全列挙する
    // Note: 本番では全探索が必要→DFSの方針にしてしまったが、最短経路を求める問題なのでBFSがベター。
    //       →BFSであれば集まる座標は必ず最短経路で求められるため、座標ごとに最短かのチェックは不要
    while (!next_position.empty()) {
        auto current_pos1 = next_position.front().first;
        auto current_pos2 = next_position.front().second;
        auto& [current_X, current_Y] = current_pos1;
        auto& [current_X2, current_Y2] = current_pos2;
        next_position.pop();

        // 4方向の移動を全探索
        REP(i, 4) {
            ll new_Y = current_Y + dy_4[i];
            ll new_X = current_X + dx_4[i];
            ll new_Y2 = current_Y2 + dy_4[i];
            ll new_X2 = current_X2 + dx_4[i];
            // グリッドの中に収まっているかチェック
            if (new_Y != std::clamp(new_Y, ll(0), N - 1) ||
                new_X != std::clamp(new_X, ll(0), N - 1)) {
                new_Y = current_Y;
                new_X = current_X;
            }
            if (new_Y2 != std::clamp(new_Y2, ll(0), N - 1) ||
                new_X2 != std::clamp(new_X2, ll(0), N - 1)) {
                new_Y2 = current_Y2;
                new_X2 = current_X2;
            }
            // 行き先が障害物でないかチェック
            if (grids[new_Y][new_X] == '#') {
                new_Y = current_Y;
                new_X = current_X;
            }
            if (grids[new_Y2][new_X2] == '#') {
                new_Y2 = current_Y2;
                new_X2 = current_X2;
            }

            // BFSなので必ず最短経路が求められているはずなので、INF以外の値が既に記録されていた場合はスキップするだけで良い
            if (shortest_distance[new_X][new_Y][new_X2][new_Y2] != INF)
                continue;
            // 次の座標に進むための操作回数は、現在の座標に到達するまでに必要な操作回数+1
            shortest_distance[new_X][new_Y][new_X2][new_Y2] =
                shortest_distance[current_X][current_Y][current_X2]
                                 [current_Y2] +
                1;
            point new_p1({new_X, new_Y}), new_p2({new_X2, new_Y2});
            next_position.push({new_p1, new_p2});
        }
    }

    dump(shortest_distance);
    ll ans = INF;
    // BFSで初期位置から各座標に集まるための最短経路が全列挙されているはずなので、
    // その中で以下の2つの条件を共に満たすものが答え。
    // ・2人が集まれる座標である、すなわち(X1, Y1) = (X2, Y2)を満たす
    // ・初期位置から移動に必要な回数が最小である
    REP(i, N) REP(j, N) ans = min(ans, shortest_distance[i][j][i][j]);
    cout << (ans == INF ? -1 : ans) << endl;
}

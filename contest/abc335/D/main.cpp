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

// 解法1: 本番後に自分で実装したコード
//　3×3をベースとし、Nがそれより大きい場合は、既にあるグリッドの各要素を加算し、
// 新たな外周となる要素を追加していく方針
void solve1(vector<vector<int>>& grids, int N) {
    // ベースの3×3を作る
    grids.assign(3, vector<int>(3, 0));

    grids[0] = {1, 2, 3};
    grids[1] = {8, -100000000, 4};
    grids[2] = {7, 6, 5};

    dump(grids);

    if (N == 3) {
        // やることなし
    } else {
        for (int i = 5; i <= N; i += 2) {
            // 外周の要素の個数
            int out = 4 * i - 4;

            // 既にある要素を更新
            for (auto& vec : grids) {
                for (auto& elem : vec) {
                    elem += out;
                }
            }

            // １番上の行を追加→[1, N]の配列になる
            {
                vector<int> begin;
                REP(j, i) begin.push_back(j + 1);
                grids.insert(grids.begin(), begin);
            }

            // １番下の行を追加→[3i-2, 3i-3,...]の配列になる(左下、(0, N-1)からスタート)
            {
                vector<int> end;
                auto head = 3 * i - 2;
                REP(j, i) {
                    end.push_back(head);
                    head--;
                }
                grids.insert(grids.end(), end);
            }
            // 左側の縦のi-2個を更新→((0, 1)から下方向にi-2個処理する)
            {
                auto head = out;
                REP3(j, 1, i - 2 + 1) {
                    grids[j].insert(grids[j].begin(), head);
                    head--;
                }
            }

            // 右側の縦のi-2個を更新する→((1, N)から下方向にi-2個処理する)
            {
                auto head = grids[0].at(grids[0].size() - 1) + 1;
                REP3(j, 1, i - 2 + 1) {
                    grids[j].insert(grids[j].end(), head);
                    head++;
                }
            }
        }
    }
    dump(grids);
}

// 解法2: 解説にあった以下の方針の実装
//       右上の(0,0)から左方向に更新していき、次の要素が端 or 既に更新した要素だった場合は、
//       進行方向を90度回転させる
void solve2(vector<vector<int>>& grids, const int N) {
    // まだ訪れていないマスは-1とする
    grids.assign(N, vector<int>(N, -1));

    // 移動方向(時計回り)
    // ・0 : 右
    // ・1 : 下
    // ・2 : 左
    // ・3 : 上
    int move_direction(0);
    // 入力座標がグリッドの内側かの判定
    auto is_inside = [&](const int N, const int x, const int y) {
        return (x == std::clamp(x, 0, N - 1)) && (y == std::clamp(y, 0, N - 1));
    };

    int x(0), y(0), last(1);
    grids[x][y] = last;
    while (true) {
        // 次の要素が有効でない(e.g. グリッドの範囲外、既に訪問済み)可能性もあるので、
        // 座標の更新前のチェックが必要
        int next_x(x), next_y(y);
        if (move_direction % 4 == 0)
            next_y++;
        else if (move_direction % 4 == 1)
            next_x++;
        else if (move_direction % 4 == 2)
            next_y--;
        else
            next_x--;

        // 次の要素がグリッドの外 or 訪問済みだったら方向転換
        if (!is_inside(N, next_x, next_y) || grids[next_x][next_y] > 0) {
            move_direction++;
            continue;
        }
        // 外周から螺旋状に探索するので、中央に来たら終わり
        if (next_x == N / 2 && next_y == N / 2) break;

        x = next_x, y = next_y;
        last++;
        grids[x][y] = last;
    }
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0);
    cin >> N;

    vector<vector<int>> grids;
    // solve1(grids, N);
    solve2(grids, N);

    // Note: 以下は各行の最後に不要な空白が入り、ローカルのテストは失敗するが、
    //       Atcoder上で直接提出すればACになる
    REP(i, N) {
        REP(j, N) {
            if (grids[i][j] > 0) {
                cout << grids[i][j] << " ";
            } else {
                cout << "T"
                     << " ";
            }
        }
        cout << endl;
    }
}

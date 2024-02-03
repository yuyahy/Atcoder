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

// 2近傍(左上原点)
// Y = ( ↓, そのまま)
// X = (そのまま, →)
const int dy_2[2] = {1, 0};
const int dx_2[2] = {0, 1};
// 4近傍
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// DFSで経路を全探索する方針
void solve_dfs(const auto& H, const auto& W, const auto& grids) {
    // DFSで右上の原点から左下のゴールまでの移動経路を全列挙する
    auto dfs = [&](auto self, const vector<vector<ll>>& grids, set<ll> path,
                   const ll x, const ll y, vector<ll> debug) -> int {
        debug.push_back(grids[y][x]);
        path.insert(grids[y][x]);
        // ゴールの点にたどりついたケース
        // std::setを用いて、これまでの経路で通ってきたマスに書かれていた数字が全てユニークかチェック
        if (y == H - 1 && x == W - 1) {
            dump(path);
            dump(debug);
            return path.size() == (H + W - 1) ? 1 : 0;
        }
        // 現在注目している頂点の右 or 下方向に移動した際の経路を求めて再帰
        int result(0);
        REP(i, 2) {
            ll new_Y = y + dy_2[i];
            ll new_X = x + dx_2[i];
            // グリッドの中に収まっているかチェック
            if (new_Y != std::clamp(new_Y, ll(0), H - 1) ||
                new_X != std::clamp(new_X, ll(0), W - 1)) {
                continue;
            }
            result += self(self, grids, path, new_X, new_Y, debug);
        }
        return result;
    };
    ll cnt(0);
    std::set<ll> path;
    vector<ll> debug;
    path.insert(grids[0][0]);
    int move_cnt(0);
    cnt = dfs(dfs, grids, path, 0, 0, debug);
    cout << cnt << endl;
}

// 順列を用いて経路を全探索する方針
void solve_permutation(const ll H, const ll W,
                       const vector<vector<ll>>& grids) {
    // ゴールにたどりつくためには、右:W-1回、下: H-1回移動する必要がある
    // 右方向の移動:0, 下方向の移動:1 と表現する
    vector<int> P(H + W - 2, 1);
    // std::next_permutation()を使うために、昇順になる様に0, 1をセットしておく
    REP(i, W - 1) P[i] = 0;
    ll cnt(0);
    do {
        dump(P);
        std::set<ll> path;
        path.insert(grids[0][0]);
        ll x(0), y(0);
        for (const auto& elem : P) {
            if (elem == 0) x++;
            else y++;
            path.insert(grids[y][x]);
        }
        if (path.size() == H + W - 1) cnt++;
    } while (std::next_permutation(P.begin(), P.end()));
    cout << cnt << endl;
}

// bit全探索を用いて経路を全探索する方針
void solve_bit_search(const ll H, const ll W, const vector<vector<ll>>& grids) {
    auto n = H + W - 2;
    // 設問より最大18bitあれば良い
    constexpr auto bits = 24;
    ll cnt(0);
    // ゴールにたどりつくためには、右:W-1回、下: H-1回移動する必要がある
    // 右方向の移動:0, 下方向の移動:1 と表現する
    for (int bit = 0; bit < (1 << n); ++bit) {
        std::bitset<bits> binary_path(bit);
        dump(binary_path);
        dump(binary_path.count());
        // 立っているbitの数から、今回求めたい経路を表現しているかを判別する
        if (binary_path.count() != H - 1) continue;
        // 経路のマス目が全て異なる数字かをチェックする
        ll x(0), y(0);
        std::set<ll> path;
        path.insert(grids[y][x]);
        // 下位ビットから移動経路を復元する
        REP(i, n) {
            if (binary_path.test(i)) y++;
            else x++;
            path.insert(grids[y][x]);
        }
        if (path.size() == H + W - 1) cnt++;
    }
    cout << cnt << endl;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll H(0), W(0);
    cin >> H >> W;

    vector<vector<ll>> grids(H, vector<ll>(W, 0));
    REP(i, H) REP(j, W) cin >> grids[i][j];
    dump(grids);
    // solve_dfs(H, W, grids);
    // solve_permutation(H, W, grids);
    solve_bit_search(H, W, grids);
}

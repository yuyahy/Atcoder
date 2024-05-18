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
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(m) - 1; (i) >= (int)(n); --(i))

#define YESNO(T)               \
    if (T) {                   \
        cout << "YES" << endl; \
    } else {                   \
        cout << "NO" << endl;  \
    }
#define yesno(T)               \
    if (T) {                   \
        cout << "yes" << endl; \
    } else {                   \
        cout << "no" << endl;  \
    }
#define YesNo(T)               \
    if (T) {                   \
        cout << "Yes" << endl; \
    } else {                   \
        cout << "No" << endl;  \
    }

#define COUT(x) cout << (x) << endl
#define SCOUT(x) cout << (x) << " "
#define ENDL cout << endl

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

// アルファベット(小文字大文字)
const string lower_alphabet = "abcdefghijklmnopqrstuvwxyz";
const string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 数字
const string integers = "0123456789";

// 解法:1 DFS
ll solve1(const ll H, const ll W, const vector<vll>& A) {
    // その頂点が既に訪問済みかを表現する
    vector seen(H, vector<bool>(W, false));
    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    // //  ※隣接行列で処理するとO(N^2)になる点に注意
    ll result(0);
    auto dfs = [&](auto self, const ll i, const ll j, vector<vector<bool>> seen,
                   set<ll> route, ll move_cnt) -> void {
        // 訪問済みの頂点として記録
        seen[i][j] = true;
        dump(i, j);

        route.insert(A[i][j]);

        const ll dy_2[2] = {0, 1};
        const ll dx_2[2] = {1, 0};

        // bit全探索の方が楽かも

        if (move_cnt == H + W - 2 && route.size() == H + W - 1) result++;
        if (move_cnt == H + W - 2) return;

        REP(k, 2) {
            ll new_i = i + dy_2[k];
            ll new_j = j + dx_2[k];
            if (new_i != std::clamp(new_i, ll(0), H - 1) ||
                new_j != std::clamp(new_j, ll(0), W - 1)) {
                continue;
            }
            if (seen[new_i][new_j]) continue;
            self(self, new_i, new_j, seen, route, move_cnt + 1);
        }
    };
    set<ll> route;
    // 移動経路を全探索して、条件に合致する物を数える
    dfs(dfs, 0, 0, seen, route, 0);

    return result;
}

// 解法:2 bit全探索
ll solve2(const ll H, const ll W, const vector<vll>& A) {
    ll result(0);
    ll N = H + W - 2;
    dump(N);
    // {0, 1, ..., n-1} の部分集合の全探索
    for (int bit = 0; bit < (1 << N); ++bit) {
        /* bit で表される集合の処理を書く */
        ll move_X(0), move_Y(0);
        set<ll> route;
        route.insert(A[0][0]);

        // ビットが立っていたら右に移動、そうでなければ下に移動するとみなす
        for (int i = 0; i < N; ++i) {
            if (bit & (1 << i)) {  // i が bit に入るかどうか
                move_X++;
            } else {
                move_Y++;
            }
            if (move_Y != std::clamp(move_Y, ll(0), H - 1) ||
                move_X != std::clamp(move_X, ll(0), W - 1)) {
                continue;
            }
            route.insert(A[move_Y][move_X]);
        }
        // 移動回数をループ時に求めているので、実際はmove_X or move_Yのどちらかだけ確認すれば十分
        if (move_Y != H - 1 or move_X != W - 1) continue;
        if (route.size() == H + W - 1) result++;
        dump(route);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 最大で上下9マスずつ移動→18C9 = 5 * 10^6
    // - 移動方法は全列挙可能なので、愚直にDFS?
    // - 右 or 下のbit全探索が可能(2^18)

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - どこかで類題を解いた事があったため方針は迷わなかった
    // - 改善点
    //      - 原因特定できずだが、サンプルケース:2でatestだとTLE, atest_subだとOKだった
    //          - おそらくコンパイルオプションによって実行速度が低下しているのだと思う
    //      - サンプルケースしかatestしないので、普段は気がつかないのかも(サンプルケースに計算量MAXがあるかどうか？)
    //          - 実は普段もテストケースの中ではatestでは通らず、atest_subでは通るケースがあるが、それがジャッジ側だとこちらからは気が付かないという話
    //      - 明らかに解法が合ってそうなので、サンプルでTLEになる場合はダメ元でatest_subで通るか試すのはありかも
    //      - 必要な移動回数=H+W-2だが、そこで通る整数の個数はH+W-1である(後者は最初の(1, 1)のマスも含むため)
    //          - 最初ここを勘違いしていた。。。簡単なケースで要チェック

    ll H(0), W(0);
    cin >> H >> W;

    vector A(H, vll(W, 0));
    for (auto& elem : A) {
        for (auto& elem2 : elem) {
            cin >> elem2;
        }
    }
    dump(A);

    //auto result = solve1(H, W, A);
    auto result = solve2(H, W, A);

    COUT(result);
}

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - Union Find, BFS, DFS(6近傍探索)して連結成分をカウントするのが簡単?
    // - N=[1,1000]なので2重ループ可能

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 連結成分を求めるだけであればUnion Findを使うのが簡単という事を既に知っていた(ABC351-Dの学び)
    // - 改善点
    //      - 特になし

    ll N(0);
    cin >> N;
    dsu uf(N);
    vector<pair<ll, ll>> grids(N, {0, 0});
    for (auto& elem : grids) cin >> elem.first >> elem.second;

    // 6近傍(左上原点)
    const int dy_6[6] = {-1, 0, -1, 1, 0, 1};
    const int dx_6[6] = {-1, -1, 0, 0, 1, 1};

    //{x,y}にとって、{x_other,y_other}が6近傍の点かを判定するラムダ式
    auto is_hex_neighbor = [&](const ll x, const ll y, const ll x_other,
                               const ll y_other) {
        REP(i, 6) {
            ll new_y = y + dy_6[i];
            ll new_x = x + dx_6[i];

            if (new_y == y_other and new_x == x_other) return true;
        }
        return false;
    };

    REP(i, N - 1) REP3(j, i + 1, N) {
        // 6近傍に該当する要素があればマージ
        if (is_hex_neighbor(grids[i].first, grids[i].second, grids[j].first,
                            grids[j].second))
            uf.merge(i, j);
    }

    COUT(uf.groups().size());
}

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
    // - 移動できるのは道路で繋がっている都市間のみ
    // - 0本以上の道路なので移動しなくても良い
    // - 有向グラフでDFS?
    //      - サイクルとか考えると複雑だが、制約が小さいので各頂点から探索してもO(N*(N+M)) = O(10^7)

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 各連携成分ごとに1回だけDFS/BFSするとサイクルがでてきて面倒
    //      - N, Mが小さいので各頂点からDFS/BFSやっても大丈夫だと気がつく事ができた
    // - 改善点
    //      - 制約を考慮してなるべくシンプルでバグらない方針を早く思い付ける様にしたい

    ll N(0), M(0);
    cin >> N >> M;

    // 有向グラフ
    vector<vector<ll>> directed_graph(N);
    REP(i, M) {
        ll A(0), B(0);
        cin >> A >> B;
        A--;
        B--;
        directed_graph[A].push_back(B);
    }

    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, const vector<vector<ll>>& Graph, const ll vertex,
                   vector<bool>& seen) -> ll {
        // 訪問済みの頂点として記録
        seen[vertex] = true;

        ll result(1);

        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            if (seen[next_vertex]) continue;
            result += self(self, Graph, next_vertex, seen);
        }
        return result;
    };

    ll cnt(0);
    REP(i, N) {
        // その頂点が既に訪問済みかを表現する
        vector<bool> seen(N, false);
        cnt += dfs(dfs, directed_graph, i, seen);
    }
    COUT(cnt);
}

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

#define ALL(a) (a).begin(), (a).end()

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 技Nを習得するために必要な[A_N1,A_N2,...ANKn]から逆にたどっていく？
    // - 技Aiを習得するための最短時間を重ねていく
    //      - ある技Aiを習得するための最短時間は？

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 最初DPでやってサンプルは通ったが、提出前にテストケースを作り、嘘解法であることを見抜けた
    //      - この問題のポイントは「技Nを習得するために習得しなければならない技を重複なくカウントできるか」という事だと思う
    //          - 技Nを習得するために必要な技同士が独立であれば、それらを足し合わせるだけだが、「技iを覚えるためにi+1を覚えなければならない」ケースもある
    // - 改善点
    //      - 問題の考察が甘く、25分考えて一晩寝かせてからACした。本番だったら時間が足りないかも

    ll N(0);
    cin >> N;

    vector<vll> A(N);
    vll T(N);

    // 有向グラフを表現する隣接リスト
    vector<vll> directed_graph(N);

    REP(i, N) {
        ll t(0), K(0);
        cin >> t >> K;
        T[i] = t;

        vll A_sub(K, 0);
        for (auto& elem : A_sub) {
            cin >> elem;
            elem--;
        }
        A[i] = A_sub;
        directed_graph[i] = A_sub;
    }
    dump(A);
    dump(directed_graph);

    // DP[i] 技iを覚えるための最短時間
    // 初期状態 DP[0] = T1;
    // 遷移 DP[i+1] = Ti+1 + sum(A_i1,A_i2,...A_in)の最小値

    // この解法だと技Nを覚えるために技1、2が必要だが、技2を覚えるためには技1が必要というケースに技1のケースがダブって加算されてしまう
    /**
    3
    3 0
    5 1 1
    7 2 1 2

    →15になってほしい
     */

    // 技iを習得すると言う事は実質技A_i1,A_i2,...A_inを習得している事になる。。。という性質を使うと良いかも

    // その頂点が既に訪問済みかを表現する
    vector<bool> seen(N, false);
    ll result(0);
    auto dfs = [&](auto self, const vector<vector<ll>>& Graph, const ll vertex,
                   vector<bool>& seen) -> ll {
        // 訪問済みの頂点として記録
        seen[vertex] = true;

        ll cost(T[vertex]);
        dump(cost);

        // 現在注目している頂点と隣接している頂点に対して再帰
        for (const auto next_vertex : Graph[vertex]) {
            if (seen[next_vertex]) continue;
            cost += self(self, Graph, next_vertex, seen);
        }
        return cost;
    };

    result = dfs(dfs, directed_graph, N - 1, seen);

    COUT(result);
}

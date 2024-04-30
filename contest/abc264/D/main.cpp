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

// 転倒数を用いた解法
void solve1(const string& S) {
    const string atcoder = "atcoder";

    //"atcoder"の各アルファベットに[0,1,2,3,4,5,6]を割り振る
    vll conv_number(atcoder.size(), 0);
    REP(i, atcoder.size()) REP(j, S.size()) {
        if (S[j] == atcoder[i]) conv_number[j] = i;
    }
    dump(conv_number);

    // 転倒数(自分より左にいるが、自分より大きい要素の個数)をカウント
    ll result(0);
    REP(i, conv_number.size() - 1)
    REP3(j, i + 1, conv_number.size())
    if (conv_number[i] > conv_number[j]) result++;

    COUT(result);
}

// BFSを用いた解法
void solve2(const string& S) {
    // 入力文字列をグラフの始点とし、以下の様なグラフを考える
    // - 頂点: "atcoder"を並び替えて得られる文字列
    // - 辺: 一回の隣り合った文字同士を並び替える操作
    // すると、今回の設問はこの始点から頂点:"atcoder"までの最短距離に相当する

    // BFSのためのデータ構造
    // 頂点1からの最短経路を記録するリスト
    // vll shortest_distance(S.size(), -1);
    // 現在見つかっていて未訪問の頂点のリスト
    queue<string> next_verticies;
    // 文字列が探索済みかを管理するmap
    map<string, ll> shortest_distance;

    shortest_distance[S] = 0;
    next_verticies.push(S);

    while (!next_verticies.empty()) {
        auto current_vertex = next_verticies.front();
        next_verticies.pop();

        if (current_vertex == "atcoder") {
            COUT(shortest_distance[current_vertex]);
            return;
        }

        // 隣り合った文字列を入れ替える
        REP(i, current_vertex.size() - 1) {
            auto str = current_vertex;
            std::swap(str[i], str[i + 1]);
            if (!shortest_distance.count(str)) {
                shortest_distance[str] = shortest_distance[current_vertex] + 1;
                next_verticies.push(str);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 転倒数？

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 問題を見て直ぐに転倒数だと気がつく事ができた
    // - 改善点
    //      - 改善点というか別解法としてBFSもある

    string S;
    cin >> S;

    // solve1(S);
    solve2(S);
}

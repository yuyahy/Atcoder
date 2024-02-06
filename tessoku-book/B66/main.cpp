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

    int N(0), M(0);
    cin >> N >> M;

    dsu union_find(N);

    int A(0), B(0);
    vector<pair<int, int>> lines(M);
    REP(i, M) {
        cin >> A >> B;
        A--;
        B--;
        lines[i] = {A, B};
    }
    int Q(0), query(0), x(0), u(0), v(0);
    cin >> Q;
    // x番目の路線が運休か
    vector<bool> cancelled_lines(M, false);
    vector<vector<int>> queries(Q);
    dump(Q);
    REP(i, Q) {
        cin >> query;
        queries[i].push_back(query);
        if (query == 1) {
            // x本目の路線が運休
            cin >> x;
            x--;
            queries[i].push_back(x);
            cancelled_lines[x] = true;
        } else {
            // 駅uからvに行けるか
            cin >> u >> v;
            u--;
            v--;
            queries[i].push_back(u);
            queries[i].push_back(v);
        }
    }
    // 最後のクエリの処理後のUnionFindを作る
    REP(i, M) {
        if (cancelled_lines[i]) continue;
        union_find.merge(lines[i].first, lines[i].second);
    }
    // Note: 最後のクエリの状態から逆順にクエリを辿る事で、辺を削除する処理→辺を追加する処理と見なす事ができる
    //       →このクエリを先読みしておき、逆順に辿るテクニックは他の系統の問題でも使えそう
    vector<string> results;
    REP_R(i, Q) {
        if (queries[i][0] == 1) {
            // 辺を張る
            union_find.merge(lines[queries[i][1]].first,
                             lines[queries[i][1]].second);
        } else {
            // 回答を逆順に保持
            results.push_back(
                (union_find.same(queries[i][1], queries[i][2]) ? "Yes" : "No"));
        }
    }
    // 回答が逆順になっているので、出力は更に逆順にして本来の順序に戻す必要があるので注意
    REP_R(i, results.size()) cout << results[i] << endl;
}

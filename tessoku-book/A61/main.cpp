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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0), M(0);
    cin >> N >> M;
    // <頂点, その頂点と隣接している頂点の番号>
    map<int, vector<int>> graph;
    REP(i, M) {
        int vertex1(0), vertex2(0);
        cin >> vertex1 >> vertex2;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }
    dump(graph);

    REP(i, N) {
        auto elem = graph[i + 1];
        cout << i + 1 << ": {";
        sort(elem.begin(), elem.end());
        for (int j = 0; j < elem.size(); j++) {
            if (j == elem.size() - 1) {
                cout << elem.at(j) << "}";
            } else {
                cout << elem.at(j) << ", ";
            }
        }
        if (elem.empty()) cout << "}";
        cout << endl;
    }
}

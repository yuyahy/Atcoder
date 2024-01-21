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

    int N(0);
    cin >> N;

    // <X, Xの後の人>
    map<int, int> rows;

    int A(0), head(0);
    REP(i, N) {
        cin >> A;
        if (A == -1) {
            head = i + 1;
        } else {
            rows[A] = i + 1;
        }
    }
    dump(rows);

    int pre(0);
    REP(i, N) {
        if (i == 0) {
            cout << head << " ";
            pre = head;
        } else {
            cout << rows[pre] << " ";
            pre = rows[pre];
        }
    }
    cout << endl;
}

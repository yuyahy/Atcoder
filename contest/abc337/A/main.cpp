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

    int N(0), t_win(0), a_win(0);
    cin >> N;
    int X(0), Y(0);
    REP(i, N) {
        cin >> X >> Y;
        t_win += X;
        a_win += Y;
        // if (X > Y) {
        //     t_win++;
        // } else if (Y > X) {
        //     a_win++;
        // }
    }
    string result;
    if (t_win > a_win) {
        result = "Takahashi";
    } else if (a_win > t_win) {
        result = "Aoki";
    } else {
        result = "Draw";
    }
    cout << result << endl;
}

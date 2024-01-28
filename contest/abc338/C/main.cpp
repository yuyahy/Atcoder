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

    ll N(0);
    cin >> N;

    vector<ll> Q(N, 0), A(N, 0), B(N, 0);
    REP(i, N) cin >> Q[i];
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];

    dump(Q);
    dump(A);
    dump(B);

    auto Q_tmp = Q;
    auto A_tmp = A;
    auto B_tmp = B;

    // Note: 本番ではbit全探索か？と迷走したが、ABC330-C問題の類題(こちらの方が小数点の誤差を気にしなくて良いので簡単)
    //       2変数を特定の条件下で動かし、最大値 or 最小値を求める問題である(全探索の一種)
    //       Aの個数を1e6程度から初め、そうするとB用に残った食材の数がわかるので、それをBで調理できるかチェックする方針
    ll max = ll(1e6) + 100;
    ll result(0);
    REP(i, max) {
        Q = Q_tmp;
        A = A_tmp;
        B = B_tmp;
        bool b_cook = true;
        // Aで調理できる分を調理する
        REP(j, N) {
            if (Q[j] - i * A[j] < 0) {
                b_cook = false;
                break;
            }
            Q[j] -= i * A[j];
        }
        if (!b_cook) continue;

        // Bで残った食材を調理できるか
        ll cnt_B(max);
        REP(j, N) {
            if (!B[j]) continue;
            cnt_B = min(cnt_B, Q[j] / B[j]);
        }
        result = std::max(result, i + cnt_B);
    }
    cout << result << endl;
}

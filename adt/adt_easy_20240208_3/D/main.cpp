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

    int N(0);
    cin >> N;
    vector<int> A(N, 0);
    REP(i, N) cin >> A[i];

    dump(A);
    bool b_different_ans(true);
    if (b_different_ans) {
        // 別解法
        // 計算量: O(N)
        // 累積和で解く
        // 仮にマス4を超えても、コマを取り除かなかった場合の最終的な各コマの位置を求める
        // i番目のコマは合計A[i, N]分移動できるため、累積和を右から取ると各コマの移動量がわかる
        vector<int> accum_move(N + 1, 0);
        dump(N);
        REP3R(i, N, 0) {
            // for (int i = N - 1; i >= 0; i--) {
            dump(i);
            accum_move[i] = accum_move[i + 1] + A[i];
        }
        dump(accum_move);
        int cnt(0);
        for (const auto& pos : accum_move) {
            if (pos >= 4) cnt++;
        }
        cout << cnt << endl;
    } else {
        // 本番提出解法
        // 操作一回ごとに新しいコマをqueueに蓄え、その後queueに残っている要素を全て取り出し、
        // A[i]を加算した値を詰め直している
        // →Nが大きいとTLEになるかも
        queue<int> koma;
        // シミュレーション
        REP(i, N) {
            int cnt(0);
            koma.push(0);
            cnt = koma.size();
            // cnt++;
            while (cnt--) {
                int top = koma.front();
                top += A[i];
                koma.pop();
                koma.push(top);
            }
        }
        // 最終的な位置がマス4以降のコマをカウント
        int res(0);
        while (!koma.empty()) {
            int top = koma.front();
            dump(top);
            koma.pop();
            if (top > 3) res++;
        }
        cout << res << endl;
    }
}

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

    int H(0), W(0), K(0);
    cin >> H >> W >> K;
    vector<vector<string>> grids(H, vector<string>(W, ""));

    string str;
    REP(i, H) {
        cin >> str;
        REP(j, str.length()) grids[i][j] = str[j];
    }
    dump(grids);

    // Note: この問題は縦方向と横方向に依存関係がないので、全て行として処理すると簡単(列は転置して行として処理できる)
    // Note: K個の区間を1マスずつずらしてチェックしていき、操作回数の最小値を求める
    //       操作回数の最小値は、区間ごとの"."の個数と"x"の個数が高速に求められればOK(今回は累積和でやる)
    //
    // Memo: 本番時はスキップしたが、累積和を使うと時間内に全探索できること、列を行とみなす発送があれば、後は添字ミスに注意すれば簡単
    //       問題の言い換え能力が足りていない
    auto check_row = [&](const vector<vector<string>>& array) -> int {
        int result = int(1e12);

        REP(i, array.size()) {
            // これからチェックする行の"."と"x"の個数を累積和として求めておく
            int W_ = array[0].size();
            vector<int> dots(W_ + 1, 0), xs(W_ + 1, 0);
            for (int j = 0; j < W_; j++) {
                dots[j + 1] = dots[j];
                xs[j + 1] = xs[j];
                if (array[i][j] == ".") dots[j + 1]++;
                else if (array[i][j] == "x") xs[j + 1]++;
            }
            // 連続したK個の'o'に変更できるかチェック
            for (int j = 0; j <= W_ - K; j++) {
                auto dot_cnt = dots[j + K] - dots[j];
                auto xs_cnt = xs[j + K] - xs[j];
                // 'x'が1個以上含まれる場合は対象外
                if (xs_cnt > 0) continue;
                result = std::min(result, dot_cnt);
            }
        }
        return result;
    };

    // 横方向に探索
    auto result = check_row(grids);

    // 転置して縦方向も探索
    vector<vector<string>> transpose_grids(W, vector<string>(H, ""));
    REP(i, H) REP(j, W) transpose_grids[j][i] = grids[i][j];
    dump(transpose_grids);
    result = std::min(result, check_row(transpose_grids));

    if (result == int(1e12)) result = -1;
    cout << result << endl;
}

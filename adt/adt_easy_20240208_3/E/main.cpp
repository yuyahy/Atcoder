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

    int N(0), K(0);
    cin >> N >> K;
    vector<int> scores(N, 0);
    int tmp(0);
    REP(i, N) REP(j, 3) {
        cin >> tmp;
        scores[i] += tmp;
    }
    auto vec = scores;
    dump(scores);
    // 二分探索用に昇順ソート
    sort(scores.begin(), scores.end());
    dump(scores);

    REP(i, N) {
        // 4日目に自分以外の人が全員0点だったときに、K位以内に入れるかだけ考えれば良い
        // とりうる最大のスコア
        auto max_score = vec[i] + 300;
        // max_score以下の最大のインデックスが欲しいので、upper_bound()でmax_scoreを超えた最小のインデックスを求める
        auto position = upper_bound(scores.begin(), scores.end(),
                                    max_score);  // max_score を二分探索
        auto idx_lower = distance(scores.begin(), position);
        // max_score以下の最大のインデックス
        idx_lower--;
        dump(idx_lower);
        // 大きい方から数えて上位K番目以内に入っているか
        // ※size()は[1, N], インデックスは[0, N-1]なので注意
        if (abs(int(scores.size()) - idx_lower) <= K) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

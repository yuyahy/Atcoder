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

    ll N(0);
    cin >> N;
    auto custom_comp = [](const pair<ll, ll>& left, const pair<ll, ll>& right) {
        if (left.second == right.second) {
            return left.first > right.first;
        } else {
            return left.second > right.second;
        }
    };
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(custom_comp)>
        questions(custom_comp);

    vector<pair<ll, ll>> sorted_questions;
    REP(i, N) {
        ll T(0), D(0);
        cin >> T >> D;
        questions.push({T, D});
    }
    // 全問解けるかを各N問に対してやる感じ？

    // どうすれば与えられた問題が全て解ける？に答えられるか
    // →締切が早い順に並び替えて、全ての(Ti, Di)について
    // 経過時間 <= DiであればOK?

    // 与える[1,2,...N]問はどうやって選ぶか？
    // 各N問を解く解かないで列挙すると2^100になり間に合わない
    // 単調性(二分探索)や貪欲に選び方が決まれば全列挙の必要はない

    // 時間に着目してみる
    // ある時刻Diまでが締切の問題を全て解くことはできるのか？

    // 全問解けるか？を考えてみる
    // 全問解ける場合→締切が早い順に並び替えて、全ての(Ti, Di)について
    // 経過時間 <= DiであればOK?

    // ・解ける場合は問題数がそのまま答えになる
    // ・解けない場合は？どれか一個の問題を削除してみる
    //      どの問題を削除するか？

    // 開始: Tiが最小かつ、Ti <= Diの物を選ぶ
    while (!questions.empty()) {
        auto elem = questions.top();
        dump(elem);
        questions.pop();
        sorted_questions.push_back(elem);
    }
    dump(sorted_questions);

    // 全問解けるか？については、想定どおり締切の早い物から順に解けるかをチェックすればOK

    // 解く問題の選び方は貪欲には決められないので、以下の様な動的計画法で考える
    // 「i番目の問題を解くか決める。解く場合は現在時刻がTi増えるので、動的計画法で最も多くの問題を解ける様なフローを探す」

    // テーブル定義: DP[i][j]:i番目までの問題を解き終わった時点の時刻がjである時の問題の解答数の最大値
    // 初期状態: DP[0][T0] = 1
    // 遷移: DP[i][j] = DP[i-1][j] (D < j(締切を過ぎた場合) or j < T(まだ解き終わっていない場合))
    //               = max(DP[i-1][j], DP[i-1][j-Ti] + 1) (T<=j<=Dの場合)
    //      パターンA: i-1番目の問題を解答した時点で時刻jであり、i番目の問題を解かない
    //      パターンB: i-1番目の問題を解答した時点で時刻j-Tiであり、i番目の問題を解く

    constexpr ll MAX_TIME = 1440;
    vector<vector<ll>> DP(N + 1, vector<ll>(MAX_TIME + 1, 0));
    DP[0][0] = 0;
    dump(sorted_questions.size());
    REP3(i, 1, N + 1) REP(j, MAX_TIME + 1) {
        auto [solve_time, deadline] = sorted_questions[i - 1];
        if (deadline < j || j < solve_time) DP[i][j] = DP[i - 1][j];
        else DP[i][j] = std::max(DP[i - 1][j], DP[i - 1][j - solve_time] + 1);
    }
    ll result(-1);
    REP(j, MAX_TIME + 1) result = std::max(result, DP[N][j]);
    dump(DP);
    cout << result << endl;
}

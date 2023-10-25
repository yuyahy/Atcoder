// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif

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
  int N(0), S(0);
  cin >> N >> S;
  vector<int> cards(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> cards[i];
  }
  // 二次元DPテーブル
  // DP[i][j]→i番目までのカードを使う、使わないを組み合わせて、数jが作れるか？を意味する
  vector<vector<bool>> DP(N + 1, vector<bool>(S + 1, false));
  // 初期値
  // 0番目までのカード(=どれも使えない)を使って作れるのは0のみ。
  // よって、DP[0][0] = true, DP[0][0...N] = false
  DP[0][0] = true;
  for (int j = 1; j < S + 1; j++) {
    DP[0][j] = false;
  }
  // ここからDP
  for (int j = 0; j < S + 1; j++) {
    for (int i = 1; i < N + 1; i++) {
      // DP[i][j]がtrueになるのは以下の2パターン
      // 1. DP[i-1][j] = true → i番目のカードを選ばなければOK
      // 2. DP[i-1][j - i番目のカード] = true → i番目のカードを選べばOK
      // ※ただしパターン2については、
      // 事前に(j - i番目のカード)=0以上である事をチェックしておく必要あり
      if (j >= cards[i - 1] && (DP[i - 1][j] || DP[i - 1][j - cards[i - 1]])) {
        DP[i][j] = true;
      }
      if (j < cards[i - 1] && DP[i - 1][j]) {
        DP[i][j] = true;
      }
    }
  }
  auto result_str = DP[N][S] ? "Yes" : "No";
  cout << result_str << endl;
}

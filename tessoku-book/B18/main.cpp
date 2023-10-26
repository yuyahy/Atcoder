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

  // 選ぶカードを復元
  vector<int> select_cards;
  int now_card(N), now_sum(S);
  while (now_card > 0) {
    bool bSelect(false);
    if (now_sum >= cards[now_card - 1]) {
      // 一個前までのカードをどう選んでも和が作れない &
      // 一個前までのカードの和+今回のカードの数字を足して
      // 目的の和になる場合は選択する
      bSelect = !DP[now_card - 1][now_sum] &&
                        DP[now_card - 1][now_sum - cards[now_card - 1]]
                    ? true
                    : false;
    }
    // 選択する場合は目的の和を更新する
    if (bSelect) {
      select_cards.push_back(now_card);
      now_sum = now_sum - cards[now_card - 1];
    }
    now_card -= 1;
  }
  // 和が作れないパターン
  if (select_cards.size() == 0) {
    cout << -1 << endl;
  } else {
    cout << int(select_cards.size()) << endl;
    for (int i = int(select_cards.size()) - 1; i >= 0; i--) {
      if (i == 0) {
        cout << select_cards[i] << endl;
      } else {
        cout << select_cards[i] << " ";
      }
    }
  }
}
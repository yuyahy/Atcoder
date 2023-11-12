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

int double_num(int num) {
  int y;

  /* １桁の場合、ゾロ目ではないので終了 */
  if (!(num / 10)) return 1;

  y = num % 10; /* １の位を記憶 */
  while (1) {
    num /= 10; /* 10で割って桁を下げる。1234なら123になる。 */
    if (!num) break; /* 位が無くなると終了 */

    if (y != num % 10) /* １の位とXの位を比較。 */
      return 0;        /* 違っていたら終了 */
  }
  return 1;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  vector<int> D(N + 1, 0);
  for (int i = 1; i <= N; i++) {
    cin >> D[i];
  }

  int sum(0);
  for (int i = 1; i <= N; i++) {
    if (double_num(i) == 0) continue;
    string str1 = to_string(i);
    for (int j = 1; j <= D[i]; j++) {
      if (double_num(j) == 0) continue;
      string str = to_string(j);
      bool bMatch(true);
      for (int k = 0; k < str.length(); k++) {
        if (str[k] != str1[0]) bMatch = false;
      }
      if (bMatch) sum++;
    }

    // int tmp(i), pw(1), origin(i);
    // while (true) {
    //   if (tmp <= D[i]) {
    //     tmp += origin * std::pow(10, pw);
    //     sum++;
    //     pw++;
    //     dump(tmp);
    //   } else {
    //     break;
    //   }
    // }
  }
  cout << sum << endl;
}

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
  int n(0);
  cin >> n;

  // ※ひょっとしたらSTLなどで一発で変換できるかも
  string binary("");
  while (true) {
    binary += to_string(n % 2);
    // 2で割ったときの商が0になった時点までの余りを収集したいので、
    // このタイミングでループチェック
    if (n / 2 == 0) break;
    n /= 2;
  }
  reverse(binary.begin(), binary.end());
  // 問題文より、10桁未満の場合は上位桁を0埋め
  auto diff_to_max_length = 10 - int(binary.size());
  if (diff_to_max_length) {
    for (int i = 0; i < diff_to_max_length; i++) binary.insert(0, "0");
  }

  cout << binary << endl;
}

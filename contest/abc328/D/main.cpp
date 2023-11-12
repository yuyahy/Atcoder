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
  // Github Actionsのテスト
  string str;
  cin >> str;
  // 先頭からi文字目までの文字列から"ABC"を削除した文字列
  vector<string> DP(str.length(), "");
  DP[0] = str;
  for (int i = 1; i < str.length(); i++) {
    // auto sub = str.substr(i);
    // if (sub.length() < 3) {
    //   DP[i] = DP[i - 1];
    // } else {
    auto pos = DP[i - 1].find("ABC");
    if (pos == string::npos) {
      DP[i] = DP[i - 1];
    } else {
      DP[i] = DP[i - 1].erase(pos, 3);
    }
    // }
  }
  dump(DP);

  //   while (true) {
  //     auto pos = str.find("ABC");
  //     if (pos == string::npos) {
  //       break;
  //     } else {
  //       str = str.erase(pos, 3);
  //     }
  //   }
  cout << DP[str.length() - 1] << endl;
}

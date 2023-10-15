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
  ll N(0);
  cin >> N;
  bool bExist = false;
  //   if (N % 2 == 0 || N % 3 == 0 || N == 1) bExist = true;
  int MAX = 10000;
  for (int x = 0; x < MAX; x++) {
    ll two = std::pow(2, x);
    if (two > N) break;
    for (int y = 0; y < MAX; y++) {
      ll three = std::pow(3, y);
      if (two * three == N) {
        bExist = true;
        break;
      } else if (two * three > N) {
        break;
      }
    }
  }

  auto str_result = bExist ? "Yes" : "No";
  cout << str_result << endl;

  //   for (int x = 0; x < count; x++) {
  //     /* code */
  //   }
}

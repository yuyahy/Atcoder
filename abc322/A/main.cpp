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
  int N(0);
  cin >> N;
  vector<int> p_vec, q_vec;
  std::string input_string;

  cin >> input_string;
  //   dump(input_string);
  auto pos = input_string.find("ABC");
  //   for (int i = 0; i < count; i++) {
  //     /* code */
  //   }

  int result_str = pos != std::string::npos ? pos + 1 : -1;
  cout << result_str << endl;
}

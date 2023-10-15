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

std::string extractLastNChars(std::string const& str, int n) {
  if (str.size() < n) {
    return str;
  }

  return str.substr(str.size() - n);
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0), M(0);
  cin >> N >> M;
  std::string S_string, T_string;
  cin >> S_string;
  cin >> T_string;

  //   dump(input_string);
  //   auto pos = input_string.find("ABC");

  // 接頭辞か
  bool bPrefix = false;
  auto prefix_string = T_string.substr(0, N);
  if (prefix_string == S_string) bPrefix = true;

  // 接尾辞か
  bool bSuffix = false;
  auto suffix_string = extractLastNChars(T_string, N);
  if (suffix_string == S_string) bSuffix = true;

  int result = -1;
  if (bPrefix && bSuffix) {
    result = 0;
  } else if (bPrefix && !bSuffix) {
    result = 1;
  } else if (!bPrefix && bSuffix) {
    result = 2;
  } else {
    result = 3;
  }
  cout << result << endl;
}

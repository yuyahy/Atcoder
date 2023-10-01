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
  //   int N(0), M(0);
  //   cin >> N >> M;
  vector<vector<string>> poly_vec;
  for (int i = 0; i < 3; i++) {
    vector<string> poly_string;
    for (int k = 0; k < 4; k++) {
      std::string tmp_string;
      cin >> tmp_string;
      poly_string.push_back(tmp_string);
    }
    for (const auto& poly : poly_string) {
      cout << poly << endl;
    }
    poly_vec.push_back(poly_string);
  }
  //   dump(input_string);
  //   auto pos = input_string.find("ABC");

  //   cout << result << endl;
}

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
  vector<int> a_vec;

  for (int i = 0; i < N; i++) {
    auto tmp = 0;
    cin >> tmp;
    a_vec.push_back(tmp);
  }

  auto bFind = false;
  for (int i = 0; i < N - 2; i++) {
    for (int j = i + 1; j < N - 1; j++) {
      for (int k = i + 2; k < N; k++) {
        if (a_vec[i] + a_vec[j] + a_vec[k] == 1000) {
          bFind = true;
          break;
        }
      }
    }
  }

  auto result_str = bFind ? "Yes" : "No";
  cout << result_str << endl;
}

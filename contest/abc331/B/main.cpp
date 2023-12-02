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

  int N(0), S(0), M(0), L(0);
  cin >> N >> S >> M >> L;
  int S_cnt(0), M_cnt(0), L_cnt(0);
  int N_max(100), min(1e8);
  // それぞれ何パック買うか
  for (int i = 0; i < N_max; i++) {
    for (int j = 0; j < N_max; j++) {
      for (int k = 0; k < N_max; k++) {
        if (i * 6 + j * 8 + k * 12 < N) continue;
        min = std::min(min, i * S + j * M + k * L);
      }
    }
  }

  cout << min << endl;
}
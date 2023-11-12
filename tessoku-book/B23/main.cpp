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

double calc_distance(double x, double y) { return std::hypot(x, y); }

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  vector<int> X(N + 1, 0), Y(N + 1, 0);

  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  dump(X);
  dump(Y);

  // i→通った都市の組み合わせ、j→今いる都市 = 最小の移動時間
  vector<vector<double>> DP((1 << N), vector<double>(N + 1, 10000000));
  DP[0][0] = 0;

  // 今いる都市から次の都市に遷移する時にかかる時間を更新
  for (int i = 0; i < (1 << N); i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        if ((i / (1 << k)) % 2 == 1) continue;
        // 今いる都市jから次の都市kに遷移する
        DP[i + (1 << k)][k] = std::min(
            DP[i + (1 << k)][k],
            DP[i][j] + calc_distance(abs(X[j] - X[k]), abs(Y[j] - Y[k])));
      }
    }
  }
  dump(DP);
  cout << DP[(1 << N) - 1][0] << endl;
}

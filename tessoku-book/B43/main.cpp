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

  ll N(0), M(0);
  cin >> N >> M;

  // i番目の生徒が何問不正解だったか
  vector<int> A_False(N, 0);
  for (int i = 0; i < M; i++) {
    int tmp(0);
    cin >> tmp;
    A_False[tmp - 1]++;
  }

  for (int i = 0; i < N; i++) {
    cout << M - A_False[i] << endl;
  }
}

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
  int N(0), D(0);
  cin >> D;
  cin >> N;
  int L(0), R(0);

  // 以下のコメントアウトされているのが最初に書いた回答
  // 一応ACにはなるが、現在のソースコードと比較すると最大で10倍ほど遅いため、
  // 前日比を使った方法の方が良い
  vector<int> accum_participants(D);
  accum_participants.push_back(0);
  for (int i = 0; i < N; i++) {
    cin >> L >> R;
    // for (int j = L - 1; j < R; j++) accum_participants[j] += 1;
    accum_participants[L] += 1;
    accum_participants[R + 1] += -1;
  }
  for (int i = 1; i < D + 1; i++) {
    accum_participants[i] += accum_participants[i - 1];
    cout << accum_participants[i] << endl;
  }

  //   for (const auto& participant : accum_participants) {
  //     cout << participant << endl;
  //   }
}

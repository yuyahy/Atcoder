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
  int N(0), Q(0);
  cin >> N >> Q;
  string S;
  cin >> S;
  dump(S);
  vector<int> l(Q + 1, 0), r(Q + 1, 0);
  for (int i = 1; i <= Q; i++) {
    cin >> l[i] >> r[i];
  }
  dump(l);
  dump(r);
  // 先頭からi文字目までの同じ英小文字が隣合う箇所の和
  vector<ll> accumulate(N, 0);

  for (int i = 1; i < S.length(); i++) {
    if (S[i] == S[i - 1]) {
      accumulate[i] = accumulate[i - 1] + 1;
    } else {
      accumulate[i] = accumulate[i - 1];
    }
  }
  dump(accumulate);

  for (int i = 1; i <= Q; i++) {
    cout << accumulate[r[i] - 1] - accumulate[l[i] - 1] << endl;
  }
}

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

  int M(0), D(0), y(0), m(0), d(0);
  cin >> M >> D;
  cin >> y >> m >> d;
  int y_(0), m_(0), d_(0);
  if (d + 1 <= D) {
    d_ = d + 1;
    m_ = m;
    y_ = y;
  } else {
    d_ = 1;
    m_ = m + 1;
    y_ = y;
    if (m_ > M) {
      m_ = 1;
      y_ += 1;
    }
  }
  cout << y_ << " " << m_ << " " << d_ << endl;
}

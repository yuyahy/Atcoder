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
  string n("");
  cin >> n;
  int digit = 0;
  digit = std::stoi(n, 0, 2);
  // 初めは以下の方法で実装していたが、上記の方が簡潔で早そうなので変更した
  // なお、bitsetを使っても一発で変換できるっぽい
  //   for (int i = 0; i < int(n.size()); i++) {
  //     // N桁目について、0 or 1 * 2のN-1乗の総和を求め、
  //     // 2進数→10進数に変換する
  //     digit += int(n[i] - '0') * int(std::pow(2, n.size() - i - 1));
  //   }

  cout << digit << endl;
}

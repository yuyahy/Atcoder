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
  ll N(0), A(0);
  cin >> N;
  string T("");
  ll result(0);
  for (int i = 0; i < N; i++) {
    cin >> T >> A;
    // Note: 愚直に演算→余りを出力...とやっているとオーバーフローする(long
    // longでも)
    //       そのため、足し算引き算掛け算では演算途中のタイミングで余りをとっても結果が変わらない
    //       性質があるので、操作のたびに余りを代入する事でオーバーフローを防ぐ
    // result %= 10000;
    if (T == "+") {
      result += A;
    } else if (T == "-") {
      result -= A;
    } else {
      result *= A;
    }
    // Note:　演算の結果マイナスになる場合は、商を足す必要がある
    // e.g. 10003 - 4 = 9999が答えだが、余りで計算すると、
    //       3 -4 = -1になってしまうため
    if (result < 0) result += 10000;
    dump(T);
    dump(A);
    cout << result % 10000 << endl;
  }
}

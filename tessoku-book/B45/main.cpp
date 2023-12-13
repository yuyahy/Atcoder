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

  ll a(0), b(0), c(0);
  cin >> a >> b >> c;
  // ある数を+1し、また別の数を-1するので、整数の総和は不変量である
  // よって初期状態での総和が0の場合のみ、この操作を繰り返してすべての
  // 整数を0にする事ができる
  //
  // a+b+c=0の場合、「正の整数の絶対値の合計」と「負の整数の絶対値の合計」
  // が必ず等しくなる。よって、正の整数を+1し、負の整数を-1する操作を
  // 「正の整数の絶対値の合計」回行えば、必ずすべての整数が0になる
  auto result = (a + b + c) == 0 ? "Yes" : "No";
  cout << result << endl;
}

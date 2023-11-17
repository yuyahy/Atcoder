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
  // Note: 原因不明だが、atestは普通に通るが、asubを使って提出しようとすると
  //       2つ目のケースでTLEになる。ただし、AtCoderのUIからだと普通に提出できる謎
  // 追記:
  // test時のオプションをマシマシにしている事が原因っぽい(ASANなどを消してコンパイルした物は通った)
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0);
  cin >> N;
  // modintを使うと、演算の度に自動で余りを計算してくれるので便利
  // もちろん、vector<int>で足し算する要素の余りを取る &
  // 演算結果で更に余りを取ってもOK
  // →自分が試した限りではmodintを使った方が2倍程度高速だった
  vector<mint> fib_mod(N, 0);
  fib_mod[0] = 1;
  fib_mod[1] = 1;
  for (int i = 2; i < N; i++) {
    fib_mod[i] = fib_mod[i - 1] + fib_mod[i - 2];
    // modintを使わない場合、vector<int> fib_mod(N, 0);
    // fib_mod[i] = (fib_mod[i - 1] % 1000000007) + (fib_mod[i - 2] %
    // 1000000007); fib_mod[i] %= 1000000007;
  }
  cout << fib_mod[N - 1].val() << endl;
}

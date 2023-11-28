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

  ll N(0);
  cin >> N;

  // 1.各桁について、総和への寄与を考えてみましょう。
  // たとえば、f(456)=4+5+6 です。ほかにも345,152 などで
  // 10 の位が5 になります。
  // 各桁が1,2,…,9になる回数が何回であるかを高速に計算することができれば、答えを求めることができそうです。

  // e.g [1, 9]だと、1の位に[1,2,...9]がそれぞれ一回ずつでてくる
  // e.g [10, 19]だと、1の位に[1,2,...9]がそれぞれ一回ずつでてくる
  // e.g.[1, 100]だと、1の位に[1,2,...9]がそれぞれ、([1, 9]のカウント+[10,
  // 19]+...+[90, 99]のカウント)だけでてくる
  //     → 1 + 1*9 = 10回でてくる

  // 10のN乗を求める
  constexpr int max_digit = 16;
  vector<ll> Power10(max_digit + 1, 0);
  Power10[0] = 1;
  for (int i = 1; i <= max_digit; i++) {
    Power10[i] = Power10[i - 1] * 10LL;
  }

  // R[i][j]の計算
  // R[i][j]→下からi桁目の数字がjとなる、0以上N以下の整数は何個あるか？
  vector<vector<ll>> R(18, vector<ll>(10, 0));
  for (int i = 0; i <= 14; i++) {
    // 下からi桁目の数字を求める
    ll Digit = (N / Power10[i]) % 10LL;
    // R[i][j]の値を求める
    // R[i][j]は以下の様な形で一般化できる
    // ・j < （10^iの位の値）の場合→[N÷10^(i+1)]×10^i + 10^i
    // ・j = （10^iの位の値）の場合→[N÷10^(i+1)]×10^i + (Nmod10^i+1)
    // ・j > （10^iの位の値）の場合→[N÷10^(i+1)]×10^i
    for (int j = 0; j < 10; j++) {
      if (j < Digit) {
        R[i][j] = (N / Power10[i + 1]) * Power10[i] + Power10[i];
      }
      if (j == Digit) {
        R[i][j] = (N / Power10[i + 1]) * Power10[i] + (N % Power10[i]) + 1LL;
      }
      if (j > Digit) {
        R[i][j] = (N / Power10[i + 1]) * Power10[i];
      }
    }
  }

  // 答えを求める
  ll Answer(0);
  for (int i = 0; i < max_digit; i++) {
    for (int j = 0; j < 10; j++) {
      Answer += 1LL * j * R[i][j];
    }
  }
  cout << Answer << endl;
}

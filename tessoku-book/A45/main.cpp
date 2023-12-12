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

  int N(0);
  string C(""), A("");
  cin >> N >> C;
  cin >> A;

  // Note:本設問では、最初のカードの情報が確定した時点で、
  //      最終的に何の色になるかは操作に関係なく決まる
  //      例えば、3枚のカードをそれぞれ、(W,R,B)=(0,1,2)と整数を割り当て、
  //      カードのスコアの合計に着目すると以下の性質がある。
  //      ・6種類のどの操作を行っても、その前後でスコアの合計を3で割った余りは変化しない
  //      これは、どの操作を行っても、スコアが±0 or -3にしかならないため
  //      よって初期状態でスコアの計算をし、それを3で割った余りを計算し、目的のCと一致
  //      するかを見ればO(N)で解ける

  // ※不変量とは操作によって変化しない何らかの値の事を指す
  // 数字を割り振るという発想は浮かんできたが、その余りに着目することはできなかった。。。
  // また、余りと紐づけて考える都合上、0~2で割り振る必要がある
  //
  // e.g. 1~3で割り振ると操作前後のスコアの増減は以下の様になる
  // 白白→-1
  // 青青→-1
  // 赤赤→−４
  // 白青→-1
  // 白赤→-1
  // 青赤→-4

  // 文字列操作などを定量的に評価できると、その規則性に気づきやすくなるのかも

  static_modint<3> score;
  for (int i = 0; i < (int)A.length(); i++) {
    int mul(0);
    switch (A[i]) {
      case 'W':
        mul = 0;
        break;
      case 'B':
        mul = 1;
        break;
      case 'R':
        mul = 2;
        break;
      default:
        assert(0);
        break;
    }
    score += mul;
  }

  int C_int(0);
  switch (C[0]) {
    case 'W':
      C_int = 0;
      break;
    case 'B':
      C_int = 1;
      break;
    case 'R':
      C_int = 2;
      break;
    default:
      assert(0);
      break;
  }
  string result = score == C_int ? "Yes" : "No";
  cout << result << endl;
}

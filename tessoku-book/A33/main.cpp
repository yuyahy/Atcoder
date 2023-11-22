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
  cin >> N;
  vector<int> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  // Note:
  // 山が2つの場合は、山1と山2の石の数が等しい場合は、後手必勝、数が異なる場合は先手必勝。
  //       →山の石の数が等しい場合は、先手の取った石の数をそのまま後手が真似して同じ数とることで必ず勝てる
  //        石の数が等しくない場合は、先手が山同士の石の数が等しくなる様に1手目で石を取り、後は先手が物真似戦略
  //        をすることで必ず勝てる
  // これを山の数が一般の場合に拡張すると以下になる
  // ・A1 XOR A2 XOR A3...... XOR AN ≠ 0の場合→先手必勝
  // ・A1 XOR A2 XOR A3...... XOR AN = 0の場合→後手必勝

  // 全要素のXOR=ニム和を取る
  int XOR_Sum = A[0];
  for (int i = 1; i < N; i++) {
    XOR_Sum ^= A[i];
  }
  auto result = XOR_Sum ? "First" : "Second";
  cout << result << endl;
}

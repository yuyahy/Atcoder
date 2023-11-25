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
  int N(0), K(0);
  cin >> N >> K;
  vector<int> bulbs(N, 0);
  string str("");
  cin >> str;
  int onCnt(0);
  for (int i = 0; i < N; i++) {
    cin >> str;
    bulbs[i] = int(str[i] - '0');
    if (bulbs[i] == 1) onCnt++;
  }
  dump(bulbs);
  // 2個選んで反転させた後の、ONになっている電球の個数の偶奇は、
  // 1. 2個ともON→変わらない(ONの個数が-2)
  // 2. 片方がON、もう一方がOFF→変わらない(ONの個数も変わらない)
  // 3. 2個ともOFF→変わらない(ONの個数が+2)
  // よって、どの様に操作しても偶奇の個数を変えることはできないので、

  // K=0 → 元々ONだった個数が偶数であれば2個ずつOFFにして可能
  // Kと元々ONだった個数の偶奇が一致する →　2個ずつOFF→ON or ON→OFFで可能
  // Kと元々ONだった個数の偶奇が一致しない →　上記の理由により不可能
  bool canChange(false);
  if (K % 2 == onCnt % 2) {
    canChange = true;
  } else {
    canChange = false;
  }
  auto result = canChange ? "Yes" : "No";
  cout << result << endl;
}

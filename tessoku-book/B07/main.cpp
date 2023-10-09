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
  int T(0), N(0);
  cin >> T;
  cin >> N;
  vector<int> employees(T);
  employees.push_back(0);
  int L(0), R(0);
  // 今回はRが退店時刻を表現しているため、それを出口として-1する
  // →A07の様に存在期間が与えられている場合は、末端+1したインデックスが消失時刻になる
  for (int i = 0; i < N; i++) {
    cin >> L >> R;
    employees[L + 1] += 1;
    employees[R + 1] -= 1;
  }
  // 累積和を求める
  for (int i = 1; i < T + 1; i++) {
    employees[i] += employees[i - 1];
    cout << employees[i] << endl;
  }
}

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

constexpr double eps = 0.001;

// 近似解を求める関数
double func(double x) { return (std::pow(x, 3) + x); }

bool isLowerIndex(double key, int N) {
  // 目標のインデックスはkey以下か
  if (func(key) >= N) {
    return true;
  } else {
    return false;
  }
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  constexpr int MAX = 100000;
  double right(MAX);
  double left(1.0);
  double mid(0);

  while (right - left > eps) {
    mid = (right + left) / 2;
    if (isLowerIndex(mid, N)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  // 小数点の許容誤差以降の値を切り捨てる
  right /= eps;
  double result = int(right) * eps;
  cout << fixed << setprecision(6) << result << endl;
}

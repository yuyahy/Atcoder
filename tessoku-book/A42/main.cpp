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

  vector<pair<int, int>> students(N + 1, {0, 0});
  for (int i = 1; i <= N; i++) {
    auto tmpA(0), tmpB(0);
    cin >> tmpA >> tmpB;
    students[i] = {tmpA, tmpB};
  }
  dump(students);

  // どの2人も差がK以内に収まるためには、
  // 取った人たちの最大値をmax、最小値をminとすると、
  // 0 <= max - min <= Kを満たす必要がある
  // よって[0,K]→[1,K+1]→...の範囲で取れる人を全員取っていき、最大値を求めれば答えが求まる
  // 今回の制約条件下だと、最悪の計算量はO(100 * 100 * 300)程度
  // なお、二次元累積和を使った方針だと、O(100*100 + 300)まで減らせるらしい
  // TODO: 二次元累積和でも実装してみる

  // 区間を固定して、選べる人を取っていく
  int max(0);
  for (int begin = 1; begin < 100; begin++) {
    // 条件よりA、Bは共に[1, 100]の範囲
    auto end = std::clamp(begin + K, 1, 100);
    for (int begin_energy = 1; begin_energy < 100; begin_energy++) {
      // 条件よりA、Bは共に[1, 100]の範囲
      auto end_energy = std::clamp(begin_energy + K, 1, 100);
      int cnt(0);
      for (const auto& [power, energy] : students) {
        // ある変数の値がある区間[a,b]内に収まっているかはstd::clampを使うと
        // 演算子を使うよりは簡潔に記述できる
        if (power == std::clamp(power, begin, end) &&
            energy == std::clamp(energy, begin_energy, end_energy)) {
          cnt++;
        }
      }
      max = std::max(max, cnt);
    }
  }
  cout << max << endl;
}

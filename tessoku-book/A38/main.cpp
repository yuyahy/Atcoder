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
  int N(0), D(0);
  cin >> D >> N;
  int L(0), R(0), H(0);
  // <日付、働ける時間の最大値>
  map<int, int> worktime;
  // 1日の最大値の24Hで初期化
  // Note: 全ての日付が[L, R ,D]の範囲に出てくるとは限らないので、
  //       指定のない日は24Hで計算する必要あり
  for (int i = 1; i <= D; i++) {
    worktime[i] = 24;
  }
  // 働ける時間を更新
  for (int i = 0; i < N; i++) {
    cin >> L >> R >> H;
    for (int j = L; j <= R; j++) {
      worktime[j] = min(worktime[j], H);
    }
  }

  auto sum =
      std::accumulate(worktime.begin(), worktime.end(), 0,
                      [](const int previous, const std::pair<int, int>& p) {
                        return previous + p.second;
                      });
  std::cout << sum << std::endl;

  dump(L);
  dump(R);
  dump(H);
  dump(worktime);
}

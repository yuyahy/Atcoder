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

int calc_later(const vector<bool>& fireworks_day, const int& idx,
               const int& N) {
  int cnt = 0;
  for (int i = idx; i < N; i++) {
    if (fireworks_day[i]) {
      break;
    }
    cnt++;
  }
  return cnt;
}
// int calc_later(bool fireworks_day, const int& idx, const int& N) {
//   auto cnt = 0;
//   for (int i = idx; i < N; i++) {
//     if (fireworks_day[i]) {
//       break;
//     }
//     cnt++;
//   }
//   return cnt;
// }

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0), M(0);
  cin >> N >> M;
  //   std::vector<bool> fireworks_day(N, false);
  //   std::vector<bool> fireworks_day;
  bool fireworks_day[N];
  //   fireworks_day.reserve(N);
  for (int i = 0; i < N; i++) fireworks_day[i] = false;
  for (int i = 0; i < M; i++) {
    int idx = -1;
    // cin >> idx;
    scanf("%d", &idx);
    fireworks_day[idx - 1] = true;
  }

  //   dump(fireworks_day);
  //   auto pos = input_string.find("ABC");

  int cnt = 0;
  for (int i = 0; i < N; i++) {
    // int later_day = calc_later(fireworks_day, i, N);
    if (cnt > 0) {
      cnt--;
    } else {
      for (int j = i; j < N; j++) {
        if (fireworks_day[j]) {
          break;
        }
        cnt++;
      }
    }
    printf("%d\n", cnt);
  }
}

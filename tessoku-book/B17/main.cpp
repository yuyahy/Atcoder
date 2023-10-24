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
  vector<int> h(N, 0), DP(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }
  DP[0] = 0;
  DP[1] = std::abs(h[1] - h[0]);
  for (int i = 2; i < N; i++) {
    DP[i] = std::min(DP[i - 1] + std::abs(h[i] - h[i - 1]),
                     DP[i - 2] + std::abs(h[i] - h[i - 2]));
  }

  // 最短経路を復元する
  auto place(N);
  vector<int> shortest_place;
  while (place > 0) {
    shortest_place.push_back(place);
    // Note:
    // 以下の条件を比較にすると、テストケースの一部と合わない
    // →最短経路が複数ある際にテストケースの回答と合わない事がある？
    if (DP[place - 2] + std::abs(h[place - 1] - h[place - 2]) ==
        DP[place - 1]) {
      place = place - 1;
    } else {
      place = place - 2;
    }
  }
  cout << shortest_place.size() << endl;
  for (int i = int(shortest_place.size()) - 1; i >= 0; i--) {
    if (i == 0) {
      cout << shortest_place[i] << endl;
    } else {
      cout << shortest_place[i] << " ";
    }
  }
}

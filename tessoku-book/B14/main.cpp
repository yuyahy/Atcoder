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

vector<int> calc_sum_by_bit_search(const auto& array, const int& N) {
  vector<int> sums;
  // bit全探索で部分和の集合を求める
  for (int bit = 0; bit < (1 << N); ++bit) {
    int sum(0);
    for (int i = 0; i < N; i++) {
      if (bit & (1 << i)) {
        sum += array[i];
      }
    }
    sums.push_back(sum);

    // bit の表す集合の出力
    // cout << bit << ": {";
    // for (int i = 0; i < (int)sums.size(); ++i) {
    //   cout << sums[i] << " ";
    // }
    // cout << "}" << endl;
  }
  return sums;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0), K(0);
  cin >> N >> K;
  vector<int> cards1(N / 2, 0), cards2(N - (N / 2), 0);
  for (int i = 0; i < N / 2; i++) {
    cin >> cards1[i];
  }
  for (int i = 0; i < N - (N / 2) / 2; i++) {
    cin >> cards2[i];
  }

  // (N/2)*2^(N/2) + (N/2)*2^(N/2)  + logN = 491520 + 491520 + 3.40　=
  // 983040回程度の計算
  auto first_half = calc_sum_by_bit_search(cards1, N / 2);
  auto latter_half = calc_sum_by_bit_search(cards2, N - (N / 2));
  bool bFind = false;
  // 二分探索のためにソートしておく
  sort(latter_half.begin(), latter_half.end());
  for (const auto& first : first_half) {
    auto position =
        lower_bound(latter_half.begin(), latter_half.end(), K - first);
    if (*position == K - first) {
      bFind = true;
      break;
    }
  }
  auto result_str = bFind ? "Yes" : "No";
  cout << result_str << endl;
}

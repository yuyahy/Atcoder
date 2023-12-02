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
  vector<ll> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  // Aをコピーしソート
  // ソートした配列で累積和
  // Aiごとに二分探索して、累積和の配列からそれ以上の要素を求める
  auto A_sort = A;
  sort(A_sort.begin(), A_sort.end());
  dump(A);
  dump(A_sort);
  vector<ll> number_sum;
  ll now_number(A_sort[0]), now_sum(A_sort[0]);

  // ある数未満の和のmap
  map<ll, ll> number_cnt;
  ll sum(A_sort[0]);
  number_cnt[A_sort[0]] = A_sort[0];
  for (int i = 1; i < N; i++) {
    if (number_cnt.count(A_sort[i]) == 0) {
      number_cnt[A_sort[i]] = number_cnt[A_sort[i - 1]];
      number_cnt[A_sort[i]] += A_sort[i];
    } else {
      number_cnt[A_sort[i]] += A_sort[i];
    }
    sum += A_sort[i];
  }
  dump(number_cnt);
  dump(sum);

  for (int i = 0; i < N; i++) {
    if (i == N - 1) {
      cout << sum - number_cnt[A[i]] << endl;
    } else {
      cout << sum - number_cnt[A[i]] << " ";
    }
  }
}
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
  // Note: std::set & std::set::lower_boundを使う方針で実装したが、TLEしたため、
  //      std::vectorをコピー & ソートした上で重複要素を削除する方針に変更した
  // XをAの重複要素を削除したソート済みの配列にする事で、A[i]を座標圧縮した値は、
  // Xの該当要素のインデックスに+1した物になる
  auto X = A;
  std::sort(X.begin(), X.end());
  // Note:
  // std::uniqueは重複している隣接要素のみを削除するため、事前にソートしておく必要がある
  X.erase(std::unique(X.begin(), X.end()), X.end());
  // 二分探索にO(log(N))かかり、N個の要素それぞれに行うため、計算量 : O(Nlog(N))
  for (int i = 0; i < N; i++) {
    auto position = std::lower_bound(X.begin(), X.end(), A[i]);
    auto idx_lower = distance(X.begin(), position);
    if (i == N - 1) {
      cout << idx_lower + 1 << endl;
    } else {
      cout << idx_lower + 1 << " ";
    }
  }
}

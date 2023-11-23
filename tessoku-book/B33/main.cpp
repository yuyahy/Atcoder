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

  ll N(0), H(0), W(0);
  cin >> N >> H >> W;

  vector<pair<ll, ll>> grid(N, {0, 0});
  ll A(0), B(0);
  for (ll i = 0; i < N; i++) {
    cin >> A >> B;
    grid[i] = {A, B};
  }
  // Note:
  // 本問題は行と列の座標をそれぞれ別の山と考えることで、ニムに帰着できる
  // ※左上(1,1)の位置に移動すると、それ以上の移動ができなくなる(山でいうと石が0個の状態)
  //  のため、各成分を-1する必要がある
  ll XOR_Sum_col = grid[0].first - 1;
  ll XOR_Sum_row = grid[0].second - 1;
  for (ll i = 1; i < N; i++) {
    XOR_Sum_col ^= grid[i].first - 1;
    XOR_Sum_row ^= grid[i].second - 1;
  }
  dump(XOR_Sum_col);
  dump(XOR_Sum_row);
  dump(XOR_Sum_col ^ XOR_Sum_row);

  // 最終的に行と列でXORした結果が答え
  auto result = (XOR_Sum_col ^ XOR_Sum_row) ? "First" : "Second";
  cout << result << endl;
}

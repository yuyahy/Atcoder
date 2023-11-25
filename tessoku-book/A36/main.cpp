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
  ll N(0), K(0);
  cin >> N >> K;

  // 少なくとも縦方向と横方向にN-1回ずつ移動しないといけない
  // 2*(N-1)回移動しゴールに着いた後に、まだ移動する回数が余っている場合は、往復して回数を消費する必要がある
  // ※残りが奇数だと、元の位置には帰ってこれない
  // また、マス目を交互に別の色で塗ると、今回はグリッドが正方形のため、スタート地点とゴール地点は必ず同じ色になる
  // そして、1回の移動の度に、今いるマスの色は交互に変わるので、偶数回の移動をしなければ、スタート地点と同じ色の
  // マスにはたどり着けない
  bool canReach(false);
  if (2 * N - 2 > K) {
    canReach = false;
  } else {
    auto remain_move_cnt = K - (2 * N - 2);
    if (remain_move_cnt % 2 == 0) canReach = true;
  }
  auto result = canReach ? "Yes" : "No";
  cout << result << endl;
}

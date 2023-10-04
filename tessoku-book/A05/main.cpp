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
  // 各カードは[1, N]を書かなければいけない
  // 赤、青、白の３枚の書き方について全探索で
  // 愚直にループすると、O(N^3)で制約よりNmax=3000のため、3000^3 =
  // 270億通りで処理時間2秒では間に合わない(大体1秒で1億回の計算しかできないため)
  // そこで3つの数値を使って総和をKにする際に
  // 2つの数値が決まれば残り1個が何の数値か決まる性質を利用し、ループのネストを減らす
  int cnt = 0;
  for (int i = 1; i <= N; i++) {
    int tmp = K - i;
    for (int j = 1; j <= N; j++) {
      // 2つの数値が決まれば、総和をKにする様な3つ目の数値の決定される
      int tmp2 = tmp - j;
      // 最後の数値が制約条件を満たしていればカウントする
      if (tmp2 >= 1 && tmp2 <= N) cnt++;
    }
  }

  cout << cnt << endl;
}

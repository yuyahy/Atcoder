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

// index が条件を満たすかどうか
bool isLowerIndex(vector<int> a, int index, int key) {
  // Note: 求める経過秒数(この場合のindex)が決まれば、
  // その間に各プリンターが印刷する枚数は、
  // (経過秒数) / (各プリンターの印刷間隔)
  // で求められる事がポイント。累積和を使う必要はない
  ll sum = 0;  // ここをintにすると一部のテストケースでエラーになる(桁あふれ？)
  for (const auto& elem : a) {
    sum += index / elem;
  }
  if (sum >= key)
    return true;
  else
    return false;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0), K(0);
  cin >> N >> K;
  vector<int> printers(N, 0);
  int tmp = 0;
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    printers[i] = tmp;
  }
  // 捜索範囲
  // 制約より、答えは10^9以下とあるので、それを最大値とする
  constexpr int MAX_CNT = 1000000000;
  int left = 0;
  int right = MAX_CNT;
  int mid = -1;
  // Note: 終了条件とleftの更新値の関係は注意。
  // e.g. while (right - left > 0)の場合は、 left = mid+1にしないと無限ループ

  while (right - left > 1) {
    mid = (right + left) / 2;
    // 答えのKが存在する範囲がmidより小さいかを判定する
    if (isLowerIndex(printers, mid, K)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  cout << right << endl;
}

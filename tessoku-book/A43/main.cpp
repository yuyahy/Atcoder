
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
  ll N(0), L(0);
  cin >> N >> L;
  // 本問題のポイントは、「誰が１番最後に出るか」は判別する必要がないという事。
  // あくまで、「最後の人がトンネルから出るのは何秒後か」だけ分かれば良い。
  // そこで、以下の様に求める条件を言い換える事ができる。
  // ・「トンネルの幅が充分に大きく、すれ違える時に、最後の人は何秒後にトンネルをでるか」
  // これは初期位置がゴールから最も遠い人がゴールするまでにかかる時間と一致する
  // 解説ACだったが、この発想は横軸を秒、縦軸を現在位置とする様な１次関数のグラフ
  // を書き、すれ違っても向きを変えても、現れる軌跡は変わらないという所を見ないと
  // 思い浮かばない気がした。
  // →つまり考察系の問題では、図示は有効な気がする
  ll max_distance(0);
  for (int i = 0; i < N; i++) {
    ll pos(0), dist(0);
    string direction("");
    cin >> pos >> direction;
    // ゴールまでの距離を算出
    if (direction == "E") {
      dist = L - pos;
    } else {
      dist = pos;
    }
    max_distance = std::max(max_distance, dist);
  }

  cout << max_distance << endl;
}

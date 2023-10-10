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

  int N(0), X(0), Y(0);
  cin >> N;
  constexpr int MAX_SIZE = 1500;
  vector<vector<int>> exist_points(MAX_SIZE + 1, vector<int>(MAX_SIZE + 1, 0));
  // 各行と列の先頭にダミーの0をいれ、累積和計算の場合分けをなくす
  for (int i = 0; i < N; i++) {
    cin >> X >> Y;
    // Note
    // 最初ここを代入にしていたら、サンプルケースはOKだったが、提出後のテストケースがほぼダメだった
    //      →ある座標に対して、2個以上の点が配置されるケースの考慮が漏れていた
    //      特に問題文で「重複しない物とする」などの記載がない場合は、基本的に重複ケースも考慮する必要がありそう
    exist_points[X][Y] += 1;
  }
  // X方向の累積和
  for (int i = 1; i < MAX_SIZE + 1; i++) {
    for (int j = 1; j < MAX_SIZE + 1; j++) {
      exist_points[i][j] += exist_points[i][j - 1];
    }
  }
  // Y方向の累積和
  for (int j = 1; j < MAX_SIZE + 1; j++) {
    for (int i = 1; i < MAX_SIZE + 1; i++) {
      exist_points[i][j] += exist_points[i - 1][j];
    }
  }

  // 質問に答える
  int Q(0), a(0), b(0), c(0), d(0);
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> a >> b >> c >> d;
    // いもす法で対角の情報を使って、指定範囲に存在する点の個数を算出する
    cout << exist_points[c][d] + exist_points[a - 1][b - 1] -
                (exist_points[a - 1][d] + exist_points[c][b - 1])
         << endl;
  }
}

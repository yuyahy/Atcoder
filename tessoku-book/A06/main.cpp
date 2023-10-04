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
#include <numeric>
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
  int N(0), Q(0);
  cin >> N >> Q;
  vector<int> visitors;
  // 先頭にダミーの0を入れておく事で、後々の計算時に1日目のみ出力するケースでも場合分けが不要になる
  visitors.push_back(0);
  for (int i = 0; i < N; i++) {
    auto tmp = 0;
    cin >> tmp;
    visitors.push_back(tmp);
  }
  // 累積和を求める
  // 以下のSTLライブラリを使えば一発で求められそうだが、この環境だと使えなさそうなので
  // 一旦放置(gccだと実装されていない？)
  //   std::exclusive_scan(visitors.begin(), visitors.end(), visitors.begin());
  // 先頭にダミーの0を追加しているため、インデックスに注意
  for (int i = 1; i < N + 1; i++) {
    visitors[i] += visitors[i - 1];
  }
  // 質問の答えを求め、出力する
  int L(0), R(0);
  for (int i = 0; i < Q; i++) {
    cin >> L >> R;
    auto accumu = visitors[R] - visitors[L - 1];
    // 以下はダミーの0を入れなかった場合
    // ※ダミーの0を入れなかった場合は、上記の累積和計算時のインデックスも修正の必要がある(N+1→N)
    // auto accumu = L > 1 ? visitors[R - 1] - visitors[L - 2] : visitors[R
    // - 1];
    cout << accumu << endl;
  }
}

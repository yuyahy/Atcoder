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

  int N(0), M(0);
  cin >> N >> M;
  vector<int> A(N + 1, 0);
  map<int, int> mp;
  int tmp(0);
  // Memo: 本番中は問題文のチラ見しかできなかったが、
  //       翌日やったら普通に解けた。。。

  // Note:
  // 本問題のポイントは、i+1回目の投票で当選する人は以下のいずれかだけに限られること。
  //       1. i回目の投票で当選した人(当選者が変わらないパターン)
  //       2. i+1回目の投票で投票された人(当選者が新しい人に変わるパターン)
  //       よって、前回の当選者を1変数で、各候補者とその得票数を配列で管理しておき、後は上記の2人を比較して、
  //       必要に応じて当選者を更新していけば、O(N)で解ける

  // 現時点での得票数が最大のインデックス(=候補者の番号)とその得票数
  // より若い番号で更新するためにインデックスの初期値充分大きい値にしておく
  // ※一応自分の解答が以下だが、当選者が分かれば配列からその得票数も分かるため、
  //  実際にはpairではなく、当選者の番号だけ保持しておけばOK
  pair<int, int> max_pair({99999999999, 0});
  for (int i = 0; i < M; i++) {
    cin >> tmp;
    A[tmp] = A[tmp] + 1;
    // 1. 現時点で得票数最大の人が更に投票された場合、最大得票数が+1
    if (tmp == max_pair.first) {
      max_pair.second += 1;
    } else {
      if (A[tmp] > max_pair.second) {
        // 2.得票数の最大値が更新された場合、保持している最大値の情報を更新
        max_pair = {tmp, A[tmp]};
      } else if (A[tmp] == max_pair.second && tmp < max_pair.first) {
        // 3.得票数の最大値に追いついた人がでてきたかつ、その番号がより若い番号だった場合、
        //   保持している最大値の情報を更新
        max_pair = {tmp, A[tmp]};
      }
    }
    cout << max_pair.first << endl;
  }
  dump(mp);
  dump(A);
}

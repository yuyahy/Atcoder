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
  string S(""), edit_str("");
  cin >> S;
  dump(S);

  // 1つでも3つ同じ色が並んでいる所があれば、その両端から1マスずつずらして目的の配色にできる
  // 1つも3つ同じ色が並んでいる所がなければ、どう塗っても目的の配色にはできない
  //
  // Note:
  // 自分は思いつかなかったが、最後の一手は必ず同じ色が3つ並ぶ事を考えると、
  // それ以外のマスはどうやって塗れるかを考えると思いつくのかもしれない
  // →最初or最後の目的を達成するために必ず行う操作や状態から考えるのが良いのかも
  int continuous_cnt(0);
  char now_char = 'a';
  bool bCreatable(false);
  for (const auto& ch : S) {
    if (now_char != ch) {
      now_char = ch;
      continuous_cnt = 1;
    } else {
      continuous_cnt++;
    }
    if (continuous_cnt == 3) {
      bCreatable = true;
      break;
    }
  }
  auto res = bCreatable ? "Yes" : "No";
  cout << res << endl;
}

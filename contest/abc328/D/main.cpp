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
  // Github Actionsのテスト
  string str;
  cin >> str;
  // 先頭からi文字目までの文字列から"ABC"を削除した文字列
  vector<string> DP(str.length(), "");
  DP[0] = str;
  // Note:
  // 入力された文字列を先頭から探索→"ABC"が見つかったら削除という方針だと、
  // 探索にO(N)、"ABC"を削除した際に、std::string::erase()の内部で文字列を並べ直す処理にO(N)かかり、
  // 最悪O(N^2)かかり間に合わない。
  // よって、std::stackなどを用いてO(N)に計算回数を落とす工夫が必要になる
  // →後ろから"ABC"が追加された時点で都度削除すれば、それより前の要素を並べ直す時間はかからないので削除の仕方がポイント。
  std::stack<char> str_stack;
  dump(str_stack);
  // 先頭から探索すると、std::stackの性質上(先入れ先出し)、逆順で出力しないと文字列の順序が逆転してしまうため、
  // 逆順で探索する
  // Note: str.length()始まりにしてしまうと、エラーにならない &
  // 謎の空要素がpushされてしまうので注意
  for (int i = str.length() - 1; i >= 0; i--) {
    str_stack.push(str[i]);
    // 要素の追加ごとに"ABC"が含まれていないかチェックし、含まれている場合は削除する
    if (str_stack.size() >= 3 && str[i] == 'A') {
      // 先頭
      auto tmp_i = str_stack.top();
      str_stack.pop();
      // 2番目
      auto tmp_i_1 = str_stack.top();
      str_stack.pop();
      // 3番目
      auto tmp_i_2 = str_stack.top();
      str_stack.pop();
      // 先頭が"A"である事はチェック済みなので、残りの"BC"のみチェックする
      // →もし"ABC"になっていなければ詰め直す必要がある
      if (tmp_i_1 != 'B' || tmp_i_2 != 'C') {
        str_stack.push(tmp_i_2);
        str_stack.push(tmp_i_1);
        str_stack.push(tmp_i);
      }
    }
  }
  dump(DP);
  dump(str_stack);

  // 以下は最初に書いた方針だが、TLEした
  //   while (true) {
  //     auto pos = str.find("ABC");
  //     if (pos == string::npos) {
  //       break;
  //     } else {
  //       str = str.erase(pos, 3);
  //     }
  //   }
  while (!str_stack.empty()) {
    cout << str_stack.top();
    str_stack.pop();
  }
  cout << endl;
}

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

// 入力された数値がゾロ目(1もOK)かを判定する
bool IsSameNumbers(int num) {
  int y;

  /* １桁の場合、ゾロ目ではないので終了 */
  if (!(num / 10)) return true;

  y = num % 10; /* １の位を記憶 */
  while (true) {
    num /= 10; /* 10で割って桁を下げる。1234なら123になる。 */
    if (!num) break; /* 位が無くなると終了 */

    if (y != num % 10) /* １の位とXの位を比較。 */
      return false;    /* 違っていたら終了 */
  }
  return true;
}

// 入力された文字列が1種類の文字列で構成されているかを判定する
bool IsSameStrings(string str) {
  set<char> str_set;
  // for (int i = 0; i < str.length(); i++) {
  //   str_set.insert(str[i]);
  // }
  // return str_set.size() == 1 ? true : false;
  return (size(set<char>(str.begin(), str.end())) == 1);
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  vector<int> D(N + 1, 0);
  for (int i = 1; i <= N; i++) {
    cin >> D[i];
  }

  // 計算量がO(N*Di)で、条件より高々100^2 = 10000程度なので日付を全探索する
  // →月と日にちの内、それぞれゾロ目であるかをチェックし、ゾロ目の場合は月を構成する1種類の数字と日にちの1種類の数字が一致しているかチェックする
  // 他の解法としては、設問の条件から、ゾロ目の日付としてあり得る物を全列挙しておき(今回は36通り)、その内入力値の日付の範囲内に含まれる物が何個あるかをカウントする方法がある
  //
  // ある数値がゾロ目かどうかは以下の2種類の方法でチェックできる
  // 1.
  // 10で割れるだけ割り、その余りを見て1桁目と全て一致していればゾロ目(1桁の数値はすべてゾロ目として扱う)
  // 2.
  // 月と日にちを文字列に変換 &
  // 結合し、それが1種類の文字列で構成されているかチェックする(std::setの長さが1ならゾロ目)
  int sum(0);
  bool bUseIsSameNumbers(false);
  for (int i = 1; i <= N; i++) {
    if (bUseIsSameNumbers) {
      if (!IsSameNumbers(i)) continue;
      string str1 = to_string(i);
      for (int j = 1; j <= D[i]; j++) {
        if (!IsSameNumbers(j)) continue;
        string str2 = to_string(j);
        // ここに到達している時点で月と日にちがゾロ目であることは確定しているので、
        // 適当な桁から一文字だけ抽出して同じか比較する
        bool bMatch = str1[0] == str2[0] ? true : false;
        if (bMatch) sum++;
      }
    } else {
      string str1 = to_string(i);
      for (int j = 1; j <= D[i]; j++) {
        string str2 = to_string(j);
        auto month_day = str1 + str2;
        if (IsSameStrings(month_day)) sum++;
      }
    }
  }
  cout << sum << endl;
}

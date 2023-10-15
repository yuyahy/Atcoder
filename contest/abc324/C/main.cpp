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
  string T_(""), S("");
  cin >> N >> T_;
  vector<int> vec_str;

  // Note: 本番では正規表現で比較する方針を採用し、サンプルケースは通ったが、
  // テストケースではほとんどTLE、いくつかREしていた
  // →std::regexはそんなに高速ではないらしく、特に構築に時間がかかるらしい
  //  今回は正規表現を使う場合は動的に表現を作成しなければいけないため、方針ミス
  //
  // Note:
  // std::stringの代入時のコピーは、文字列のサイズに比例して時間がかかるため、入力文字列が非常に長いケースではTLEになる
  //       入力値はstd::stringで受け取り、代入時はstd::string_viewで取り回すことで解消できる
  string_view longer_string(""), shorter_string("");
  int longer_size(0), shorter_size(0);
  int T_size = T_.size();

  for (int i = 0; i < N; i++) {
    bool bEqual = false;
    cin >> S;
    if (T_size >= (int)S.size()) {
      longer_string = T_;
      shorter_string = S;
    } else {
      longer_string = S;
      shorter_string = T_;
    }
    longer_size = (int)longer_string.size();
    shorter_size = (int)shorter_string.size();
    int prefix_same_cnt(0), suffix_same_cnt(0);

    for (int i = 0; i < shorter_size; i++) {
      if (shorter_string[i] == longer_string[i]) {
        prefix_same_cnt += 1;
      } else {
        break;
      }
    }
    for (int i = shorter_size - 1; i >= 0; i--) {
      if (shorter_string[i] ==
          longer_string[i + (longer_size - shorter_size)]) {
        suffix_same_cnt += 1;
      } else {
        break;
      }
    }

    if (prefix_same_cnt == suffix_same_cnt && prefix_same_cnt == shorter_size &&
        shorter_size == longer_size) {
      // 比較文字列が等しいケース
      bEqual = true;
    } else if (prefix_same_cnt + suffix_same_cnt >= shorter_size &&
               shorter_size == longer_size - 1) {
      // 文字列SがT′に対して、1文字過剰 or 1文字足りないケース
      bEqual = true;
    } else if (prefix_same_cnt + suffix_same_cnt == shorter_size - 1 &&
               shorter_size == longer_size) {
      // 文字列SがT′に対して、1文字だけ異なるケース
      bEqual = true;
    }

    // 以下は公式解答のPythonで書かれていた方のコードをC++で実装した物。
    // →shorter_string、longer_stringをstd::stringにすると、これらの代入時のコピーでTLEする
    //  よって、std::string_viewで代入時にコピーではなく参照で扱う様にしている
    // while (true) {
    //   //
    //   //
    //   比較文字列のサイズの差が1より大きい時点で、条件を満たさない事がわかる
    //   if (longer_size - shorter_size > 1) break;
    //   // 一文字の不足、過剰、置き換えは許容できるので、
    //   // それをチェックしていく
    //   int miss_cnt(0);
    //   int i(0), j(0);
    //   while (i < int(shorter_size)) {
    //     if (shorter_string[i] != longer_string[j]) {
    //       miss_cnt += 1;
    //       if (miss_cnt > 1) break;
    //       j += 1;
    //       if (longer_size == shorter_size) {
    //         i += 1;
    //       }
    //     } else {
    //       i += 1;
    //       j += 1;
    //     }
    //   }
    //   if (miss_cnt <= 1) bEqual = true;
    //   break;
    // }
    if (bEqual) vec_str.push_back(i);
  }
  int vec_size = vec_str.size();
  cout << vec_size << '\n';
  for (int i = 0; i < vec_size; i++) {
    if (i != vec_size - 1) {
      cout << vec_str[i] + 1 << " ";
    } else {
      cout << vec_str[i] + 1 << '\n';
    }
  }
}

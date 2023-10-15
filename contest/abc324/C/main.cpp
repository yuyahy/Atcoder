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
#include <regex>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;
// ￥

bool is_insert(string T, string S) {
  for (int i = 0; i < T.size(); i++) {
    auto del_str = T;
    del_str.insert(i, "[a-z]");
    if (regex_match(S, regex(del_str))) {
      return true;
    }
  }
  return false;
}

bool is_delete(string T, string S) {
  for (int i = 0; i < T.size(); i++) {
    auto tmp = T;
    auto del_str = tmp.erase(i, 1);
    if (del_str == S) {
      return true;
    }
  }
  return false;
}

bool is_change(string T, string S) {
  for (int i = 0; i < T.size(); i++) {
    auto tmp = T;
    auto del_str = tmp.erase(i, 1);
    del_str.insert(i, "[a-z]");
    // dump(del_str);
    if (regex_match(S, regex(del_str))) {
      return true;
    }
  }
  return false;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  int N(0);
  string T_(""), S("");
  cin >> N >> T_;
  //   dump(N);
  //   dump(T_);
  vector<int> vec_str;
  for (int i = 0; i < N; i++) {
    bool bEqual = false;
    cin >> S;
    // 1. 等しいか
    while (true) {
      if (S == T_) {
        bEqual = true;
        break;
      } else if (is_insert(T_, S)) {
        // 2. 先頭〜末尾に一個追加して等しいか
        bEqual = true;
        break;
      } else if (is_delete(T_, S)) {
        // 3. いずれか一文字を削除して等しいか
        bEqual = true;
        break;
      } else if (is_change(T_, S)) {
        // 4. いずれか一文字を変更すると等しいか
        bEqual = true;
        break;
      }
      break;
    }
    if (bEqual) vec_str.push_back(i);
  }
  cout << vec_str.size() << endl;
  sort(vec_str.begin(), vec_str.end());
  //   for (const auto& str_ : vec_str) {
  //     cout << str_ + 1 << " ";
  //   }
  for (int i = 0; i < vec_str.size(); i++) {
    if (i != vec_str.size() - 1) {
      cout << vec_str[i] + 1 << " ";
    } else {
      cout << vec_str[i] + 1 << endl;
    }
  }
}

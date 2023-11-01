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
  string S(""), T("");
  cin >> S >> T;

  // マス(i, j)に到達するまでに通る斜めの線の本数の最大値
  // Note: 縦軸と横軸にそれぞれ比較対象の文字列を配置した表を考えるのがポイント
  vector<vector<ll>> DP(S.length() + 1, vector<ll>(T.length() + 1, 0));
  for (int i = 1; i < int(S.length()) + 1; i++) {
    for (int j = 1; j < int(T.length()) + 1; j++) {
      // Sのi文字目とTのj文字目が一致するパターンとi文字目とTのj文字目が一致しないパターンに大別できる
      // ※端で左 or 上の値が使用できないケースもある事に注意
      auto DP_Left = i - 1 >= 0 ? DP[i - 1][j] : 0;
      auto DP_Upper = j - 1 >= 0 ? DP[i][j - 1] : 0;
      auto DP_UpperLeft = i - 1 >= 0 && j - 1 >= 0 && S[i - 1] == T[j - 1]
                              ? DP[i - 1][j - 1] + 1
                              : 0;
      DP[i][j] = std::max({DP_Left, DP_Upper, DP_UpperLeft});
    }
  }
  dump(DP);
  // Github Actionsのテスト
  cout << DP[S.length()][T.length()] << endl;
}

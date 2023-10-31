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
  dump(S);
  dump(T);

  // 文字列Sのi番目までと文字列Tのj番目までを比較した際のレーベンシュタイン距離の最小値
  vector<vector<ll>> DP(S.length() + 1,
                        vector<ll>(T.length() + 1, 1000000000000));
  DP[0][0] = 0;
  for (int i = 1; i < int(T.length() + 1); i++) {
    DP[0][i] = i;
  }
  for (int i = 1; i < int(S.length() + 1); i++) {
    DP[i][0] = i;
  }
  for (int i = 1; i < int(S.length()) + 1; i++) {
    for (int j = 1; j < int(T.length()) + 1; j++) {
      // Sのi文字目とTのj文字目が一致するパターンとi文字目とTのj文字目が一致しないパターンに大別できる
      // ・Sのi文字目とTのj文字目(=部分文字列の末尾)が一致するパターン→末尾がなくても編集距離は同じなので、表の左上(両方とも末尾が一文字ない場合)のマス目と同じ編集距離
      // ・Sのi文字目とTのj文字目(=部分文字列の末尾)が一致しないパターン→何らかの操作を一回しないと同じ文字列にはならないので、表で隣接している、
      //                                                       　左 or 上 or
      //                                                       左上のマス目+1回の編集が必要
      // ※端で左 or上の値が使用できないケースもある事に注意
      auto DP_Left = i - 1 >= 0 ? DP[i - 1][j] + 1 : 1000000000000;
      auto DP_Upper = j - 1 >= 0 ? DP[i][j - 1] + 1 : 1000000000000;
      auto DP_UpperLeft = i - 1 >= 0 && j - 1 >= 0 && S[i - 1] == T[j - 1]
                              ? DP[i - 1][j - 1]
                              : DP[i - 1][j - 1] + 1;
      DP[i][j] = std::min({DP_Left, DP_Upper, DP_UpperLeft});
    }
  }
  dump(DP);
  cout << DP[S.length()][T.length()] << endl;
}
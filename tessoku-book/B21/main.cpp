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
  ll N(0);
  cin >> N;
  string S("");
  cin >> S;
  dump(N);
  dump(S);

  // 文字列Sのl文字目からr文字目までを探索範囲としたときに、最大何文字の回文が作れるか
  vector<vector<ll>> DP(N, vector<ll>(N, 0));
  // 初期状態
  // 後述のDPテーブルの更新では処理しないケースを先に初期値を入れる
  // 今回は、両端を1広げると回文だったケースは、「拡張前の最長の回文の文字数」+2と分かるが、
  // この更新の仕方だと少なくとも3つの文字が存在する事になり、2文字かつ同じ文字のパターンが漏れてしまう

  // 1文字だけ選ぶ場合
  for (ll i = 0; i < N; i++) {
    DP[i][i] = 1;
  }
  // 2文字選ぶ場合
  // ※2文字選ぶ場合は、同じ文字でなければいけない
  for (ll i = 0; i < N - 1; i++) {
    if (S[i] == S[i + 1]) {
      DP[i][i + 1] = 2;
    } else {
      DP[i][i + 1] = 1;
    }
  }

  // 1文字だけのパターン、2文字のパターンは初期値で求めているので、文字3つのパターンから処理していく
  // ※探索範囲を広げてDPテーブルを更新していく都合上、先に狭い範囲から求めていく必要あり
  // Note:
  // 任意の文字を取り除けるため、拡張した探索範囲の両端にのみ着目すれば良い

  // 探索範囲の長さ
  // ※そのまま左側のインデックスに足しているので、実際はlen+1が探索範囲になる
  for (int len = 2; len < N; len++) {
    for (int left = 0; left < N - len; left++) {
      auto right = left + len;
      // DP[left][right]に遷移するパターンは以下のとおり
      // ・DP[left+1][right]から左に一文字広げる
      // ・DP[left][right-1]から右に一文字広げる
      // ・DP[left+1][right-1]から両端を一文字ずつ広げる(両端が同じ文字である必要あり)
      if (S[left] == S[right]) {
        DP[left][right] = std::max({DP[left + 1][right], DP[left][right - 1],
                                    DP[left + 1][right - 1] + 2});
      } else {
        DP[left][right] = std::max({DP[left + 1][right], DP[left][right - 1]});
      }
    }
  }
  dump(DP);
  cout << DP[0][N - 1] << endl;
}

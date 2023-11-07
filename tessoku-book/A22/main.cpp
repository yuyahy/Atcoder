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
  constexpr ll score_A(100);
  constexpr ll score_B(150);

  ll N(0);
  cin >> N;
  vector<ll> A(N + 1, 0), B(N + 1, 0);
  ll tmp(0);
  for (ll i = 1; i < N; i++) {
    cin >> A[i];
  }
  for (ll i = 1; i < N; i++) {
    cin >> B[i];
  }
  dump(A);
  dump(B);
  dump(A_map);
  dump(B_map);
  // マスiにたどりつくまでの、スコアの最大値
  vector<ll> DP(N + 1, 0);
  // Note: 全てのマスにたどり着く行動パターンが存在するとは限らないので、
  //        初期値は0ではなく、充分に小さい値にしておく必要がある(これをやらないと一部ケースでWA)
  // →0初期化だと、DPテーブル更新の際に、実際には存在しない移動が最大値になってしまうケースがあるため、
  // 行動で得られるスコアよりもかなり小さい値にしておく
  for (int i = 2; i <= N; i++) {
    DP[i] = -1000000000000;
  }

  // Note:今までは最後の行動に対して場合わけしていたが(=貰う遷移形式)、
  //      動的計画法はその限りではなく、一手先の行動を考えてテーブルを更新していくのもOK
  //      これを「配る遷移形式」と呼ぶ
  for (int i = 1; i < N; i++) {
    DP[A[i]] = std::max(DP[A[i]], DP[i] + score_A);
    DP[B[i]] = std::max(DP[B[i]], DP[i] + score_B);

    // 以下は元々考えていた方針
    // →貰う遷移形式の考え方で、おそらく間違ってはいないが、
    // あるマスに辿りつく直前の行動を自分で管理する実装を行わないといけない。
    // →直前の行動は入力値からは知ることができないため

    // 最終マスから、選択できる行動の内、スコアが大きい手段を使って戻る
    // ※ただし、必ずそのマスにたどり着く手段があるとは限らない
    // 1. マスXから行動Aのみマスiにたどり着ける→DP[X] + 100
    // 2. マスYから行動Bのみマスiにたどり着ける→DP[Y] + 150
    // 3. マスX、Yの両方からマスiにたどり着ける→std::max(DP[X] + 100, DP[Y] +
    // 150)
    // 4. そのマスにたどりつく手段がない→0 or 適当な最小値
  }
  dump(DP);
  cout << DP[N] << endl;
}

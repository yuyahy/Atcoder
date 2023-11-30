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

// 終了時刻の早い順に昇順ソート
// 一応終了時刻が等しい場合は、上映時間が短い物が早いインデックスになるようにしている
// ※特に意味はないかもしれない
bool custom_comp(pair<int, int>& left, pair<int, int>& right) {
  if (left.second == right.second) {
    return (left.second - left.first) < (right.second - right.first);
  } else {
    return left.second < right.second;
  }
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  vector<int> L(N, 0), R(N, 0);
  vector<pair<int, int>> movies;
  for (int i = 0; i < N; i++) {
    cin >> L[i] >> R[i];
    movies.push_back({L[i], R[i]});
  }
  dump(L);
  dump(R);
  dump(movies);
  // 本問題は終了時刻の早い物から取っていくと正解にたどり着くが、
  // 愚直に一個選ぶ→次に最も早い映画を探す→更に次に最も早い映画を探す...
  // とすると最悪O(N*見る映画の数)になり間に合わない。
  // あらかじめ映画を終了時刻の早い順にソートしておけば、
  // 次のインデックスの映画が取れればとる、更に次のインデックスの映画が取れればとる
  // を繰り返す事でループをN回まわすだけ答えが求められる
  sort(movies.begin(), movies.end(), custom_comp);
  dump(movies);

  // 貪欲法で終了時刻の最も早い物を選択していくと、正解にたどり着く
  auto current_movie_end_time(movies[0].second);
  auto movie_cnt(1);
  for (int i = 1; i < N; i++) {
    // 取れる映画の場合は取り、終了時刻を更新
    if (movies[i].first >= current_movie_end_time) {
      movie_cnt++;
      current_movie_end_time = movies[i].second;
    }
  }
  cout << movie_cnt << endl;
}

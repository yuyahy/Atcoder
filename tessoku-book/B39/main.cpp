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

// スコアの高い順に降順でソート
// ※もしスコアが等しい物がある場合はその中で昇順にする
bool custom_comp(pair<int, int>& left, pair<int, int>& right) {
  if (left.second == right.second) {
    return right.first > left.first;
  } else {
    return left.second > right.second;
  }
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  ll N(0), D(0), X(0), Y(0);
  cin >> N >> D;
  vector<pair<int, int>> jobs;
  for (int i = 0; i < N; i++) {
    cin >> X >> Y;
    jobs.push_back({X, Y});
  }
  dump(jobs);
  // スコア順に並べる
  sort(jobs.begin(), jobs.end(), custom_comp);
  dump(jobs);

  // スコアの高い順に仕事できる場合は仕事する
  vector<ll> job_list(D + 1, 0);
  for (int i = 0; i < N; i++) {
    // その仕事の解禁日が空いていればやる
    if (job_list[jobs[i].first] == 0) {
      job_list[jobs[i].first] = jobs[i].second;
    } else {
      // jobs[i].first以降の日で空いている日がないかチェック
      for (int j = jobs[i].first + 1; j < D + 1; j++) {
        // 空いている日があった場合は、その中の一番最初の日付にその仕事をやる
        if (job_list[j] == 0) {
          job_list[j] = jobs[i].second;
          break;
        }
      }
    }
  }
  ll sum = std::accumulate(job_list.begin(), job_list.end(), 0);
  dump(job_list);
  cout << sum << endl;
}

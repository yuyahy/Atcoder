// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++(i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++(i))
#define REP_R(i, n) for (int i = (int)(n)-1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))
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

  // スコアの高い順に降順で並び替えるqueue
  priority_queue<int> items;
  // i日目からできる仕事のmap
  map<int, vector<int>> job_map;

  for (int i = 0; i < N; i++) {
    cin >> X >> Y;
    jobs.push_back({X, Y});
    job_map[X].push_back(Y);
  }
  dump(items);

  bool bUsePriorityQueue(true);
  if (bUsePriorityQueue) {
    int max(0);
    // i+1日目ごとにできる仕事を優先度付きキューにつめる
    // Note: 入力値の受け取り時にキューにつめると、一部ケースでTLEする
    //       要素数が多くなるほど、挿入の度に並び替えるコストが発生するせいかもしれない
    //       ソートでも挿入の度にやるより、要素を一通り入れてから一回だけソートした方が速いのと同じ？
    REP(i, D) {
      for (const auto& job : job_map[i + 1]) {
        items.push(job);
      }
      if (items.empty()) continue;
      auto salary = items.top();
      max += salary;
      items.pop();
    }
    cout << max << endl;
  } else {
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
}

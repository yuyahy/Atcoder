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
  int N(0), Q(0);
  cin >> N;
  vector<int> accum_win_vector;
  accum_win_vector.push_back(0);
  for (int i = 0; i < N; i++) {
    int tmp = 0;
    cin >> tmp;
    accum_win_vector.push_back(tmp);
  }
  // 累積和を求める
  for (int i = 1; i < N + 1; i++) {
    accum_win_vector[i] += accum_win_vector[i - 1];
  }

  int L(0), R(0);
  cin >> Q;
  // 質問に回答する
  for (int i = 0; i < Q; i++) {
    cin >> L >> R;
    string result_str("");
    // 始めに配列にダミーの0を挿入しているため、
    // 最初のインデックスの考慮と、「L回目」、「R回目」を-1してインデックスに対応させる
    // 計算が不要になる
    auto win_cnt = accum_win_vector[R] - accum_win_vector[L - 1];
    auto lose_cnt = R - L + 1 - win_cnt;
    if (win_cnt > lose_cnt) {
      result_str = "win";
    } else if (lose_cnt > win_cnt) {
      result_str = "lose";
    } else {
      result_str = "draw";
    }
    cout << result_str << endl;
  }
}

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

int search_neighbor(vector<vector<int>>& grids, int i, int j, int& cnt) {
  // 8近傍を探す
  // 右
  //   dump(i);
  //   dump(j);
  grids[i][j] = 0;

  for (int k = -1; k < 2; k++) {
    if (i + k < 0 || i + k > grids.size() - 1) continue;
    for (int l = -1; l < 2; l++) {
      if (k == 0 && l == 0) continue;
      if (j + l < 0 || j + l > grids[0].size() - 1) continue;
      if (grids[i + k][j + l] == 1) {
        cnt++;
        search_neighbor(grids, i + k, j + l, cnt);
      }
    }
  }

  //   if (i - 1 >= 0 && grids[i - 1][j] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i - 1, j, cnt);
  //   }
  //   //   左
  //   if (i + 1 < grids.size() && grids[i + 1][j] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i + 1, j, cnt);
  //   }
  //   // 上
  //   if (j + 1 < grids[0].size() && grids[i][j + 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i, j + 1, cnt);
  //   }
  //   //  下
  //   if (j - 1 >= 0 && grids[i][j - 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i, j - 1, cnt);
  //   }
  //   // 右上
  //   if (i - 1 >= 0 && j + 1 < grids[0].size() && grids[i - 1][j + 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i - 1, j + 1, cnt);
  //   }
  //   // 左上
  //   if (i + 1 < grids.size() && j + 1 < grids[0].size() &&
  //       grids[i + 1][j + 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i + 1, j + 1, cnt);
  //   }
  //   // 右下
  //   if (i - 1 >= 0 && j - 1 >= 0 && grids[i - 1][j - 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i - 1, j - 1, cnt);
  //   }
  //   // 左下
  //   if (i + 1 < grids.size() && j - 1 >= 0 && grids[i + 1][j - 1] == 1) {
  //     cnt++;
  //     search_neighbor(grids, i + 1, j - 1, cnt);
  //   }
  return 0;
}

int main() {
  // TODO 競プロの教訓をまとめておく
  // set precision (10 digit)
  cout << setprecision(10);
  int H(0), W(0);
  cin >> H >> W;
  //   vector<vector<string>> grids(H, vector<string>(W, ""));
  //   vector<string> grids(H, "");
  vector<vector<int>> grids(H, vector<int>(W, 0));
  //   char ch = '#';
  int sensors = 0;
  for (int i = 0; i < H; i++) {
    string str;
    cin >> str;
    // for (int j = 0; j < W; j++) {
    //   string tmp("");
    //   cin >> tmp;
    //   grids[i][j] = tmp;
    // }
    for (int j = 0; j < int(str.length()); j++) {
      auto num = str[j] == '#' ? 1 : 0;
      if (num == 1) sensors++;
      grids[i][j] = num;
    }

    // sensors += std::count(grids[i].begin(), grids[i].end(), 1);
  }
  //   dump(grids);
  //   dump(sensors);
  int res(0);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      int cnt(0);
      //   if (grids[i][j] == 1) {
      search_neighbor(grids, i, j, cnt);
      //   }
      if (cnt > 0) res++;
    }
  }
  cout << res << endl;
}

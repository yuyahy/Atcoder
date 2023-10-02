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

// ※以下は公式回答を参考に、自分の理解を深めるために一部実装や関数名の変更、コメントの追加を行っている

// ポリオミノを右に90度回転させる
vector<string> rotateVector90Angle(const vector<string>& vec) {
  auto rotate_vec = vec;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      rotate_vec[3 - j][i] = vec[i][j];
    }
  }
  return rotate_vec;
}

// 指定座標がグリッド内に収まっているかを判定する
bool is_inside_grid(int x, int y) { return 0 <= x && x < 4 && 0 <= y && y < 4; }

// (x, y)を左上としてポリオミノが配置できるかチェックする
bool is_enable_assign(const vector<string>& poly_vec,
                      vector<vector<int>>& exist_poly, int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (poly_vec[i][j] != '#') continue;
      auto x_ = i + x;
      auto y_ = j + y;
      // グリッド内に収まるか
      if (!is_inside_grid(x_, y_)) return false;
      // すでに配置されているポリオミノに重ならないか
      if (exist_poly[x_][y_] == 1) return false;
      // 配置フラグをたてる
      exist_poly[x_][y_] = 1;
    }
  }
  return true;
}

// ポリオミノを再帰的に配置できるかチェックする
bool assign_polyomino(const vector<vector<string>>& poly_vec,
                      const vector<vector<int>>& exist_poly, int depth) {
  if (depth == 3) {
    int result = 1;
    for (const auto& exist : exist_poly) {
      for (const auto& is_exist : exist) {
        // グリッド内の配置フラグが全てたっているか(=隙間なく配置できたか)をチェックする
        result &= is_exist;
      }
    }
    return result ? true : false;
  }
  bool isAssignComplete = false;
  // 4✕4マスなので、考えられる移動量は上下左右共に[-3, 3]
  for (int i = -3; i <= 3; i++) {
    for (int j = -3; j <= 3; j++) {
      auto exist = exist_poly;
      bool can_assign = is_enable_assign(poly_vec[depth], exist, i, j);
      if (!can_assign) continue;
      // ポリオミノを配置できた場合は再帰
      if (assign_polyomino(poly_vec, exist, depth + 1)) {
        isAssignComplete = true;
        break;
      }
      if (isAssignComplete) break;
    }
    if (isAssignComplete) break;
  }
  return isAssignComplete;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  // ポリオミノ✕3ごとの入力形状
  vector<vector<string>> poly_vec(3);
  for (int i = 0; i < 3; i++) {
    poly_vec[i].resize(4);
    for (auto& s : poly_vec[i]) {
      cin >> s;
    }
  }

  // 右方向に90度回転 & 上下左右に1マスずつ平行移動のケースを全探索し、
  // グリッドにポリオミノを敷き詰められるか判定する
  bool bAbleAssign = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (assign_polyomino(poly_vec, vector(4, vector(4, 0)), 0)) {
        // 並べ切れた時点で探索終了
        bAbleAssign = true;
        break;
      }
      poly_vec[2] = rotateVector90Angle(poly_vec[2]);
    }
    if (bAbleAssign) break;
    poly_vec[1] = rotateVector90Angle(poly_vec[1]);
  }
  std::string result_str = bAbleAssign ? "Yes" : "No";
  cout << result_str << endl;
}

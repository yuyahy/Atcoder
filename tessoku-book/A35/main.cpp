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

struct Node {
  // 所属階層
  int level;
  // 自分の右下、左下のノードのポインタ
  Node* left;
  Node* right;
  // 自分のスコア
  double score;
};

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  vector<int> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  dump(A);

  // Note:本問題は、取れる選択肢がブロックごとに2通りしかないので、
  //      動的計画法を用いて、ピラミッドの最下層から最善を尽くした時をシミュレーションする

  // 局面(i, j)の時にお互い最善行動をした時のスコア
  vector<vector<int>> DP(N, vector<int>(N, 0));
  // 初期状態
  for (int i = 0; i < N; i++) {
    DP[N - 1][i] = A[i];
  }

  for (int i = N - 2; i >= 0; i--) {
    for (int j = 0; j < N - 1; j++) {
      // 太郎と次郎のどちらのターンかによって、遷移が変わるので注意
      if (i % 2 == 0) {
        DP[i][j] = std::max(DP[i + 1][j], DP[i + 1][j + 1]);
      } else {
        DP[i][j] = std::min(DP[i + 1][j], DP[i + 1][j + 1]);
      }
    }
  }

  cout << DP[0][0] << endl;

  // 以下は最初思いついたアイデア。
  // ツリーを作り、右下と左下のブロックの平均を取ったスコアを一個上のブロックのスコアにするという方針でやったが、
  // 一般性がなく、一部のテストケースでエラーになった。

  // ツリーをつくる
  // <階層、その階層のノードの配列>
  //   std::map<int, vector<Node>> pyramid;
  //   for (int i = N - 1; i >= 0; i--) {
  //     auto nodes_in_level = i + 1;
  //     vector<Node> Nodes;

  //     if (i == N - 1) {
  //       // 最下段の場合
  //       for (int j = 0; j < N; j++) {
  //         Node node = {i, nullptr, nullptr, A[j]};
  //         Nodes.push_back(node);
  //       }
  //       pyramid[i] = Nodes;
  //       dump(Nodes.size());
  //       dump(N);
  //       dump(i);
  //     } else {
  //       // 最下段以外の場合
  //       int upper_idx(0);
  //       auto upper_vec = pyramid[i + 1];
  //       for (int j = 0; j < nodes_in_level; j++) {
  //         // Node node = {
  //         //     i, &upper_vec[upper_idx], &upper_vec[upper_idx + 1],
  //         //     (upper_vec[upper_idx].score + upper_vec[upper_idx +
  //         1].score) /
  //         //     2};
  //         auto left =
  //             new Node{upper_vec[upper_idx].level, upper_vec[upper_idx].left,
  //                      upper_vec[upper_idx].right,
  //                      upper_vec[upper_idx].score};

  //         auto right = new Node{
  //             upper_vec[upper_idx + 1].level, upper_vec[upper_idx + 1].left,
  //             upper_vec[upper_idx + 1].right, upper_vec[upper_idx +
  //             1].score};
  //         Node node = {
  //             i, left, right,
  //             (upper_vec[upper_idx].score + upper_vec[upper_idx + 1].score) /
  //             2};
  //         Nodes.push_back(node);
  //         upper_idx++;
  //       }
  //       pyramid[i] = Nodes;
  //     }
  //   }
  //   dump(pyramid);
  //   auto elem = pyramid[1];
  //   dump(elem[0].right->score);

  //   // トップからたどる
  //   bool bTaro(true);
  //   int score(-1);
  //   auto tmp = pyramid[0];
  //   Node* result = &tmp[0];
  //   for (int i = 0; i < N - 1; i++) {
  //     dump(bTaro);
  //     if (bTaro) {
  //       result = result->left->score > result->right->score ? result->left
  //                                                           : result->right;
  //     } else {
  //       result = result->left->score > result->right->score ? result->right
  //                                                           : result->left;
  //     }
  //     bTaro = !bTaro;
  //   }

  //   cout << result->score << endl;
  // メモリリークするので、一応解放しておく(Atcoderだからメモリリークしても関係はなさそうだが)
  //   for (int i = 0; i < N; i++) {
  //     auto level = pyramid[i];
  //     for (auto elem : level) {
  //       delete elem.right;
  //       delete elem.left;
  //     }
  //   }
}

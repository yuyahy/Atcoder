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

  int N(0);
  cin >> N;
  string S("");
  cin >> S;
  dump(S);

  // この問題は、単純にDPで、高さが0未満になった場合遡って条件を満たす様に加算していく方針だと、
  // サンプルケースは解けるが、テストケースがほぼ失敗する
  // 理由としては、この方針だとABが連続しているケースで最小値が得られないため
  // e.g. N=8, S=AABABBBのケース
  // 上記の方針でやると、以下が得られる
  // ・[ 1, 2, 3, 2, 4, 3, 2, 1 ]
  // 一見良さげだが、実は4番目(先頭を1とすると)は3番目と5番目の両方より高さが低くなるのが、
  // 条件のため、2ではなく1が最小値として適切。
  // →動的計画法の適用条件として、各ステップの最適解が全体の最適解となるという条件があるが、
  //  本設問は上記の様に、何が求める答えかは全ての大小関係の条件を考慮する必要があるので、
  //  各遷移が全体の条件を考慮すると、最適解になっていない可能性がある
  // (後はある条件だったら遡って過去のテーブルを更新する、というのはDPぽくはないかも)

  // 本設問はABC329のC問題と似た感じで、以下の方針で解ける
  // 1. 先頭から探索し、条件Aに該当する部分の最小値を更新する
  // 2. 末端から探索し、条件Bに該当する部分の最小値を更新する
  //    末端から探索する事で、先頭から探索して、Bがでたら-1して...的な事を考えなくて済むのがポイント
  // 3. 1、2それぞれで計算した最小値のmaxを取ったものが求める答え

  // 条件A(<)の最小値を求める
  vector<int> A(N, 1);
  int continuous_cnt_A(1);
  for (int i = 0; i < N - 1; i++) {
    if (S[i] == 'A') {
      A[i + 1] += continuous_cnt_A;
      continuous_cnt_A++;
    } else {
      continuous_cnt_A = 1;
    }
  }
  dump(A);
  // 条件B(>)の最小値を求める
  vector<int> B(N, 1);
  int continuous_cnt_B(1);
  for (int i = N - 2; i >= 0; i--) {
    if (S[i] == 'B') {
      B[i] += continuous_cnt_B;
      continuous_cnt_B++;
    } else {
      continuous_cnt_B = 1;
    }
  }
  dump(B);

  // 条件AとBで求めた最小値の内、大きい方を全体の最小値とする
  // →大きい方であればもう一方の条件も満たすため
  vector<int> result(N, 0);
  for (int i = 0; i < N; i++) {
    result[i] = std::max(A[i], B[i]);
  }

  auto sum = std::reduce(std::begin(result), std::end(result));
  cout << sum << endl;
}

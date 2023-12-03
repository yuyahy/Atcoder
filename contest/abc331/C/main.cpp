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
  vector<ll> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  bool bMyAnswer(false);
  if (bMyAnswer) {
    // 実際に自分が本番中に提出した方針
    // 1. Aをコピーしソート
    // 2. mapで「key=Aのある整数、value=Aの内、key以下の要素の和」を求める
    // 3.各クエリで、「Aの総和」-「配列中のAi以下の要素の和」を計算し解答する
    // (逆順に求めておくと引く必要はなくなる)
    // ※この問題では、Aの中に同じ数が複数回出現するパターンが存在するため、Aiと和に関する対応関係を作る必要がある(今回はmapを採用)

    auto A_sort = A;
    sort(A_sort.begin(), A_sort.end());
    dump(A);
    dump(A_sort);
    vector<ll> number_sum;

    // ある数未満の和のmap
    map<ll, ll> number_cnt;
    ll sum(A_sort[0]);
    number_cnt[A_sort[0]] = A_sort[0];
    for (int i = 1; i < N; i++) {
      // 今見ている数字が変わるタイミングで、そこまでの累積和を初期代入する
      if (number_cnt.count(A_sort[i]) == 0) {
        number_cnt[A_sort[i]] = number_cnt[A_sort[i - 1]];
        number_cnt[A_sort[i]] += A_sort[i];
      } else {
        number_cnt[A_sort[i]] += A_sort[i];
      }
      sum += A_sort[i];
    }
    dump(number_cnt);
    dump(sum);

    for (int i = 0; i < N; i++) {
      if (i == N - 1) {
        cout << sum - number_cnt[A[i]] << endl;
      } else {
        cout << sum - number_cnt[A[i]] << " ";
      }
    }
  } else {
    // Note:
    // 以下の解法はローカルだとTLEになるが、Atcoder上でソースを貼り付けると通る
    //       →おそらくコンパイルオプションによって遅くなっている
    // 別解(ソートしない)
    // 1.mapで「key=Aのある整数、value=Aの内、Aが出現するインデックスの配列」を求める
    //    →上記の通り最終的に各Aiに対して回答を行う必要があるため、この情報を持っておく
    // 2.本設問の条件より、[1, 10^6]内の整数について、"降順"で以下を行う
    //   → 今見ている整数よりも大きい数の和をその数に対する答えとして記録
    //   → {今見ている数} ×
    //   {その数が配列Aで出現する回数}を現在の和に足し込む(寄与)
    //
    // 本方針はソートする必要がないのと、実装が上記の方針と比較するとシンプルという特徴がある
    // 「ある整数とその数が出現するインデックス」を管理するのがポイント。インデックスの個数が分かれば、出現回数が分かり、
    //  出現回数が分かれば、その数が全体の和に寄与する量も分かる
    map<ll, vector<ll>> index_map;
    for (ll i = 0; i < N; i++) {
      index_map[A[i]].push_back(i);
    }
    // 設問よりAiはここまで見れば充分なはず。
    // ※不安であれば+5くらいしても良い
    constexpr ll MAX(1e6);
    // <Aの中のある数, keyより大きい数の和>map
    map<ll, ll> sum_map;
    ll accum_sum(0);
    for (ll i = MAX; i >= 1; i--) {
      // Note: 今回求めるのはAi"より"大きい数の和なので、Aiを含めない事に注意
      //       よってAiを和に足し込む前にあるAiに対応する答えを代入しておく
      sum_map[i] = accum_sum;
      // 各整数とAの中で出現した回数
      accum_sum += i * (ll)index_map[i].size();
    }
    for (ll i = 0; i < N; i++) {
      if (i == N - 1) {
        cout << sum_map[A[i]] << endl;
      } else {
        cout << sum_map[A[i]] << " ";
      }
    }
  }
}
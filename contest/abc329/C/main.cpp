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

  // Note: 本問題を部分文字列をstd::setに突っ込み(重複チェック)、最終的に
  //       集合内の個数を解答する方針でやったが、TLE & MLEが発生した
  //       おそらく、文字列長が長くなると、setだとそれなりに処理時間がかかってしまうためと思われる
  //       本番中に気がつくのが遅すぎたが、今回は「各アルファベットが最大何文字連続しているか」を
  //       mapなどで管理し、最終的に足し合わせる方針でやればよかった。
  //       →そうすると、長い文字列を保持する必要もないし、mapのキーも最大26個(=アルファベット1文字のバリエーション)
  //        なので、メモリも問題なくなる

  //  各アルファベット1文字が最大何回連続して出現するかを管理するmap
  map<string, int> same_continuous_map;
  same_continuous_map.insert({string{S[0]}, 1});
  int same_continuous_cnt(1);

  for (int i = 1; i < N; i++) {
    if (S[i] != S[i - 1]) {
      // 直前と異なる場合
      same_continuous_cnt = 1;
      same_continuous_map[string{S[i]}] =
          std::max(same_continuous_map[string{S[i]}], same_continuous_cnt);
    } else {
      // 直前と同じ文字の場合は最大値を更新する
      same_continuous_cnt++;
      same_continuous_map[string{S[i]}] =
          std::max(same_continuous_map[string{S[i]}], same_continuous_cnt);
    }
    dump(same_continuous_map);
  }
  int sum(0);
  for (const auto& mp : same_continuous_map) {
    sum += mp.second;
  }
  cout << sum << endl;
}


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

// class RollingHash {
//  private:
//   vector<int> m_digit_string;

// }

// // TODO:クラスにまとめた方が良いかも
// //      それぞれ必要な配列はメンバで保持する
// //      部分文字列のハッシュ値はメンバ関数で返す
// auto calc_rolling_hash(const string& str, const int N, const int hash_base,
//                        const int mod) {
//   // 入力文字列のi番目の文字をcharからintに変換
//   // 0になると和差の計算上はあってもなくても変わらなくなってしまうので、
//   // a=1, b=2,...z=26と対応させる
//   vector<int> digit_string(N + 1, 0);
//   REP3(i, 1, N + 1) digit_string[i] = (str[i - 1] - 'a') + 1;
//   // 後の計算のためにB^iを前計算
//   using mint_hash = static_modint<mod>;
//   vector<mint_hash> hash_base_powers(N + 1, 0);
//   hash_base_powers[0] = 1;
//   REP3(i, 1, N + 1) {
//     dump(hash_base_powers[i - 1].val());
//     hash_base_powers[i] = hash_base_powers[i - 1] * hash_base;
//   }

//   // Hash(S[1,1]),Hash(S[1,2]),...Hash(S[1,N])を前計算
//   //   ここで、文字列S[1,i]はS[1,i-1]の後にT[i]を足した物なので、
//   // Hash(S[1,i]) = B*Hash(S[i,i-1])+T[i]
//   // ※ここで、B=B進法、T[i]=アルファベットのi番目を整数で表現した値
//   vector<mint_hash> hash(N + 1, 0);
//   REP3(i, 1, N + 1) hash[i] = (hash_base * hash[i - 1]) + digit_string[i];

//   for (const auto& elem : hash) dump(elem.val());
//   for (const auto& elem2 : hash_base_powers) dump(elem2.val());

//   // 指定区間[l,r]から文字列str[l,r]の部分のハッシュ値を求める
//   // ・Hash(S[l,r]) = Hash(S[1,r])-B^(r-l+1)*Hash(S[1,l-1])
//   auto calc_hash = [&](const ll l, const ll r) {
//     return hash[r] - (hash_base_powers[r - l + 1] * hash[l - 1]);
//   };
// }

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  ll N(0), Q(0);
  cin >> N >> Q;
  string str;
  cin >> str;

  // 愚直に部分文字列の比較をやるとTLEする
  // 以下の発想より、文字列を整数でハッシュ化して比較するとACできる
  //
  // 1. 文字列を切り出すのと、文字列の比較に時間がかかる
  // 特に文字列の比較は、一文字ずつ比較していく形になるので、O(N)かかる
  // 一方で、数値同士の比較はO(1)で行える(理由は以下)
  // ・固定型であるかぎり、その型で表現できる数字のビット長は固定(e.g.intであれば32)
  // ・ビット比較は各対応ビットが一致しているかのみを比較するため
  //
  // そのため、もし文字列をそれに対応する整数で置き換える事ができれば、比較にかかる処理速度は向上する
  //
  // 2.
  // ある文字列Sの[l,r]からなる部分文字列S[l,r]のハッシュ値は、事前に[1,1],[1,2]...[1,N]
  // を求めておけば、任意の[l,r]についてO(1)で求めることができる
  // ・Hash(S[l,r]) = Hash(S[1,r])-Hash(S[1,l])
  // →累積和系のアイデアに似ている

  // ハッシュ化に用いる基数
  constexpr int hash_base = 100;
  constexpr int mod = INT_MAX;

  // 入力文字列のi番目の文字をcharからintに変換
  // 0になると和差の計算上はあってもなくても変わらなくなってしまうので、
  // a=1, b=2,...z=26と対応させる
  vector<int> digit_string(N + 1, 0);
  REP3(i, 1, N + 1) digit_string[i] = (str[i - 1] - 'a') + 1;

  // 後の計算のためにB^iを前計算
  using mint_hash = static_modint<mod>;
  vector<mint_hash> hash_base_powers(N + 1, 0);
  hash_base_powers[0] = 1;
  REP3(i, 1, N + 1) {
    dump(hash_base_powers[i - 1].val());
    hash_base_powers[i] = hash_base_powers[i - 1] * hash_base;
  }

  // Hash(S[1,1]),Hash(S[1,2]),...Hash(S[1,N])を前計算
  //   ここで、文字列S[1,i]はS[1,i-1]の後にT[i]を足した物なので、
  // Hash(S[1,i]) = B*Hash(S[i,i-1])+T[i]
  // ※ここで、B=B進法、T[i]=アルファベットのi番目を整数で表現した値
  vector<mint_hash> hash(N + 1, 0);
  REP3(i, 1, N + 1) hash[i] = (hash_base * hash[i - 1]) + digit_string[i];

  for (const auto& elem : hash) dump(elem.val());
  for (const auto& elem2 : hash_base_powers) dump(elem2.val());

  // 指定区間[l,r]から文字列str[l,r]の部分のハッシュ値を求める
  // ・Hash(S[l,r]) = Hash(S[1,r])-B^(r-l+1)*Hash(S[1,l-1])
  auto calc_hash = [&](const ll l, const ll r) {
    return hash[r] - (hash_base_powers[r - l + 1] * hash[l - 1]);
  };

  // 各クエリに対して事前計算したハッシュを求めてO(1)で解答する
  ll a(0), b(0), c(0), d(0);
  REP(i, Q) {
    cin >> a >> b >> c >> d;
    auto hash1 = calc_hash(a, b);
    auto hash2 = calc_hash(c, d);
    auto result = hash1.val() == hash2.val() ? "Yes" : "No";
    cout << result << endl;
  }
}

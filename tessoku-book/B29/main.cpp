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
constexpr ll DIV = 1000000007;

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  ll a(0), b(0), ans(1);
  cin >> a >> b;
  // Note: modintのpowを使うと特に何もしなくても解ける
  // N回回すと間に合わないので、計算量を落とす工夫が必要
  // →繰り返し二乗法で、O(log(n))で求められる
  //
  // 前提: ある整数Xの指数が2のべき乗で表現できる時、高速に計算する事ができる
  //           e.g. X^8を求める場合
  //            1. X^2 = X^1 * X^1を計算する(X^1はすでに求まっている)
  //            2. X^4 = X^2 * X^2を計算する(X^2はすでに1.で求まっている)
  //            3. X^8 = X^4 * X^4を計算する(X^4はすでに1.で求まっている)
  //            この例だと愚直にやると8回2を掛け算しないといけないが、上記だと3回で計算できる
  //      一般的に、X^(2^k)と表現できる場合、k回の演算で計算できる
  // 主題: 上記の性質を用いると、ある整数XのN乗を以下の手順で求められる
  //            1. 求める答えを1で初期化する
  //            2. Nの2進数表現を考える
  //            3. Nの1桁目のビットが立っているかを見る
  //               (10進数だと2で割り切れない場合はビットが立っていると分かる)
  //            4. ビットが立っていれば答えに掛け算する
  //            5. Nを1桁右シフトする
  //               (10進数だと2で割る操作)
  //            6. Nが0になったら全ての桁を探索した事になるので終了し、
  //               その時点での答えが解答となる

  // 演算を10進数(掛け算割り算)で統一したバージョン
  bool b_calc_digit(true);
  while (b_calc_digit && b) {
    // 10進数表現で2で割り切れるかチェック
    // 割り切れなければ、bが2進数表現で1桁目(最右)がビットが立っている事がわかる
    if (b % 2) {
      ans *= a % DIV;
      ans %= DIV;
    }
    // ループの度に、a^2、a^4、a^8...となっていく
    a *= (a % DIV);
    a %= DIV;
    // 左シフトする
    // 10進数表現で言うところの、2で割る処理に対応する
    b /= 2;
  }

  // ※こちらの解法はbの桁数が大きく、1<<N の計算でエラーになった
  // 演算を2進数(ビット演算)で統一したバージョン
  // bのN桁目
  //   ll N(0);
  //   // bを2進数で表現した時の桁数を求める
  //   ll binary_digit_num(0);
  //   binary_digit_num = log2(b);
  //   dump(binary_digit_num);
  //   while (!b_calc_digit && N != binary_digit_num + 1) {
  //     // N桁目のビットが立っているかチェック
  //     ll bit = (1 << N);
  //     if (b & bit) {
  //       ans *= a % DIV;
  //       ans %= DIV;
  //     }
  //     a *= (a % DIV);
  //     a %= DIV;
  //     // 探索する桁を1つ左にシフト
  //     // 10進数表現で言うところの、2で割る処理に対応する
  //     N++;
  //   }
  cout << ans << endl;
}

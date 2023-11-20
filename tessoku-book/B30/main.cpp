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

mint CalcFactorial(int n) {
  //   int n = mod.val();
  mint mod(1);
  for (int i = 2; i <= n; i++) {
    mint num(i);
    mod *= num;
  }
  return mod;
}

// 繰り返し二乗法でa^bをDIVで割った余りを高速に求める
ll CalcPower(ll a, ll b) {
  ll ans(1);
  while (b) {
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
  return ans;
}

ll CalcFactorialMod(int n) {
  ll mod(1);
  for (int i = 2; i <= n; i++) {
    i %= DIV;
    mod *= i;
    mod %= DIV;
  }
  return mod;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  int H(0), W(0);
  cin >> H >> W;

  // 右方向の移動と下方向への移動の全部でH+W-2回の移動が必要になる
  // よって、後は何回目に横方向に移動するかを求める問題に帰着するので、
  // 組み合わせを求めれば良い
  auto n = H + W - 2;
  auto r = W - 1;

  bool bUsemint(false);
  mint result(0);
  ll result_l(0);
  if (bUsemint) {
    result = CalcFactorial(n) / (CalcFactorial(r) * CalcFactorial(n - r));
  } else {
    ll numerator = CalcFactorialMod(n) % DIV;
    ll denominator =
        (CalcFactorialMod(r) % DIV) * (CalcFactorialMod(n - r) % DIV);
    denominator %= DIV;

    // Mを素数とし、bをMで割り切れない整数とする
    // この時、Mで割った余りを求める問題では、
    // 「÷b」を「×b^M-2」に書き換えても問題ない事を利用している
    result_l = numerator * CalcPower(denominator, DIV - 2);
    result_l %= DIV;
  }

  if (bUsemint) {
    cout << result.val() << endl;
  } else {
    cout << result_l << endl;
  }
}

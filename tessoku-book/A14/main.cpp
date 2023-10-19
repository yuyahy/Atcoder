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
  int N(0), K(0);
  cin >> N >> K;
  vector<int> A(N, 0), B(N, 0), C(N, 0), D(N, 0);
  // Note: 予想に反して、unordered_setよりsetのほうが早かった
  set<int> set_D;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> C[i];
  }
  int tmp(0);
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    set_D.emplace(tmp);
    D[i] = tmp;
  }

  bool bFind = false;
  bool bMyAnswer = false;
  if (bMyAnswer) {
    // 自分で最初に書いたコード
    // A〜Cは全探索すると、残りの探す値が一意に決まるため、Dはhashmap or
    // setでキー確認をlog(N) or log(1)でチェックすればいける
    //  → N^3 +　Dの存在確認にかかる時間
    // 最高で約2秒かかっていた
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          if (set_D.contains(K - (A[i] + B[j] + C[k]))) {
            bFind = true;
            break;
          }
        }
        if (bFind) break;
      }
      if (bFind) break;
    }
  } else {
    // 解答にあった半分全列挙
    // 最高で0.9秒ほどなので、上記の解法より大分高速
    set<int> first_half, latter_half;
    // AとBの和の組み合わせ
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        first_half.emplace(A[i] + B[j]);
      }
    }
    // CとDの和の組み合わせ
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        latter_half.emplace(C[i] + D[j]);
      }
    }
    // 半分ずつ列挙した集合を用いて、キー探索する
    for (const auto& sum_A_B : first_half) {
      if (latter_half.contains(K - sum_A_B)) {
        bFind = true;
        break;
      }
    }
  }
  auto result_str = bFind ? "Yes" : "No";
  cout << result_str << endl;
}

// TODO: マクロや共通関数は別ファイルに定義し、埋め込む様にする
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

bool isNthBitSet(ll num, ll N) {
    // 1をNビット左シフトして、numとの論理積をとる
    // 結果が0でなければ、N桁目が立っている
    return (num & (1 << N)) != 0;
}

ll binary(ll bina) {
    ll ans = 0;
    for (ll i = 0; bina > 0; i++) {
        if (bina % 2)
            // ans = ans + (bina % 2) * pow(10, i);
            bina = bina / 2;
    }
    return ans;
}

std::string intToBinaryString(int number) {
    // int型の数値を2進数表現の文字列に変換
    return std::bitset<sizeof(int) * 8>(number).to_string();
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0);
    cin >> N;

    auto str = to_string(N);

    ll cnt(0), v(0);

    // Note:
    // なぜか本番に勘違いしていたが、2進数の桁数≠10進数の桁数なので、
    // str.lengh()分だけカウントすると上位ビットを見ていないケースがある(なぜかサンプルだけは上手くいくが。。。)
    //
    // 以下が１番シンプルな解答
    // while (true) {
    //     if (N & (1 << v)) break;
    //     cnt++;
    //     v++;
    // }

    auto bin = intToBinaryString(N);
    dump(bin);
    auto num_digit = bin.length();

    REP(i, num_digit) {
        if (isNthBitSet(N, i)) break;
        cnt++;
    }

    cout << cnt << endl;
}

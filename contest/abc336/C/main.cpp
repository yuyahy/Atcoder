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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0);
    cin >> N;
    // Note: 本問題を解くのに足りていなかった思考
    //       ・M進数とはM種類の記号を使って整数を表現する方法であること
    //       ・連番でなくても、一旦0〜M-1までの記号を使ってM進数表記に変換し、
    //         それを元の記号に戻せばOK

    // Nを0-4の数字を使って5進法に変換する
    string fifth_system("");
    constexpr int base = 5;
    N--;
    // M進数は対象の10進数の整数を基数で割った余りを商が0になるまで並べ、
    // 最後にそれを逆順に並べた物に等しくなる
    while (N) {
        auto digit = N % base;
        fifth_system += to_string(digit);
        N /= base;
    }
    std::reverse(fifth_system.begin(), fifth_system.end());
    dump(fifth_system);
    if (fifth_system.empty()) fifth_system = "0";
    auto result = stoll(fifth_system);
    // 本設問は元々(0,2,4,6,8)で表現した数を答える問題なので、2をかける必要がある
    cout << result * 2 << endl;
}

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

    string S;
    cin >> S;

    // A, B, Cがこの順にならんでいれば拡張ABC、ただし空文字もOKである点に注意
    int A(0), B(0), C(0);
    char pre;
    pre = S[0];

    bool bExtended(false);
    S += 'X';
    string suppered;
    REP(i, S.length()) {
        if (S[i] != pre) {
            suppered += pre;
        }
        pre = S[i];
    }
    dump(suppered);
    if (suppered == "ABC" || suppered == "A" || suppered == "B" ||
        suppered == "C") {
        bExtended = true;
    } else if (suppered == "AB" || suppered == "AC" || suppered == "BC") {
        bExtended = true;
    }

    auto result = bExtended ? "Yes" : "No";
    cout << result << endl;
}

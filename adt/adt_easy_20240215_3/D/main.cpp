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
#define REP3R(i, m, n) for (int i = (int)(m)-1; (i) >= (int)(n); --(i))

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

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int H(0), M(0);
    cin >> H >> M;

    string result;
    while (true) {
        auto str_H = to_string(H);
        auto str_M = to_string(M);

        // 1桁→2桁に0うめ
        if (str_H.length() == 1) str_H = '0' + str_H;
        if (str_M.length() == 1) str_M = '0' + str_M;

        auto next_str = str_H + str_M;
        swap(next_str[1], next_str[2]);
        std::string time_pattern = "(2[0-3]|[01]?[0-9])([0-5][0-9])";
        std::regex pattern(time_pattern);
        if (std::regex_match(next_str, pattern)) {
            result = str_H + " " + str_M;
            break;
        }

        M++;
        if (M > 59) {
            M = 0;
            H++;
        }
        if (H > 23) H = 0;
    }
    cout << result << endl;
}

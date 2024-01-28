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

    map<char, int> cnt_map;
    // REP(i, 26) cnt_map[i] = 0;
    REP(i, S.length()) { cnt_map[S[i]] += 1; }

    // int max = *cnt_map.rbegin();
    auto max = std::max_element(
        cnt_map.begin(), cnt_map.end(),
        [](const auto& x, const auto& y) { return x.second < y.second; });

    for (const auto& [key, value] : cnt_map) {
        if (value == max->second) {
            cout << key << endl;
            return 0;
        }
    }
}

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

void solve1(const string& S) {
    // 本番回答時の解法
    // std::mapは内部で辞書順の昇順ソートされていることを利用している
    map<char, int> cnt_map;
    REP(i, S.length()) { cnt_map[S[i]] += 1; }

    // std::mapのバリューの最大値とそのキーを求める（辞書順で若いものが優先される）
    auto max = std::max_element(
        cnt_map.begin(), cnt_map.end(),
        [](const auto& x, const auto& y) { return x.second < y.second; });

    for (const auto& [key, value] : cnt_map) {
        if (value == max->second) {
            cout << key << endl;
            return;
        }
    }
}

void solve2(const string& S) {
    // アルファベット各文字をカウントする配列
    vector<int> char_cnt_array(26, 0);
    REP(i, S.length()) { char_cnt_array[S[i] - 'a'] += 1; }

    // 先頭から探索し、辞書順で最も若く、出現回数が多いものを特定する
    int cnt_max(0);
    char max_char;
    REP(i, char_cnt_array.size()) {
        // 大なり比較にすることで、後に同じ出現回数の物がでてきてもスキップされる
        // 逆に、辞書順で後ろを優先したい場合は、等号をつければOK
        if (char_cnt_array[i] > cnt_max) {
            cnt_max = char_cnt_array[i];
            max_char = i + 'a';
        }
    }
    cout << max_char << endl;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    string S;
    cin >> S;

    // solve1(S);
    solve2(S);
}

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
    int N(0), Q(0);
    cin >> N >> Q;

    deque<pair<int, int>> pos;
    REP(i, N) { pos.push_back({i + 1, 0}); }
    dump(pos);

    int query(-1), now(-1);
    string move;

    // Note: C++のdequeはランダムアクセスがO(1)で行えるので以下の解法が使える(公式と同じ)
    REP(i, Q) {
        cin >> query;
        if (query == 1) {
            // 頭を1移動する
            cin >> move;

            // 末端は不要になるので削除
            pos.pop_back();
            pair<int, int> new_pos;

            if (move == "R") {
                new_pos = {pos.front().first + 1, pos.front().second};
            } else if (move == "L") {
                new_pos = {pos.front().first - 1, pos.front().second};
            } else if (move == "U") {
                new_pos = {pos.front().first, pos.front().second + 1};
            } else {
                new_pos = {pos.front().first, pos.front().second - 1};
            }
            pos.push_front(new_pos);
        } else {
            cin >> now;
            // パーツpの現在位置を求める
            cout << pos.at(now - 1).first << " " << pos.at(now - 1).second
                 << endl;
        }
    }
}

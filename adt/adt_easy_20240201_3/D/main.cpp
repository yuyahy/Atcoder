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

    ll N(0), M(0);
    cin >> N >> M;
    vector<ll> answers(N, 0);
    REP(i, N) {
        string tmp, binary;

        cin >> tmp;
        REP(j, M) {
            auto cha = (tmp[j] == 'o') ? '1' : '0';
            binary += cha;
        }
        answers[i] = stoi(binary, 0, 2);
    }
    dump(answers);

    ll max(0);
    REP(i, M) { max += (1 << i); }
    dump(max);

    ll cnt(0);
    REP(i, N - 1) REP3(j, i + 1, N) {
        if ((answers[i] | answers[j]) == max) cnt++;
    }
    cout << cnt << endl;
}

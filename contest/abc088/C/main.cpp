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

#define YESNO(T)               \
    if (T) {                   \
        cout << "YES" << endl; \
    } else {                   \
        cout << "NO" << endl;  \
    }
#define yesno(T)               \
    if (T) {                   \
        cout << "yes" << endl; \
    } else {                   \
        cout << "no" << endl;  \
    }
#define YesNo(T)               \
    if (T) {                   \
        cout << "Yes" << endl; \
    } else {                   \
        cout << "No" << endl;  \
    }

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

// アルファベット(小文字大文字)
const string lower_alphabet = "abcdefghijklmnopqrstuvwxyz";
const string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 数字
const string integers = "0123456789";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - (a1, a2, a3), (b1, b2, b3)の合計9通り
    // - 和からai, biを求めるのは性質的に難しそう？
    // - ciは[0,100]を満たすので、a, bも[0,100]を満たすはず(Yesの場合は)
    // - 全探索だと(10^2)^6 = 10^12でTLE
    // - aiを決めれば、bi = ci - aiが成り立つかチェックすればOK。この場合は(10^2)^3=10^6で間に合う

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 「ai、bi全てで全探索はできない、では何を基準にすれば時間内に全探索できるか？」という思考が解法に結びついた
    //      - 手書きで9通りの式を書く事で方針が浮かんだ
    // - 改善点
    //      - 最初の提出ACコードが汚く、インデックスミスを招きそうな物だった。ラムダ式でリファクタリングした。

    ll H(3), W(3);
    vector<vector<ll>> grids(H, vector<ll>(W, 0));
    REP(i, H) { cin >> grids[i][0] >> grids[i][1] >> grids[i][2]; }

    // 列ごとに ci = ai + biが満たされているかをチェックするためのラムダ式
    auto check_row = [&](const ll a, const vector<ll>& b, const ll colum_idx) {
        return (a + b[0] == grids[colum_idx][0] &&
                a + b[1] == grids[colum_idx][1] &&
                a + b[2] == grids[colum_idx][2]);
    };

    bool res(false);
    vector<ll> b(H, 0);
    REP(a1, 101) {
        // a1からb1,b2,b3を決める
        REP(i, W) b[i] = grids[0][i] - a1;
        REP(a2, 101) {
            if (!check_row(a2, b, 1)) continue;
            REP(a3, 101) {
                if (!check_row(a3, b, 2)) continue;
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}

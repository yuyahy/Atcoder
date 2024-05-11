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
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(m) - 1; (i) >= (int)(n); --(i))

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

#define COUT(x) cout << (x) << endl
#define SCOUT(x) cout << (x) << " "
#define ENDL cout << endl

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
    // - クエリ1がボトルネックになる？
    // - std::fillやstd::vectorの再構築はO(N)かかる
    // - N,Q = [1, 2*10^5]なので2重ループにはできない(N, Qがマックスかつ、最後のクエリ以外全初期化だと間に合わない)
    // - クエリ1を実際に配列に代入するのではなく、今のベースの値はこれという形で持っておく？

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - クエリ1をそのまま行うのではなく、{最後に代入した値} + {そこからの差分}という管理の仕方にするアイデア
    // - 改善点
    //      - 「差分をリセットする部分で結局O(N)かかって間に合わない？」と思ったが、リセットする差分の個数は最後にクエリ1の操作をしてから
    //        現在に至るまでに出現したクエリ2の操作の個数未満なので、O(N)未満だった。

    ll N(0);
    cin >> N;
    vector<ll> A(N, 0);
    for (auto& elem : A) cin >> elem;
    ll Q(0);
    cin >> Q;

    ll base(-1);
    map<ll, ll> add_map;
    REP(i, Q) {
        ll query(0);
        cin >> query;
        if (query == 1) {
            cin >> base;
            add_map.clear();
        } else if (query == 2) {
            ll iq(0), xq(0);
            cin >> iq >> xq;
            add_map[iq - 1] += xq;
        } else {
            ll iq(0);
            cin >> iq;
            iq--;
            if (base != -1) COUT(base + add_map[iq]);
            else COUT(A[iq] + add_map[iq]);
        }
    }
}

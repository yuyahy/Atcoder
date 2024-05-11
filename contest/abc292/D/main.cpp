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
    // - Union Findで同じ頂点間で複数回辺張れる？
    //      - 駄目そう。同一グループ内で辺を張ったかどうかが判定できない
    // - Union Findで連結成分は簡潔に作成できるので、張った辺の本数は別途mapで行う

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - Union Findでできる事とできない事を考察し、できない事を別途mapで行う事で正しい方針に辿り着く事ができた
    //      - データ構造ごとの得意な所と、そうでない/できない所を把握しておくことが大切
    // - 改善点
    //      - 特になし

    ll N(0), M(0);
    cin >> N >> M;
    dsu uf(N);

    // 辺を張る
    vector<pair<ll, ll>> vertices;
    REP(i, M) {
        ll v(0), v_(0);
        cin >> v >> v_;
        v--;
        v_--;

        uf.merge(v, v_);
        vertices.push_back({v, v_});
    }

    // 連結成分ごとに張った辺の個数をカウントするmap
    // keyは連結成分ごとの代表元を使用し、連結成分ごとを表現する
    map<ll, ll> cnt_edges_by_components;
    for (const auto& [v, v_] : vertices) {
        cnt_edges_by_components[uf.leader(v)]++;
    }
    // 全ての連結成分が条件を満たしているかチェック
    bool b_res(true);
    for (const auto& elem : uf.groups()) {
        ll cnt_vertices = elem.size();
        ll cnt_edges = cnt_edges_by_components[uf.leader(elem[0])];
        if (cnt_vertices != cnt_edges) b_res = false;
    }
    YesNo(b_res);
}

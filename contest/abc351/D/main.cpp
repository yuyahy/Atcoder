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
    // - 全マスを開始点として試すと10^6かかる
    // - マスからDFS or BFSする？
    // - DFSだとO(N+M) = O(10^6 + 4)かかるから、全マスを始点にする事はできない？

    // Note:
    // - 結果: 解説AC
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: 十分: DFSなどの探索方法は知っていた
    // - 考察: 不十分: 各座標からDFSするとTLEする事は分かっていたが、どうすれば計算量を減らせるかが思いつかなかった。
    //               今回でいうと、「行き止まりではないマスからなる連結成分の中は自由に移動できるので、その様な連結成分を検出し、
    //               各連結成分とそれに隣接する行き止まりのマスをカウントすれば十分」という部分が思いつかなかった。
    //               連結成分をDFS、BFS、UnionFindで検出し、連結成分ごとに処理するアイデアが大事
    // - 実装: 不十分: 「ダメ元の各マスからDFS」する方針は本番内に実装できたが、解説AC時に実装の修正に時間がかかってしまった。

    ll H(0), W(0);
    cin >> H >> W;
    vector<string> S(H);
    REP(i, H) cin >> S[i];
    dump(S);

    // やはり、各マスからDFS / BFSを行うと最悪O(H^2W^2)になりTLE(※H、Wは最大10^3)

    // - 周囲に磁石が置かれていないマス同士は自由に移動できる事に着目すると、その様なマス目から構成される連結成分の内どれか１座標を始点とし、
    //   連結成分の個数とその周囲に存在する「周囲に磁石がある行き止まりのマス」の和が、その連結成分の自由度となる。
    // - ただし、「既にそのマスを見たかのフラグ」は連結成分ごとに管理しないと、漏れが発生するので注意が必要

    // 与えられたマスが行き止まりポイントかをチェックするラムダ式
    auto check_dead_end = [&](const ll i, const ll j) -> bool {
        bool b_dead_end(false);
        REP(k, 4) {
            ll new_i = i + dy_4[k];
            ll new_j = j + dx_4[k];
            if (new_i != std::clamp(new_i, ll(0), H - 1) ||
                new_j != std::clamp(new_j, ll(0), W - 1)) {
                continue;
            }
            // 動けない
            if (S[new_i][new_j] == '#') {
                b_dead_end = true;
                break;
            }
        }
        return b_dead_end;
    };

    // 1. 行き止まりポイント('.'かつ自身に隣接する上下左右のいずれかに'#'が存在するマス)を記録
    //    Note: ここではフラグを管理する配列に記録しているが、文字列Sに対して'!'などの文字を直接書き込むのでもOK
    //          →この場合管理するデータが減るのがメリット
    vector is_dead_end_point(H, vector<bool>(W, false));
    REP(i, H) REP(j, W) {
        if (S[i][j] == '#') {
            continue;
        }
        if (check_dead_end(i, j)) is_dead_end_point[i][j] = true;
    }
    dump(is_dead_end_point);

    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意
    auto dfs = [&](auto self, const vector<string>& S, const ll i, const ll j,
                   vector<vector<bool>>& seen,
                   set<pair<ll, ll>>& cnt_set) -> ll {
        // 訪問済みの頂点として記録
        seen[i][j] = true;
        ll ret(1);

        REP(k, 4) {
            ll new_i = i + dy_4[k];
            ll new_j = j + dx_4[k];
            if (new_i != std::clamp(new_i, ll(0), H - 1) ||
                new_j != std::clamp(new_j, ll(0), W - 1)) {
                continue;
            }
            if (seen[new_i][new_j] || S[new_i][new_j] == '#') continue;
            // 連結成分に隣接する行き止まりポイントをカウント(std::setを使い重複を回避)
            if (is_dead_end_point[new_i][new_j]) {
                cnt_set.insert({new_i, new_j});
                continue;
            }
            ret += self(self, S, new_i, new_j, seen, cnt_set);
        }
        return ret;
    };

    // 2. '.'かつ行き止まりポイントでないマスをDFSで探索し、連結成分を得る
    //    →連結成分の中は自由に移動できるため、その中のどれか一点からDFSで探索すれば、同じ連結成分の他のマスからDFSする必要はない
    vector seen(H, vector<bool>(W, false));
    ll result(1);
    REP(i, H) REP(j, W) {
        if (S[i][j] == '#') {
            continue;
        }
        // 既に検出した連結成分の中の別のマス or 行き止まり
        if (seen[i][j] || is_dead_end_point[i][j]) continue;
        set<pair<ll, ll>> cnt_set;
        result =
            max(result, dfs(dfs, S, i, j, seen, cnt_set) + (ll)cnt_set.size());
        dump(cnt_set);
    }
    COUT(result);
}

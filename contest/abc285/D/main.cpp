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

// 自前実装(DFSを用いてユーザ名を変更できるかチェック)
void solve1(ll N) {
    vector<pair<string, string>> ST_vec;
    //<現在のユーザ名、変更したい名>のmap
    map<string, string> ST;
    REP(i, N) {
        string S, T;
        cin >> S >> T;
        ST[S] = T;
        ST_vec.push_back({S, T});
    }

    // その<文字列, 訪問済みか>が既に訪問済みかを表現する
    map<string, bool> seen;

    auto dfs = [&](auto self, const string begin_name,
                   const string current_name,
                   const string target_name) -> bool {
        dump(current_name, target_name);
        if (current_name == target_name) return true;

        if (ST.count(target_name) == 0) {
            // 変更したい名称が未使用であればその名称に変更する
            ST.erase(current_name);
            ST[target_name] = target_name;
            seen[target_name] = true;
            return true;
        } else {
            // サイクル(あるユーザを変更するために別のユーザを変更し...で最初のユーザに戻るケース)になっていたら変更できない
            if (ST[target_name] == begin_name) return false;
            auto result = self(self, begin_name, target_name, ST[target_name]);
            // あるユーザが変更したい名称のユーザが他の名称に変更できる場合は、
            // 帰りがけに自身を更新する
            if (result) {
                ST.erase(current_name);
                ST[target_name] = target_name;
                seen[target_name] = true;
            }
            return result;
        }
    };

    bool result(false);
    REP(i, N) {
        auto [current_name, target_name] = ST_vec[i];
        if (seen[target_name]) continue;
        result = dfs(dfs, current_name, current_name, target_name);
        if (!result) break;
    }
    YesNo(result);
}

// 解説実装(サイクルがあるかをチェック)
void solve2(ll N) {
    // 本設問を有向グラフで考えると、サイクルが存在しない場合は
    // 末端の出次数が0のノードから名称を変更→削除を繰り返す事で全ユーザ名を変更する事ができる
    // よってサイクルの有無をチェックする問題に帰着できる

    const ll max = 1000000;
    dsu uf(max);
    map<string, ll> conv_map;
    ll used(0);
    REP(i, N) {
        string S, T;
        cin >> S >> T;

        // ACLのUnionFindの頂点に指定できるのはintのみなので、文字列をintにマッピングする必要がある
        ll node_id1(0), node_id2(0);
        if (conv_map.count(S)) node_id1 = conv_map[S];
        else {
            // 初登場の文字列の場合は新しい番号を割り振る
            node_id1 = used;
            conv_map[S] = used;
            used++;
        }

        if (conv_map.count(T)) node_id2 = conv_map[T];
        else {
            node_id2 = used;
            conv_map[T] = used;
            used++;
        }

        dump(node_id1, node_id2);
        dump(conv_map);

        // 既に共通の親を持つ場合は辺を張るとサイクルができるのでNG
        if (uf.same(node_id1, node_id2)) {
            YesNo(false);
            return;
        }

        uf.merge(node_id1, node_id2);
    }
    YesNo(true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0);
    cin >> N;

    // 考察メモ
    // - Nの制約的に二重ループはできない
    // - どのユーザも一度だけ変更を行う必要がある
    // - 変更時点で他のユーザが既に使用している名称には変更できない
    // - トポロジカルソートでタスクの優先順位を決められる？
    // - <現在のユーザ名、変更したい名>のmapで処理できる？
    //      -

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 「全てのユーザ名を目的の名称に変更できるか」→「グラフっぽく考えて再規定にチェックすれば良い」というのを思いつけた
    //      - 更にあるmapのkeyに対応するvalueに対し、そのvalueをkeyとして再帰的にチェックする実装を思いついた
    //      - グラフの適用可能範囲は広いので、考察の一手として持っておくべし
    // - 改善点
    //      - 自力実装時も「サイクルの有無だけチェックすれば良いのでは？」というアイデアはでたが、本当にそれだけで十分なのか確信が持てなかった
    //      - 手書きでグラフを書いて考察してみた方が良かったかも

    // solve1(N);
    solve2(N);
}

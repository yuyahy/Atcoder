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
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

// 本番解答(弱い順に見ていって、それまでに出現したカードの中で、現在着目している物よりコストが大きい物を除外)
void solve1(ll N, vector<pll>& AC, map<ll, ll>& origin_index_map) {
    auto original = AC;
    // 強さで昇順ソート
    sort(AC.begin(), AC.end());
    dump(AC);

    // 現時点で出現したコストの大きい順に取り出す優先度付きキュー
    priority_queue<ll> cost_max;
    cost_max.push(AC[0].second);
    set<ll> delete_set;
    REP3(i, 1, N) {
        // 強さの弱い順に、「自身より弱く、コストが大きいカード」があれば削除対象にする
        // Note: 削除対象が複数存在するケースがあるので、while()で回す必要がある(ここを見落として1ペナ)
        while (!cost_max.empty()) {
            auto top = cost_max.top();
            if (top > AC[i].second) {
                delete_set.insert(origin_index_map[top]);
                cost_max.pop();
            } else {
                break;
            }
        }

        cost_max.push(AC[i].second);
    }

    COUT(N - delete_set.size());
    REP(i, N) {
        if (delete_set.count(i)) continue;
        cout << i + 1 << " ";
    }
    cout << endl;
}

// 解説(強い順に見ていって、最後に採用されたカードよりコストが低い物を採用する)
// X軸を強さ(Ai)、Y軸を弱さ(Ci)とした時に一番左からグラフが右肩上がりになる様なカードのみを採用するイメージ
// Note: 自前実装と比べると、一回のループで最後に採用された要素との比較のみ行えば良いので簡潔
void solve2(ll N, vector<pll>& AC, map<ll, ll>& origin_index_map) {
    auto custom_comp = [](const pll& left, const pll& right) {
        return left.first > right.first;
    };
    // 強さで降順ソート
    sort(AC.begin(), AC.end(), custom_comp);
    dump(AC);

    // 最後に採用されたカードより「コストが小さい物」を出力対象にする
    // →強い順に見ていってるので、コストのみ着目すれば良い
    ll last_cost(INF);
    set<ll> result_set;
    REP(i, N) {
        if (AC[i].second < last_cost) {
            // 採用 & 最後の採用カードのコストを更新
            result_set.insert(origin_index_map[AC[i].second]);
            last_cost = AC[i].second;
        }
    }
    COUT(result_set.size());
    REP(i, N) {
        if (!result_set.count(i)) continue;
        cout << i + 1 << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 2つの要素からなるペアの片方を基準にソートしておき、もう一方をそれまでの最小値 or 最大値のみ着目する類題をどこかでやっていた
    // - 改善点
    //      - 「自身より弱く、コストが大きいカード」が複数存在するケースを見落として1ペナ
    //          - なんとか本番中にその様なケースを自力で作り、バグに気がつくことができたが15分のロス
    //      - 2パラメータはXY座標上にプロットするとわかりやすいらしい
    //          - 自分の解答とは逆に強い順に見ていって、最後に採用した物よりコストが大きい物を除外するのが公式解答
    //          - こちらだと優先度付きキューで回す必要はない

    ll N(0);
    cin >> N;
    vector<pll> AC(N);

    ll idx(0);

    // <カードのコスト、元のインデックス>
    // 今回は、Ai、Ci共にユニークなのでキーとして使用できる
    map<ll, ll> origin_index_map;
    for (auto& elem : AC) {
        cin >> elem.first >> elem.second;
        origin_index_map[elem.second] = idx;
        idx++;
    }
    dump(AC);
    dump(origin_index_map);

    // solve1(N, AC, origin_index_map);
    solve2(N, AC, origin_index_map);
}

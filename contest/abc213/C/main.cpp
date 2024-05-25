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

#define ALL(a) (a).begin(), (a).end()

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

// 自前実装(sortを行・列それぞれに適用し、詰められない行・列がいくつあるかを数える)
void solve1(ll N, vector<pll> cards_pos) {
    auto original_pos = cards_pos;

    // 列方向に対して昇順ソート
    dump(cards_pos);
    sort(cards_pos.begin(), cards_pos.end());
    dump(cards_pos);

    // <座標, 移動量>
    map<pll, pll> move_map;
    // Y座標の小さい順に自身の上と左に存在するカードの存在する行・列の数を数える
    ll move_X(0), move_Y(0);
    REP(i, N) {
        auto [y, x] = cards_pos[i];
        if (i != 0 and cards_pos[i].first != cards_pos[i - 1].first) move_Y++;
        move_map[cards_pos[i]] = {move_Y, 0};
    }
    dump(move_map);

    std::sort(cards_pos.begin(), cards_pos.end(),
              [](const pll& a, const pll& b) { return a.second < b.second; });
    dump(cards_pos);

    REP(i, N) {
        auto [y, x] = cards_pos[i];
        if (i != 0 and cards_pos[i].second != cards_pos[i - 1].second) move_X++;
        move_map[cards_pos[i]] = {move_map[cards_pos[i]].first, move_X};
    }
    dump(move_map);

    REP(i, N) {
        auto [y, x] = original_pos[i];
        auto [move_Y, move_X] = move_map[original_pos[i]];
        dump(y, move_Y);
        dump(x, move_X);

        SCOUT(y - (y - move_Y) + 1);
        SCOUT(x - (x - move_X) + 1);
        ENDL;
    }
}

// 解説実装(座圧)
void solve2(ll N, vector<pll> cards_pos) {
    vector<ll> card_sorted_by_row, card_sorted_by_column;
    for (const auto& elem : cards_pos) {
        card_sorted_by_row.push_back(elem.first);
        card_sorted_by_column.push_back(elem.second);
    }

    // 座圧のため昇順ソート
    sort(ALL(card_sorted_by_row));
    sort(ALL(card_sorted_by_column));

    // 重複要素を削除
    card_sorted_by_row.erase(unique(ALL(card_sorted_by_row)),
                             card_sorted_by_row.end());
    card_sorted_by_column.erase(unique(ALL(card_sorted_by_column)),
                                card_sorted_by_column.end());

    // 元の配列の各要素に対し、ユニーク & ソートした配列の何番目に存在するかを調べるラムダ式
    auto obtain_idx = [&](const vector<ll>& vec, const ll val) -> ll {
        auto position = lower_bound(ALL(vec), val);
        auto idx_lower = distance(vec.begin(), position);
        return idx_lower;
    };

    for (const auto& elem : cards_pos) {
        SCOUT(obtain_idx(card_sorted_by_row, elem.first) + 1);
        SCOUT(obtain_idx(card_sorted_by_column, elem.second) + 1);
        ENDL;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - H, Wmax=10^9なのでグリッドを全探索する時間はない
    // - 行と列への操作はそれぞれ独立に考える事ができる
    // - 横(行)の移動→自分の左側にいくつ消せない列があるかをカウントすれば良い→数の書かれたカードが存在する列
    // - 縦(列)の移動→自分の上にいくつ消せない行があるかをカウントすれば良い→数の書かれたカードが存在する行

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //  - 行と列の操作が独立なので、それぞれごとに、自分の左 or 上に消せない物がいくつあるかをチェックすれば良いという帰着ができた
    // - 改善点
    //  - 若干強引に解いてしまったが、座圧(座標圧縮)を学ぶことができた
    //  - 元の配列をそのままソートしていた事を忘れていて、提出後にWA

    ll H(0), W(0), N(0);
    cin >> H >> W >> N;

    vector<pll> cards_pos(N, {0, 0});
    for (auto& elem : cards_pos) cin >> elem.first >> elem.second;

    // solve1(N, cards_pos);
    solve2(N, cards_pos);
}

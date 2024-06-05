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

#define INPUT_VEC(a) \
    for (auto& elem : a) cin >> elem

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

// 自前実装
// 円卓を表現するために、Tiが最小のインデックスを求め、そこから円卓の周り順のインデックスを配列にする
void solve1(vll S, vll T, ll N) {
    // テーブル定義: DP[i]: i番目のS君が宝石を受け取る最短時間
    // 初期状態: DP[S[Ti == min]] = Tmin
    // 遷移: DP[i+1] = min(DP[i] + Si, Ti)
    vll DP(N, 0);

    auto min_itr = min_element(ALL(T));
    auto idx_min = distance(T.begin(), min_itr);
    DP[idx_min] = *min_itr;

    // Tiが最小のインデックスから順番に配列につめ、円卓の受け渡し順になる様にする
    vll indices;
    REP3(i, idx_min, N) indices.push_back(i);
    if (indices.size() < N) {
        ll size = indices.size();
        // Note: 以下のような実装にしてしまうと、ループしながら要素を追加している & その要素数を元にループを回しているので未定義動作になる
        // REP(i, N - indices.size()) indices.push_back(i);
        REP(i, N - size) indices.push_back(i);
    }

    dump(indices);

    ll idx = 0;

    dump(DP);

    // 円卓の順番になる様にindicesに詰めているので、N-1回のループで十分
    // →Tiが最小のケースはそれが最小になるのは明らかなため
    while (idx < N - 1) {
        auto current_S = indices[idx];
        auto next_S = indices[idx + 1];
        DP[next_S] = min(DP[current_S] + S[current_S], T[next_S]);
        idx++;
    }
    dump(DP);

    REP(i, N) COUT(DP[i]);
}

// 解説ソース1
// 基本的な考え方(DPを使う)はsolve1と同じだが、こちらはインデックスの割り算を上手くつかって円卓の周回を表現している
void solve2(vll S, vll T, ll N) {
    // テーブル定義: DP[i]: i番目のS君が宝石を受け取る最短時間
    // 初期状態: DP[S[Ti == min]] = Tmin
    // 遷移: DP[i+1] = min(DP[i] + Si, Ti)
    vll DP(N, INF);

    auto min_itr = min_element(ALL(T));
    auto idx_min = distance(T.begin(), min_itr);
    ll timestamp = *min_itr;
    ll idx = idx_min;

    dump(DP);

    REP(i, N) {
        DP[(idx + i) % N] = timestamp;
        timestamp = min(timestamp + S[(idx + i) % N], T[(idx + i + 1) % N]);
    }

    dump(DP);

    REP(i, N) COUT(DP[i]);
}

// 解説ソース2
// DPではなく、優先度付きキューを活用する
void solve3(vll S, vll T, ll N) {
    // 優先度付きキューで昇順ソートするための比較関数
    // ※デフォルトが降順なので、大なり小なりの記号の向きに注意する必要がある
    auto custom_comp = [](const pair<ll, ll>& left, const pair<ll, ll>& right) {
        if (left.first == right.first) {
            return left.second > right.second;
        } else {
            return left.first > right.first;
        }
    };
    // <現在注目している頂点の頂点1からの最小距離, 頂点の番号>の優先度付きキュー
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(custom_comp)>
        min_queue(custom_comp);

    REP(i, N) min_queue.push({T[i], i});
    vector<bool> seen(N, false);
    vll shortest(N, INF);
    while (!min_queue.empty()) {
        auto [time, s_id] = min_queue.top();
        dump(time, s_id);
        min_queue.pop();
        if (seen[s_id]) continue;
        shortest[s_id] = min(shortest[s_id], time);
        seen[s_id] = true;
        // Note: N-1の次は0(円卓なので)になる様に処理する必要あり
        min_queue.push({time + S[s_id], (s_id + 1) % N});
    }

    REP(i, N) COUT(shortest[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - i番目のS君が宝石を受け取るのは以下の2パターン
    //      1. i-1番目のS君から宝石を受け取る
    //      2. T君から宝石を受け取る
    // - 最初に宝石を受け取るのは、Tiが最も小さいi番目のS君
    // - そのSmin(i)君から反時計回りに宝石を受け渡ししていく
    // - 動的計画法？

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 特別な知識は必要ない
    // - 考察: {不十分}
    //      - 遷移に着目し、漸化式を立ててDPで解く方針は合っていた
    // - 実装: {不十分}
    //      - L93に記載したような凡ミスをしてしまった(これを修正したら最初のコードでAC)
    //      - グリッド探索と同様に、「開始インデックス + ループ回数」を要素数Nで割った余りを利用すると循環を表現できる

    ll N(0);
    cin >> N;

    vll S(N, 0), T(N, 0);
    INPUT_VEC(S);
    INPUT_VEC(T);

    // solve1(S, T, N);
    //solve2(S, T, N);
    solve3(S, T, N);
}

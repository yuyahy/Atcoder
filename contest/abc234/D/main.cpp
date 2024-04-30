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
    // - 先頭から出現した要素を全て優先度付きキューで保持すると挿入時にコストがかかる
    // - 今回求める必要があるのは、現在の大きい順にK番目の要素なので、優先度付きキューで保持する必要があるのはMAX=K個

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 「先頭-i項の中でK番目に大きい値」→「上位Kの中の最小値」という言い換えができた
    //      - 「K番目に大きい要素が変わる時ってどんな時？」という考え方が解法に結びついた
    // - 改善点
    //      - だらだらしてしまったのか、1.5H-2.0Hほど使って解いた
    //      - nth_elementやpartial_sortを試してみたが、今回求めている物ではなかった

    ll N(0), K(0);
    cin >> N >> K;

    vector<ll> P(N, 0);
    for (auto& elem : P) cin >> elem;
    dump(P);

    // 現在出現している要素の内、上位K個までを昇順に保持する優先度付きキュー
    priority_queue<ll, vector<ll>, std::greater<ll>> top_prioriry_queue;
    // 大きい方から上位K番目の要素が変わるタイミング=i番目の要素がK番目の要素よりも大きかった時
    // なので、その様なタイミングで優先度付きキューを更新する。
    REP(i, N) {
        // K番までは問答無用で要素を追加
        if (top_prioriry_queue.size() < K) {
            top_prioriry_queue.push(P[i]);
            if (top_prioriry_queue.size() == K) COUT(top_prioriry_queue.top());
            continue;
        }
        // K+1番以降は上位K番までに変更があるかをチェックする
        if (top_prioriry_queue.top() < P[i]) {
            top_prioriry_queue.pop();
            top_prioriry_queue.push(P[i]);
        }
        COUT(top_prioriry_queue.top());
    }
}

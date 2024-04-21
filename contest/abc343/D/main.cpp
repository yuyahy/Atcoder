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

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 「これってmapとかvectorをそのまま使うだけじゃない？」という発想 + mapのキー操作にかかる計算量から、正確な計算量を見積もる事ができた
    //      - 値の種類はsetやmapで管理する事ができるのを知っていた
    // - 改善点
    //      - 一瞬で解けたので特になし

    ll N(0), T(0);
    cin >> N >> T;
    // 人Aの現在のスコア
    vector<ll> scores(N, 0);
    // <スコア, 現在そのスコアを取っている人数>
    map<ll, ll> score_cnt_map;
    // 初期値
    score_cnt_map[0] = N;

    REP(i, T) {
        ll A(0), B(0);
        cin >> A >> B;
        // mapはキーの追加/削除がO(logN)、要素数の取得がO(1)で行える
        // よっておおよそO(TlogN)で以下の処理を実行できる

        // 人:Aの最後のスコア
        auto pre_score = scores[A - 1];
        // 人:Aの最新スコアを更新
        scores[A - 1] += B;
        // 人:Aの最新スコアの人数は一人増加
        score_cnt_map[scores[A - 1]]++;
        // 人:Aの最後のスコアの人数は一人減少
        score_cnt_map[pre_score]--;
        // そのスコアの人がいなくなったらキーごと削除
        if (score_cnt_map[pre_score] == 0) score_cnt_map.erase(pre_score);

        cout << score_cnt_map.size() << endl;
    }
}

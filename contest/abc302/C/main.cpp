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
    // - 互いに異なる事は確定しているので、辞書順に並び替えて比較する？
    // - Nの順列を全て試す→8!=40320、並び替えた物が条件を満たすかチェック→5 * (8-1) = 35
    //   →　40320 * 35 = 1411200 = 10^6
    // - よって愚直でも間に合う

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 「ソートし隣り合った配列を比較する」方針は嘘解法だという事に気がつき、順列を使った全探索に切り替えた事
    // - 改善点
    //      - インデックス周りの実装でちょこちょこミス
    //          - 「同じサイズの2つの配列の同インデックスを先頭から比較する」はよくあるケースだが、pythonのzipに相当する処理がないのでミスしがち

    ll N(0), M(0);
    cin >> N >> M;
    vector<string> S(N);
    for (auto& elem : S) cin >> elem;
    dump(S);
    // std::next_permutationを使用するために昇順ソートしておく
    sort(S.begin(), S.end());
    dump(S);

    auto check_satify = [&]() -> bool {
        REP(i, N - 1) {
            const string& current = S[i];
            const string& next = S[i + 1];
            ll diff_cnt(0);
            REP(j, M) {
                if (current[j] != next[j]) diff_cnt++;
            }
            if (diff_cnt != 1) return false;
        }
        return true;
    };

    auto res = false;
    do {
        res = check_satify();
        if (res) break;
    } while (next_permutation(S.begin(), S.end()));

    YesNo(res);
}

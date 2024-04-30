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
    // - 良い文字列
    //      - 英小文字を全て削除
    //      - 連続する()を削除し、空文字になるもの
    // - シミュレーション系
    // - ')'のケースをどうやる？
    //      - 先頭から文字をstackに保持し、もっとも最近出現した'('がでるまでpopする。その過程で出現したアルファベットを箱から取り出す
    // - 取り出し処理をstack、箱の役割をsetでやればO(NlogN)で処理できる(setの追加、削除、所属判定にO(logN)かかる)

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - ()の処理はstackで行うと楽という事を知っていたのが良かった
    // - 改善点
    //      - ')'のケースの理解に時間がかかった気がする。問題文だけで理解できるとベストだが、サンプルと行き来するとより助けになる
    //        ※ただしコーナーケースはサンプルにない事もあるので、嘘解法にならないように設問を理解する必要がある

    string S;
    cin >> S;

    set<char> box;
    stack<char> string_stack;

    for (const auto& ch : S) {
        string_stack.push(ch);
        if (ch == '(') {
            continue;
        } else if (ch == ')') {
            // 整数jは必ず存在する事が保証されている
            while (true) {
                auto target_ch = string_stack.top();
                string_stack.pop();
                if (target_ch == '(') {
                    break;
                } else if (target_ch == ')') {
                    continue;
                } else {
                    // アルファベットの場合は箱から取り出す
                    box.erase(target_ch);
                }
            }
        } else {
            // アルファベットの場合
            if (box.count(ch)) {
                COUT("No");
                return 0;
            }
            box.insert(ch);
        }
    }
    COUT("Yes");
}

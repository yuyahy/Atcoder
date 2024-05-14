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
    // - 意外と数学的に除外すると面倒
    // - 4桁の整数の作り方は最大10^4なので全列挙したほうが楽かも

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 最初の場合の数っぽくやろうとしたが沼ったので、制約が小さい事と桁数が固定である事に着目して簡単な全探索を実装したこと
    // - 改善点
    //      - 場合の数っぽくやろうとして沼った。無理に数学っぽくやろうとせずにプログラミングの得意な部分(列挙とか)を活かした方が良い
    //      - 数字、アルファベットは一文字ずつ見るとありえるパターンが限られている & その数も少ないという特徴がある

    string S;
    cin >> S;

    set<char> cannot_use_string, necessary_use_string;
    REP(i, 10) {
        if (S[i] == 'x') cannot_use_string.insert(to_string(i)[0]);
        else if (S[i] == 'o') necessary_use_string.insert(to_string(i)[0]);
    }

    dump(cannot_use_string);
    dump(necessary_use_string);

    // 使用できる数字を文字列として生成する
    string can_use_numbers;
    REP(i, 10) {
        if (!cannot_use_string.count(integers[i])) {
            can_use_numbers += integers[i];
        }
    }

    dump(can_use_numbers);

    // 使用できる数字を組み合わせて(重複を許す)できる数字の中から、使用しなければならない数字を全て含む物をカウント
    ll cnt(0);
    for (const auto elem1 : can_use_numbers) {
        for (const auto elem2 : can_use_numbers) {
            for (const auto elem3 : can_use_numbers) {
                for (const auto elem4 : can_use_numbers) {
                    string candidate_str;
                    candidate_str += elem1;
                    candidate_str += elem2;
                    candidate_str += elem3;
                    candidate_str += elem4;

                    // 必要な数字を全て含んでいるかチェック
                    bool b_all_contains(true);
                    for (const auto necessary_char : necessary_use_string) {
                        if (candidate_str.find(necessary_char) ==
                            std::string::npos) {
                            b_all_contains = false;
                            break;
                        }
                    }
                    if (!b_all_contains) continue;
                    cnt++;
                }
            }
        }
    }
    COUT(cnt);
}

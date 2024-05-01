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
    // - 単純に途中挿入するとインデックスが振り直しになり、TLEしそう
    // - std::listは任意の位置にO(1)で要素を追加できるらしいのでこれを使う？
    //      - ランダムアクセスはO(N)だが、今回は直前に挿入した要素のleft or rightにしか要素を追加する事はない

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 任意の位置に高速に要素を挿入できるデータ構造がないかをChatGPTに質問し、題意にピッタリなstd::listが返ってきた
    // - 改善点
    //      - 自分はデータ構造で殴ったが、公式解法だと操作を逆順に考え、中央から左右に要素を追加していく方針が紹介されていた。
    //        自分も最初その方針でできるかな？と思ったがあまり細部を詰めずに方針転換してしまったのが反省点
    //      - 逆順に考えた時、L, Rの操作はどう変わるか？の考察が足りていなかった

    ll N(0);
    cin >> N;
    string S;
    cin >> S;

    std::list<ll> insert_list(1, 0);
    dump(insert_list);
    auto last_insertion_itr = insert_list.begin();
    dump(*last_insertion_itr);

    ll i(0);
    for (const auto& elem : S) {
        i++;
        // Note: 左に要素を追加する場合はイテレータを操作する必要がある
        //      →std::list::insert()は指定されたイテレータの直前に要素を追加する
        if (elem == 'R') std::advance(last_insertion_itr, 1);
        last_insertion_itr = insert_list.insert(last_insertion_itr, i);

        dump(*last_insertion_itr);
        dump(insert_list);
    }
    dump(insert_list);

    for (const auto& elem : insert_list) SCOUT(elem);
    ENDL;
}

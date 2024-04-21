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

/**
 * @brief 文字列の中の特定の文字を別の文字に置換する
 *
 * @param str
 * @param target
 * @param replacement
 */
void replaceChars(std::string& str, char target, char replacement) {
    size_t pos = 0;
    while ((pos = str.find(target, pos)) != std::string::npos) {
        str[pos] = replacement;
        ++pos;
    }
}

void another_solve(const string& S, const ll& N, const ll& Q) {
    auto convert_alpha = lower_alphabet;
    REP(i, Q) {
        char c, d;
        cin >> c >> d;
        // 置換
        replaceChars(convert_alpha, c, d);
    }

    dump(convert_alpha);
    for (const auto& elem : S) {
        dump(elem);
        REP(i, 26) {
            if (lower_alphabet[i] == elem) cout << convert_alpha[i];
        }
    }
    cout << endl;
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), Q(0);
    string S;
    cin >> N;
    cin >> S;
    cin >> Q;

    // 別解
    // another_solve(S, N, Q);
    // return 0;

    // 考察メモ
    // - 愚直: 10^5*10^5 = 10^10で間に合わない

    // 最終的に、各文字を何の文字に置換すれば良いかがわかっていれば、置換は26 * N程度で済む
    // ただし置換する順番はクエリの順番に合わせないと結果が合わない

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 逐次変換するのではなく、クエリから各アルファベットを何のアルファベットに置換すれば良いかを求め、最後に一回だけ置換する
    //      - mapをベースに各文字をループで置換すると、前のループで変換した文字が更に置換されてしまうため、文字列を一文字ずつ処理すれば良いと気がついた点
    // - 改善点
    //      - 「最終的にどのアルファベットがどのアルファベットに対応するのか」？というマッピングを作る際に、自分は逆にクエリを処理するという方針にしたが、
    //         another_solve()関数に実装した様にアルファベット(今回は小文字)は高々26文字しかないと分かっているので、クエリごとにこれを置換し、マッピングする
    //         という方針の方が簡潔。
    //      - 数字にしろアルファベットにしろ、単体の文字なら非常に要素数は少ないので、それを利用する発想がなかった(テンプレートには今回追加した)

    // クエリを逆順で処理するためにstackに積む
    // e.g. 以下の様な順序のクエリを考えると先頭から処理すると、以前にバリューとして設定した文字が、後続のクエリで更に置換設定されると、
    //      mapの場合はこれから置換設定するキーが以前の処理でバリューとして設定されていないかをチェックしないといけなくなるので、逆順で処理する
    //      1. r→b
    //      2. b→c
    // 最終的に、r→c、b→c
    stack<pair<char, char>> queries;
    REP(i, Q) {
        char c, d;
        cin >> c >> d;
        queries.push({c, d});
    }

    // クエリを逆順に取り出す
    map<char, char> cnv_map;
    while (!queries.empty()) {
        auto [c, d] = queries.top();
        queries.pop();
        // 既にdをキーとして置換設定がされていた場合は、cもcnv_map[d]となる
        if (cnv_map.count(d) != 0) {
            cnv_map[c] = cnv_map[d];
        } else {
            cnv_map[c] = d;
        }
    }

    dump(cnv_map);

    // 文字列を先頭から処理し、置換設定に応じて一文字ずつ出力する
    // →実際にreplace処理を行うとすると、結局クエリの順に処理しないといけなくなるため
    for (const auto& elem : S) {
        dump(elem);
        if (cnv_map.count(elem) != 0) {
            cout << cnv_map[elem];
        } else {
            cout << elem;
        }
    }
    cout << endl;
}

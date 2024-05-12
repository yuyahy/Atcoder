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
using mint = static_modint<100000000>;
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

    // Note:
    // - 結果: 解説AC
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 解説を読みそのまま理解できたので、知識面は十分だったと考えられる
    // - 考察: {不十分}
    //      - 配列の各ペアの総和は「各要素がN-1回ずつ出現するのでO(N)で求められる(二重ループしなくて良い)」という発想が欠けていたのが致命的
    //          - ホワイトボードに和を書き出したりしたが気づかなかった
    //      - 今回の制約(Ai < 10^8)の下では、x + y < 2 * 10^8なので、「(x + y)を10^8で割った余り」は
    //         ・x + y < 10^8 → x + y
    //         ・x + y >= 10^8 → x + y - 10^8
    //        と言い換える事ができる。mで割った余りの性質としては「[0, m-1]になる」くらいしか思いつかなかった。。。
    // - 実装: {十分}
    //      - 解説を読んで理解できれば解答コードは自前で実装できたので、十分だったと考えられる

    ll N(0);
    cin >> N;
    vector<ll> A(N, 0);
    REP(i, N) {
        ll tmp(0);
        cin >> tmp;
        A[i] = tmp;
    }
    ll sum(0);

    // f(x,y) = {x + yを10^8で割った余り}なので今回の制約の範囲で言い換えると、
    // {x + y < 10^8なら x + y}、{それ以外は x + y - 10^8}
    // よって、
    // ・{余りを取らない全ての和} - {x + y >= 10^8となる(i, j)の組の個数} * 10^8
    // が答えに等しい

    // 余りを取らない和は、各項がN-1回ずつ足される事から以下でO(N)で求められる
    ll sum_not_mod(0);
    for (const auto& elem : A) sum_not_mod += (N - 1) * (elem);
    dump(sum_not_mod);

    // {x + y >= 10^8となる(i, j)の組の個数}を二分探索で求める
    // Aをソートし、先頭から各Aiとそれより左にある要素で{Aj >= 10^8 - Ai}となる最小のインデックスを探す
    sort(A.begin(), A.end());
    dump(A);
    ll cnt_over(0);
    const ll max = ll(1e8);
    REP(i, N - 1) {
        // 10^8 - Ai(制約よりAi < 10^8なので符号をチェックする必要なし)
        auto remain = max - A[i];
        // 注目しているインデックスの一つ左のインデックスを開始点にする必要がある
        auto position = lower_bound(A.begin() + i + 1, A.end(), remain);
        if (position == A.end()) continue;
        auto idx_lower = distance(A.begin(), position);
        dump(remain, idx_lower);
        cnt_over += N - idx_lower;
    }
    dump(cnt_over);

    COUT(sum_not_mod - max * cnt_over);
}

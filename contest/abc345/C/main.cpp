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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);
    string S;
    cin >> S;

    // [1, N]の範囲の整数から重複しないペアはN*(N+1)/2通り→全列挙はできない

    // ペアが指す文字が同じである場合はノーカウント(入れ替えても意味がない)

    // i番目の文字がi+1...N番目の文字列と入れ替える

    // 文字の種類は26しかないので、ランレングス圧縮？
    // 今回は「ペアを入れ替える事により、何通りの文字列ができるか」にしか興味がない

    // Note:
    // - 結果: 解説AC
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: 十分
    // - 考察: 十分
    //      「愚直に各(i, j)を2重ループするとTLEになるので、(i,j)の内入れ替えると元の文字列と違う文字列になるのはどういうケース？」という観点から考察を始め、
    //      文字ごとの出現回数を管理するmapを使う事で、O(Nlog(N))に計算量を落とすという方針は合っていた。
    //      ※「インデックス(i, j)が互いに異なる文字であれば、それらを入れ替えると必ず一意な文字列になる」所に気づけるかがポイント
    //      ※多重ループの代わりに、事前に1重ループでmapを作り、カウントする別の1重ループで累積的なmapと事前に作ったmapを比較している
    // - 実装: 不十分
    //      vector<map<char, int>> char_cnt_vector(S.length());という様な文字列のインデックスごとに、それまでの文字の出現回数をカウントする
    //      方針で実装したが提出時にMLEが発生した。
    //      また、同じ文字が複数存在した場合は、元の文字列も1カウントする必要があるが、それをカウントするためのロジックをその場しのぎな物にしてしまった。
    //      簡潔なのは、「同じ文字が2回以上出現するか」をチェックする方針

    map<char, int> all_cnt_map;
    REP(i, S.length()) { all_cnt_map[S[i]]++; }

    // 自身のインデックスより右にあり、自身と異なる文字の数が入れ替える対象
    ll res(0);
    map<char, int> current_map;
    bool b_same(false);
    REP(i, S.length()) {
        current_map[S[i]]++;
        // 自身より右側にあり、自身と同じ文字の個数
        auto same_numbers = all_cnt_map[S[i]] - current_map[S[i]];
        // 自身より右側にあり、自身と異なる文字の個数
        // →{自身より右側の配列の要素数} - {自身より右側にあり、自身と同じ文字の個数}
        auto replace_target_numbers = (S.length() - i - 1) - same_numbers;
        res += replace_target_numbers;
    }
    // 同じ文字が2つ以上ある場合、それを入れ替えると元の文字列になる点に注意
    for (const auto& elem : all_cnt_map) {
        if (elem.second > 1) {
            b_same = true;
            break;
        }
    }
    if (b_same) res++;
    cout << res << endl;
}

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
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))

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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    int N(0);
    cin >> N;

    // Note: この問題は、論理クイズなどで有名な問題である。「毒入りワイン 識別」などで検索すると色々ヒットする
    //       おおまかな方針は以下。
    //       1. 各ワインに[0, N-1]の番号を振り、これの２進数表現を求める
    //       2. 友人をA = log2(N)人用意する
    //       3. ワインを２進数表現した物の各ビットが、i番目の友人Aiが飲むべきワインを表す
    //
    //       何となくM = {N/2}を満たす最小の整数かと思っていたが、間違っていた。
    //       また、bit操作は組み込みの演算子を使っても良いが、以下のstd::bitsetの方が可読性は高い印象

    // M = log2(N)を満たす最小のMを求める
    // ※2^M = N となる様な最小のＭを求めるのに等しい
    int M(0);
    while ((1 << M) < N) M++;
    cout << M << endl;

    // 各ジュースに[0, N-1]の番号を振り、これの２進数表現を求める
    // 今回はNmax=100なので、8bit用意しておけば充分
    constexpr auto bits = 8;
    vector<bitset<bits>> binary_juices(N);
    REP(i, N) {
        std::bitset<bits> binaryRepresentation(i);
        binary_juices[i] = binaryRepresentation;
    }
    dump(binary_juices);

    // i番目の友人にどのジュースを飲ませるかを出力する
    vector<vector<int>> friend_drink(M);
    REP(i, M) {
        vector<int> indices;
        dump(i);
        REP(j, N) {
            auto binary_juice = binary_juices[j];
            dump(binary_juice);
            if (binary_juice.test(i)) {
                indices.push_back(j + 1);
            }
        }
        dump(indices);
        friend_drink[i] = indices;

        cout << indices.size() << " ";
        for (const auto& juice : indices) {
            cout << juice << " ";
        }
        cout << endl;
    }

    // お腹を壊した人を受け取る
    string S;
    cin >> S;
    // 入力Sのi番目がお腹を壊したかを表すため、ジュースのbit列と比較するために
    // 逆順に並び替える必要がある
    reverse(S.begin(), S.end());

    // お腹を壊した人の情報から腐ったジュースを特定する
    std::bitset<bits> binary_hits(S);
    dump(binary_hits);
    REP(i, N) {
        if (binary_juices[i] == binary_hits) {
            cout << i + 1 << endl;
            return 0;
        }
    }
}

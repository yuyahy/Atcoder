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

ll floor(ll x, ll m) {
    // x を m で割った余りを計算し、m との合同を取ることで非負の余りに変換する
    ll r = (x % m + m) % m;

    // x から余りを引いて、m で割ることで商を計算する
    return (x - r) / m;
}

ll ceil(ll x, ll m) { return (x + m - 1) / m; }

// Note: ここでmをコピー渡しにしてしまうと、要素数が非常に大きいケースでTLE
ll cal_repeat(ll num, std::map<ll, ll>& m) {
    if (num < 2) return 0;
    if (m.count(num) != 0) return m[num];

    m[num] = num + cal_repeat(floor(num, 2), m) + cal_repeat(ceil(num, 2), m);

    return m[num];
}

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0);
    cin >> N;
    ll result(0);

    // Note: 今回はメモ化再帰について以下の事を学んだ。
    //        1. メモ化再帰は今回の様に、同じ計算毛結果が再利用できるケースでは相当高速になる→O(N)がO(logN), O(log^2N)レベル(10^18ぐらいまでも大丈夫)
    //        2. std::mapにメモする→std::vectorだと要素数が大きい時にオーバーフローしたため
    //        3. 再帰関数でstd::mapを引き渡す際は必ず参照渡しにする or グローバルな領域にstd::mapを定義する or 参照ラムダ式で再帰を書き、ローカルなstd::mapをキャプチャする
    //           →再帰関数でコピー渡しにすると、コピーコストがかかり、要素数が非常に大きいケースでTLEになるため

    std::map<ll, ll> m;
    // この環境で取れるstd::mapの要素数の最大値
    // 参考までに以前の当環境での実行結果 = mx.max_size() => 384307168202282325
    dump(m.max_size());
    // 再帰で実装
    // →再帰処理の引数にメモのmapを書かなくて良い & ローカルのmapをキャプチャして受け渡しできるので、こちらの方が良いかも
    // ※繰り返しになるが、引数でmapを受け渡しする場合は必ず参照渡しにすること(コピーはコストがかかり×)
    auto memo_calc = [&](auto self, const ll num) -> ll {
        // ベース条件
        if (num < 2) return 0;
        // 既にその引数での計算結果をメモしていた場合はそれを使う
        if (m.count(num) != 0) return m[num];

        m[num] = num + self(self, floor(num, 2)) + self(self, ceil(num, 2));

        return m[num];
    };

    result = memo_calc(memo_calc, N);
    // result = cal_repeat(N, m);
    dump(m);

    cout << result << endl;
}

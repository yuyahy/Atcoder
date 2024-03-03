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

    ll N(0);
    cin >> N;
    vector<ll> A(N, 0), B(N, 0);
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];

    // 積の和の最小化
    // 直感的にも、各要素が1以上の整数なので、気温が高い日に簡単な宿題をやるのが最小
    // 証明: 以下の2条件を両方満たす時、x日目とy日目でやる宿題を逆にした方が難易度の和が小さくなる
    //      ・条件1. x日目の気温 < y日目の気温
    //      ・条件2. x日目の難易度 < y日目の難易度
    //      ここで、i日目の宿題の難易度をAi、気温をBiとすると、
    //      反対にしない場合の気温 * 難易度の和 = Ax*Bx + Ay*By
    //      反対にした時の場合の気温 * 難易度の和 = Ay*Bx + Ax*By
    //      よって、{反対にしない場合の気温 * 難易度の和} - (反対にした時の場合の気温 * 難易度の和)は、
    //      Ax*Bx + Ay*By - Ay*Bx - Ax*By
    //      →(Ax-Ay)(Bx-By)
    //      ここで、Ax < AyかつBx < Byである事に注意すると、
    //      →(負の整数)(負の整数)なので、
    //      {反対にしない場合の気温 * 難易度の和} - (反対にした時の場合の気温 * 難易度の和) ≧ 0
    //      したがって、反対にした方が総和は小さくなるといえる
    //      また、「気温が高い日に簡単な宿題をやる」以外の方針を選択した場合、上記の条件1、2を満たす(x, y)の組が少なくとも1つ存在するはず

    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    std::reverse(B.begin(), B.end());
    // 内積を求める
    auto result = std::inner_product(A.begin(), A.end(), B.begin(), 0);
    cout << result << endl;
}

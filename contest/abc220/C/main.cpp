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

#define ALL(a) (a).begin(), (a).end()

#define INPUT_VEC(a) \
    for (auto& elem : a) cin >> elem

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

template <typename T>
vector<T> obtain_cumulative_array(const vector<T>& array) {
    vector<T> accum_array(array.size());
    inclusive_scan(ALL(array), accum_array.begin());
    return accum_array;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - X=10^18なので実際に足していくと間に合わない
    // - A[1...N]の累積和を求めておき、N * {X / ΣAの商} + {余りを最初に超えるインデックス}が答え
    // - 余りを最初に超えるのは二分探索で高速にもとめられる
    // - O(N + logN)

    // Note:
    // - 結果: {自力AC(1ペナ)}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 何回繰り返すか？系問題の典型は商と余りを求めること
    // - 改善点
    //      - 「初めて和がXを超えるのは何項目まで足したときか」なのでupper_bound()を使わないといけない所を、lower_bound()にして1ペナ

    ll N(0), X(0);
    cin >> N;
    vll A(N, 0);
    INPUT_VEC(A);
    cin >> X;

    // std::inclusive_scanを使うと累積和が一発で求められる
    auto accum_A = obtain_cumulative_array(A);
    // vll accum_A(N, 0);
    // accum_A[0] = A[0];
    // REP3(i, 1, N) accum_A[i] = accum_A[i - 1] + A[i];
    // inclusive_scan(ALL(A), accum_A.begin());

    // vll inclusive_test(A.size());
    // dump(accum_A);
    // dump(inclusive_test);

    dump(accum_A);

    // A全体を繰り返す回数
    auto repeat_time = X / accum_A.back();

    // 余った部分
    auto mod = X % accum_A.back();
    auto positon = upper_bound(ALL(accum_A), mod);
    auto idx_lower = distance(accum_A.begin(), positon);

    dump(repeat_time, idx_lower);

    COUT(repeat_time * N + idx_lower + 1);
}

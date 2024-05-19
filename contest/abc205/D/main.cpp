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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - Ki<=10^18でかなり大きい
    // - i番目 < A[0] → i
    // - i番目 < A[N-1] → i + A.size()
    // - A[i] < i番目 < A[i+1]

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 二分探索は知っていた
    // - 考察: {不十分}
    //      - i番目までの整数で、除外されている整数の累積和を算出する方針でやろうとしたが、KがA[i-1]とA[i]の間に存在するケースの求め方がわからなかった
    //      - 累積和 & 二分探索で高速に求めたい要素以上のインデックスを求め、そこから累積和の情報を使って目当ての値を求めるパターン
    //      - 数え方については解説を読んだだけだとパッとわからなかったので、図示した
    //      - 累積和を使うのであれば、基本的には求めたい情報(今回でいうと除外されない整数)を算出しておくイメージ(逆だと二分探索できない)
    //      - 求めたい情報ファーストの思考が良いのかも(自分は排反する情報に着目しがち)
    // - 実装: {十分}
    //      - 方針が分かれば実装は簡単

    ll N(0), Q(0);
    cin >> N >> Q;
    vll A(N, 0);
    set<ll> exclude;
    for (auto& elem : A) {
        cin >> elem;
        exclude.insert(elem);
    }

    // Aiまでに出現する良い整数(除外されない整数)の累積和
    vector<ll> accum(N, 0);
    accum[0] = A[0] - 1;
    REP3(i, 1, N) { accum[i] = accum[i - 1] + A[i] - A[i - 1] - 1; }
    dump(accum);

    REP(i, Q) {
        ll K(0);
        cin >> K;

        if (K > accum[N - 1]) COUT(A[N - 1] + K - accum[N - 1]);
        else {
            // Ai、Ai+1の間に求めたいKが存在するケース
            // 1. lower_bound() & distance()でaccum[i]>=Kとなる最小のインデックスを求める
            auto position = lower_bound(accum.begin(), accum.end(), K);
            auto idx_lower = distance(accum.begin(), position);
            dump(idx_lower);
            // 2. 求めたいK番目の値は、A[1.で求めたインデックス]から(accum[1.で求めたインデックス] - K - 1)戻った位置に存在する
            // Note: A[i]は除外された整数なので、使用できる整数はA[i-1]+1からA[i]-1まで
            COUT(A[idx_lower] - (accum[idx_lower] - K) - 1);
        }
    }
}
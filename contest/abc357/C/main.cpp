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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 特別な知識は必要ない
    // - 考察: {十分}
    //      - レベルが低い順にカーペットを構築する方針は正しい
    // - 実装: {不十分}
    //      - 本番内に実装ができなかった(サンプルと手元で試したN=3のケースは合ってそうだったが、提出するとWAとREがでた)
    //      - 自分はこういったグリッド内の循環系の問題が苦手なので克服する必要あり
    //      - こうした方がいいかなというポイントは以下。
    //          - vector<string>でグリッドを表現するが、処理は一文字ずつ行う(文字列単位でまとめて処理するとバグった時に対処に時間がかかる)
    //          - 行と列で分解して処理を考える(Pythonのnumpyの様に２次元の行列単位で考えるのはC++だとEigenとか使わないと難しい)
    //          - 繰り返し処理では、インデックスにオフセット(e.g. 今回でいうと1ブロックずつ書き込む処理が該当)したり、余りを使う

    ll N(0);
    cin >> N;

    if (N == 0) {
        COUT('#');
        return 0;
    }

    // 各カーペットをレベルが低い順に構築する
    ll block_size(1);
    vector<string> last_carpet(1, "#");
    REP(level, N) {
        vector<string> current_carpet(block_size * 3,
                                      string(block_size * 3, '#'));
        // 3 × 3の各ブロックごとに処理する
        REP(block_i, 3) REP(block_j, 3) {
            if (block_i == 1 and block_j == 1) {
                // 中央のブロック
                REP(i, block_size) REP(j, block_size) {
                    current_carpet[block_size * block_i + i]
                                  [block_size * block_j + j] = '.';
                }
            } else {
                // 中央以外の8ブロック
                // 3^K-1 × 3^K-1のカーペットを使う
                // ※ここの埋め方がわからなかった
                REP(i, block_size) REP(j, block_size) {
                    // 今処理しているのが縦横それぞれ何番目のブロックかを考慮し、1ブロック分オフセットする(block_size * block_i、block_size * block_j)
                    current_carpet[block_size * block_i + i]
                                  [block_size * block_j + j] =
                                      last_carpet[i][j];
                }
            }
        }
        block_size *= 3;
        dump(current_carpet);
        last_carpet = current_carpet;
    }

    REP(i, block_size) { COUT(last_carpet[i]); }
}

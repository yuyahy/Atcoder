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

// 自前実装(公式解説の最後の物とほぼ同じで、bit全探索と積が最大になるのは数字列が降順に並んでいるケースである事を利用する)
void solve1(ll N) {
    // Nの桁数と各桁の数字を求める
    ll digit(0);
    vll numbers;
    auto N_tmp = N;
    while (N_tmp) {
        numbers.push_back(N_tmp % 10);
        N_tmp /= 10;
        digit++;
    }
    dump(digit);
    dump(numbers);

    // {0, 1, ..., n-1} の部分集合の全探索
    ll max_mul(-1);
    for (int bit = 0; bit < (1 << digit); ++bit) {
        // グループわけ
        vector<ll> group_A, group_B;
        for (int i = 0; i < digit; ++i) {
            if (bit & (1 << i)) {
                group_A.push_back(numbers[i]);
            } else {
                group_B.push_back(numbers[i]);
            }
        }
        // dump(group_A);
        // dump(group_B);

        // 少なくともそれぞれのグループに1つは要素が含まれている必要がある
        if (group_A.size() == digit or group_B.size() == digit) continue;

        auto calc_combine_num = [&](vll& group) {
            // 積なのでそれぞれのグループの各数字を降順に並び替えた物が最も大きくなるはずなので、
            // 降順にソートした上で連結して1つの整数にする
            sort(ALL(group));
            reverse(ALL(group));
            dump(group);

            // 連結
            ll result(0);
            REP(i, group.size()) {
                result += pow(10, group.size() - i - 1) * group[i];
            }
            return result;
        };

        max_mul =
            max(max_mul, calc_combine_num(group_A) * calc_combine_num(group_B));
    }

    COUT(max_mul);
}

// 公式解説1(愚直に順列を生成する)
void solve2(ll N) {
    auto N_str = to_string(N);
    sort(ALL(N_str));
    ll max_mul(-1);
    do {
        // 2つのグループに分離する
        REP3(i, 1, N_str.size()) {
            string group_left, group_right;
            REP(j, i) group_left += N_str[j];
            REP3(j, i, N_str.size()) group_right += N_str[j];
            if (group_left[0] == '0' or group_right[0] == '0') continue;

            max_mul = max(max_mul, stoll(group_left) * stoll(group_right));
        }
    } while (std::next_permutation(ALL(N_str)));

    COUT(max_mul);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // - 取っ掛かりが不明
    // - ざっくり2つの正整数に分離する方法が何通りくらいあるのかを考察してみる
    //   →もし組み合わせが少ない & 実装できるのであれば全探索で解けるはず
    // - 2つのグループをそれぞれbitのON/OFFと対応づけて処理する

    // Note:
    // - 結果: {自力AC}
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 2種類のグループ分け & 組み合わせの数が大きくないのでbit全探索できると気がつけた事
    // - 改善点
    //      - 計算量の見積もりが甘かったかもしれない(愚直に順列は間に合うか確信が持てなかった)

    ll N(0);
    cin >> N;

    // solve1(N);
    solve2(N);
}

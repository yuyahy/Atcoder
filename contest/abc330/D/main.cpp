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
// 数字
const string integers = "0123456789";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0);
    cin >> N;
    vector<string> grids(N);

    REP(i, N) {
        string S;
        cin >> grids[i];
    }

    dump(grids);

    // 考察メモ
    // - 行方向は2つの◯の組み合わせ
    //      - 愚直にやるとN^2かかる
    //      - ここの高速化が思いつかない
    // - 列方向は累積和を予めとっておけば、O(1)で求められる

    // Note:
    // - 結果: 解説AC
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: 十分
    // - 考察: 不十分
    //      - 「行ごとに◯のインデックスを2つ選び、それぞれの列に存在する他の◯をカウントする」という方針しか思いつかなかった
    //      - 「探索の主役を変える事で計算量を減らせる、より簡潔な実装にできないか？」という問いかけが必要かも
    // - 実装: 十分

    // 各行・列の◯の数
    vector<ll> sum_row(N, 0), sum_column(N, 0);
    REP(i, N) {
        ll cnt(0);
        REP(j, N) {
            if (grids[j][i] == 'o') cnt++;
        }
        sum_row[i] = cnt;
    }
    REP(i, N) {
        ll cnt(0);
        REP(j, N) {
            if (grids[i][j] == 'o') cnt++;
        }
        sum_column[i] = cnt;
    }
    dump(sum_row);
    dump(sum_column);
    ll res(0);

    // 'L'の左下の頂点に相当するような、「マスのうち、丁度 2つが同じ行にある」 & 「マスのうち、丁度 2つが同じ列にある」
    // を満たす頂点に対して全探索する
    REP(i, N) REP(j, N) {
        if (grids[i][j] != 'o') continue;
        // 自身と同じ行にある'o'の数
        ll cnt_column = sum_column[i] - 1;
        // 自身と同じ列にある'o'の数
        ll cnt_row = sum_row[j] - 1;
        if (cnt_column < 1 || cnt_row < 1) continue;
        res += (cnt_column * cnt_row);
    }

    // 以下は考察時のコード
    // // 列方向の◯の数の累積和
    // vector<vector<ll>> accum_row(N, vector<ll>(N, 0));
    // REP(i, N) {
    //     ll cnt(0);
    //     REP(j, N) {
    //         if (grids[j][i] == 'o') cnt++;
    //         accum_row[j][i] = cnt;
    //     }
    // }
    // dump(accum_row);

    // // 列方向
    // ll res(0);
    // REP(i, N) {
    //     // 行方向
    //     // しゃくとりで共に'o'である様な(l, r)のペアを見つける
    //     int l = 0, r = 0;

    //     while (l < N) {
    //         if (r == N - 1 || grids[i][l] != 'o') {
    //             // 処理a
    //             ++l;
    //         } else {
    //             // 処理a'
    //             ++r;
    //         }
    //         dump(l, r);
    //         if (l >= N) break;
    //         // 処理b
    //         // l, rに対し、列方向にある'o'をカウントする
    //         ll cnt_l = accum_row[i][N - 1] - accum_row[i][l];
    //         ll cnt_r = accum_row[i][N - 1] - accum_row[i][r];
    //         res += (cnt_l + cnt_r);
    //     }
    // }

    cout << res << endl;
}

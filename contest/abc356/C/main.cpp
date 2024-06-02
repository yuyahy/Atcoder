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

    // テスト内容とその結果を管理する構造体
    struct Test {
        vll A;
        bool res;
    };

    ll N(0), M(0), K(0);
    cin >> N >> M >> K;

    vector<Test> test_result(M);
    REP(i, M) {
        ll C(0);
        cin >> C;
        vll a_tmp(C);
        REP(j, C) { cin >> a_tmp[j]; }
        string res;
        cin >> res;
        Test tmp;
        tmp.A = a_tmp;
        tmp.res = res == "o";
        test_result[i] = tmp;
        dump(test_result[i].A);
        dump(test_result[i].res);
    }

    // {0, 1, ..., n-1} の部分集合の全探索
    ll result(0);
    for (int bit = 0; bit < (1 << N); ++bit) {
        /* bit で表される集合の処理を書く */

        /* きちんとできていることを確認してみる */
        // bit の表す集合を求める
        vector<int> S;
        for (int i = 0; i < N; ++i) {
            if (bit & (1 << i)) {  // i が bit に入るかどうか
                S.push_back(i);
            }
        }

        // 条件と矛盾しないかチェック
        bool ok(true);
        for (const auto& test : test_result) {
            ll cnt(0);
            //　挿した鍵の中で、bitが立っている本数をカウント
            for (const auto& a : test.A) {
                if (bit & (1 << a - 1)) {  // i が bit に入るかどうか
                    cnt++;
                }
            }
            if (test.res and cnt < K) {
                // テスト結果は成功だが矛盾している
                ok = false;
                break;
            } else if (!test.res and cnt >= K) {
                // テスト結果は失敗だが矛盾している
                ok = false;
                break;
            }
        }
        if (ok) {
            result++;
            dump(S);
        }
    }
    COUT(result);
}
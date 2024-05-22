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
    // - 各インデックスについて自分より右側にいる[c,h,o,k,u,d,a,i]の数をカウントしておけば良い？
    // - 後は右から'c'を見つけたら組み合わせの問題
    // - しゃくとり？

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {不十分}
    //      - この問題は俗に言う「耳DP」、「chokudaiDP」という典型問題らしい
    //      - DP[位置][現在の状態]を管理するDP
    // - 考察: {不十分}
    //      - しゃくとりかな？とか思っていたがDPだった
    //      - 逆に今の自分が「これどうやって手をつければいいんだ？」という問題はDPかもしれない
    // - 実装: {不十分}
    //      - DPは毎度のごとく添字などでバグる。。。
    //      - 最初の提出でmint忘れた

    string S;
    cin >> S;
    dump(S);

    // テーブル定義: DP[i][j] Sのi番目までの文字を使って"chokudai"のj文字目までを選択する方法の数
    const string T("chokudai");
    vector DP(S.size() + 1, vector<mint>(T.size() + 1, 0));
    // 初期値
    // j=0の時は下線を全く引いていない状態なので1通り
    REP(i, S.size() + 1) DP[i][0] = 1;
    // i=0の時はSから一文字も選択していないので、"chokudai"のどの文字も選択できない
    REP3(j, 1, T.size() + 1) DP[0][j] = 0;
    // 漸化式
    // 1. Sのi文字目に下線が引ける or Sのi-1文字目までを使って"chokudai"のj文字目までを選択する: if(S[i] == chokudai[j]]) DP[i][j] = D[i-1][j] + DP[i-1][j-1]
    // 2. Sのi文字目に下線が引けない else  DP[i][j] = D[i-1][j]
    REP3(i, 1, S.size() + 1) REP3(j, 1, T.size() + 1) {
        if (S[i - 1] == T[j - 1]) DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
        else DP[i][j] = DP[i - 1][j];
    }

    dump(DP);
    COUT(DP[S.size()][T.size()].val());
}

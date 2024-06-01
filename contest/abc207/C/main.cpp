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

bool has_same_area(auto seg_right, auto seg_left, auto seg_other_right,
                   auto seg_other_left) {
    return max(seg_left, seg_other_left) <= min(seg_right, seg_other_right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(10);

    // 考察メモ
    // Nmax=2000なので多重ループ可能
    // 愚直に(i, j)ごとに共通区間をカウント？

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {不十分}
    //      - (知識と呼ぶべきなのか微妙だが)ある閉区間の比較は max(a,c)≤min(b,d)でできることを知らなかった
    // - 考察: {十分}
    //      - 基本方針→二重ループで全探索、開区間のまま処理するのは面倒なので適当な小数(e.g. 0.5)を足し引きして閉区間にするのは合っていた
    // - 実装: {十分}
    //      - 上記の区間の重複判定さえわかれば大丈夫
    // - メモ:
    //      - 開区間→閉区間の調整量を0.5とし、値に×2して整数に変換した上で比較すると浮動小数点を含まない計算にできる。
    //        →色々な問題で使えそうな考え方

    struct Segment {
        ll type;
        ll left;
        ll right;
    };

    ll N(0);
    cin >> N;
    vector<Segment> segments(N);
    REP(i, N) {
        ll t(0), l(0), r(0);
        cin >> t >> l >> r;
        segments[i] = Segment{t, l, r};
    }
    dump(segments);

    auto obtain_segment_edge =
        [&](const Segment segment) -> pair<double, double> {
        double seg_left(0), seg_right(0);
        // 以下の開区間を閉区間とみなすための操作量は0.1などでもOK。
        // ※ただし10^18レベルになると0.5でないと誤差が許容できないレベルになり、判定に失敗するらしい
        // https://note.com/momomo0214/n/nff11f69971bb
        //double diff = 0.001;
        double diff = 0.5;
        if (segment.type == 1) {
            seg_left = segment.left;
            seg_right = segment.right;
        } else if (segment.type == 2) {
            seg_left = segment.left;
            seg_right = segment.right - diff;
        } else if (segment.type == 3) {
            seg_left = segment.left + diff;
            seg_right = segment.right;
        } else {
            seg_left = segment.left + diff;
            seg_right = segment.right - diff;
        }
        return {seg_left, seg_right};
    };

    ll cnt(0);
    REP(i, N - 1) REP3(j, i + 1, N) {
        auto segment = segments[i];
        auto segment_other = segments[j];

        // 共通区間があるか判定する
        auto [seg_left, seg_right] = obtain_segment_edge(segment);
        auto [seg_other_left, seg_other_right] =
            obtain_segment_edge(segment_other);

        dump(seg_left, seg_right);
        dump(seg_other_left, seg_other_right);

        // 閉区間[a, b]と[c, d]が共通区間を持つかは以下で判定できる
        // max(a,c)≤min(b,d)
        if (has_same_area(seg_right, seg_left, seg_other_right, seg_other_left))
            cnt++;
    }
    COUT(cnt);
}

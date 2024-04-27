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

#define COUT(x) cout << (x) << endl
#define SCOUT(x) cout << (x) << " "
#define ENDL cout << endl

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

    // 考察メモ
    // - queueで処理するだけ？
    // - と思ったがcmax = 10^9なので、愚直にqueueから取り出すとTLEする
    // - c個取り出す = 連続したc個なので累積和的な考えが使えそう
    // - 実際にc個取り出す/追加するだと間に合わないので、c*xの様に一塊で挿入したい
    // - 何個残っているか？は具体的に管理してなくても問題ない(筒に残っているボールの総和と取り出されるボールの総和が管理できていればOK)
    // - ただし、今回は一塊を全て取り出すケースもあれば、中途半端に残るケースもあるため、dequeが良さそう

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - ぱっと見だとqueueを愚直にやれば良い問題に思えるが、制約条件に着目し、それだと間に合わない事が判断できた。
    // - 改善点
    //      - 今回の様な個数などの正の整数に対して、取り出す個数はstd::min()を使うと、if-elseより簡潔に実装できる

    ll Q(0);
    cin >> Q;
    // <数x, 何個あるか>
    deque<pair<ll, ll>> cylinder;
    REP(i, Q) {
        ll query(0);
        cin >> query;
        ll x(0), c(0);
        if (query == 1) {
            cin >> x >> c;
            dump(x, c);
            cylinder.push_back({x, c});
        } else {
            cin >> c;
            dump(c);
            ll idx(0), sum(0);
            while (true) {
                auto take_balls = std::min(c, cylinder[idx].second);

                sum += cylinder[idx].first * take_balls;
                cylinder[idx] = {cylinder[idx].first,
                                 cylinder[idx].second - take_balls};
                if (cylinder[idx].second == 0) cylinder.pop_front();

                // if (c < cylinder[idx].second) {
                //     // 一塊よりcが小さい場合
                //     sum += cylinder[idx].first * c;
                //     cylinder[idx] = {cylinder[idx].first,
                //                      cylinder[idx].second - c};
                // } else {
                //     // 一塊ピッタリ全部 or c > 一塊
                //     sum += cylinder[idx].first * cylinder[idx].second;
                //     cylinder.pop_front();
                // }
                c -= take_balls;
                if (c == 0) break;
            }
            COUT(sum);
        }
    }
}

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
typedef pair<ll, ll> pll;

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
    // - 数直線を考えてみる
    // - どういう時に区間同士をマージできる？
    //      - 2つの区間に重なる領域が存在する
    //      - 少なくとも一方の区間の始点はもう一方の区間内に存在する必要がある
    // - N=[1,2×10^5]なので愚直にループはできない
    // - 区間なのでマージ後は端点となる2点のみあればOK
    // - 始点が小さい順にソートし、先頭から貪欲にマージできればマージ、できなければ次の区間として始めるでOK？
    //      - 計算量はO(NlogN)

    // Note:
    // - 結果: 自力AC
    // {自力ACの場合}なぜ解けたか？
    // - ACに結びついた点
    //      - 区間の性質に着目し、マージできるかは右側の区間だけ見れば良く、延長するときは左側の区間だけ伸ばせば良い事に気がついた点
    //      - ChatGPTに雑投げし、実装アイデアが浮かんだ
    // - 改善点
    //      - 特になし

    ll N(0);
    cin >> N;

    vector<pll> intervals(N);
    for (auto& elem : intervals) cin >> elem.first >> elem.second;

    dump(intervals);
    // 貪欲にやるために事前に右側の区間に対して昇順でソートしておく
    std::sort(intervals.begin(), intervals.end());
    dump(intervals);

    vector<pll> merged_intervals;
    auto current = intervals[0];
    REP(i, N) {
        auto interval = intervals[i];
        if (interval.first ==
            std::clamp(interval.first, current.first, current.second)) {
            // マージできる場合は右側の区間を延長
            current.second = max(current.second, interval.second);
        } else {
            // マージできない場合は、これまでマージした区間を格納し、新たにスタート
            merged_intervals.push_back(current);
            current = interval;
        }
        // 最終ループのケア
        if (i == N - 1) merged_intervals.push_back(current);
    }
    for (const auto& elem : merged_intervals)
        cout << elem.first << " " << elem.second << endl;
}

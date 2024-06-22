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

// 公式解答(燃え尽きる時間Tを求め、T秒で左から燃える距離を求める)
void solve1() {
    ll N(0);
    cin >> N;
    // <左からi本目の導火線の長さ, 1秒あたりに燃える速さ>
    vector<pll> doukasen;
    REP(i, N) {
        ll A(0), B(0);
        cin >> A >> B;
        doukasen.push_back({A, B});
    }

    // 燃え尽きる時刻Tを求める
    // - 長さA、秒速Bcmで燃える導火線が片側から点火して燃え尽きるのにかかる時間は A/B
    // - この導火線を両端から同時に火をつけた場合に導火線が燃え尽きるのにかかる時間は (A/B)/2
    // - よって連結した導火線の両端から同時に火をつけた場合に導火線が燃え尽きるのにかかる時間Tは1/2*Σ(Ai/Bi)
    vector<double> burn_time;
    for (const auto& [A, B] : doukasen)
        // Note: キャストしないと1.0未満の結果の小数点以下が0で丸められる
        burn_time.push_back((double)A / (double)B);
    double sum = reduce(ALL(burn_time));
    double T = sum / 2;

    dump(T);

    // 時刻Tの時、左から何cmの位置にいるかを求める
    double pos(0.0);
    dump(burn_time);
    REP(i, N) {
        if (T - burn_time[i] > 0) {
            // 左からi番目が丸々燃やせる時
            pos += doukasen[i].first;
            T -= burn_time[i];
        } else {
            // 端数が残った時は残時間 * 残った導火線の燃える速度だけ進める
            dump(pos, T);
            pos += T * doukasen[i].second;
            break;
        }
    }
    COUT(pos);
}

// 考察時にイメージしていたが実装できなかった解答(dequeを使って両端をシミュレーション)
void solve2() {
    ll N(0);
    cin >> N;
    // <左からi本目の導火線の長さ, 1秒あたりに燃える速さ>
    deque<pair<double, double>> doukasen;
    REP(i, N) {
        double A(0.0), B(0.0);
        cin >> A >> B;
        doukasen.push_back({A, B});
    }

    // 導火線の燃えつきるまでの時間
    auto calc_burn_time = [&](const double length, const double velocity) {
        return length / velocity;
    };

    // 1.   両端から取り出す
    // 2-1. 燃え尽きるまでの時間が短い方→pop
    // 2-2. 長い方→短い方が燃えた時間を減算
    // 3.   要素が1つだけになったら残りの半分の時間
    // 4.   経過時間 * 先頭要素の燃える速度が進んだ距離
    double burn_pos(0.0);
    while (!doukasen.empty()) {
        // 先頭が燃え尽きるまでにかかる時間
        auto& front = doukasen.front();
        auto burn_time_front = calc_burn_time(front.first, front.second);
        if (doukasen.size() > 1) {
            // 末端が燃え尽きるまでにかかる時間
            auto& back = doukasen.back();
            auto burn_time_back = calc_burn_time(back.first, back.second);
            // 先頭は{先頭・末端の内、先に燃え尽きる方のかかる時間} * {先頭要素の燃える速度}分進む
            burn_pos += min(burn_time_front, burn_time_back) * front.second;
            if (burn_time_front > burn_time_back) {
                // 末尾が先に燃え尽きるケース
                front.first -= burn_time_back * front.second;
                doukasen.pop_back();
            } else {
                // 先頭が先に燃え尽きるケース
                back.first -= burn_time_front * back.second;
                doukasen.pop_front();
            }
        } else if (doukasen.size() == 1) {
            // 最後の一本のケースでは、残った長さの中央で燃え尽きる
            burn_pos += burn_time_front * front.second / 2;
            doukasen.pop_front();
        }
    }
    COUT(burn_pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // set precision (10 digit)
    cout << setprecision(16);

    // 考察メモ
    // - 答えは浮動小数点を含むケースがあるので注意
    // - dequeで導火線を管理するのが良い？
    // - かかる時間は最大で10^8 / 2くらい
    // - 両端をチェックしていけば計算量はO(N)ですむはず

    // 重み付きグラフとしても考えられるかもしれない

    // Note:
    // - 結果: {解説AC}
    // {解説ACの場合}どうすれば解けたか？
    // - 知識: {十分}
    //      - 特別な知識は必要ない
    // - 考察: {不十分}
    //      - 両端からシミュレーションするという方針は良い
    //      - シミュレーションの仕方(燃える速度は導火線によって異なる可能性がある、という所)が具体化できなかった
    //          - 実は単純な距離・速さ・時間の問題
    // - 実装: {不十分}
    //      -　解き直し時にミスが多かった気がする
    //      -　コメント書きながら整理していった方が手戻り少ないかも

    //solve1();
    solve2();
}

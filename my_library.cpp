
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
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))
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

// 動的にmodintの型を決める事ができるか不明なので、一旦定数にする
constexpr int mod = INT_MAX;
using mint_hash = static_modint<mod>;
class RollingHash {
   public:
    /**
     * @brief Construct a new Rolling Hash object
     *
     * @param str RollingHash対象の文字列
     * @param N strの文字列長(おそらくリファクタリングすれば引数にしなくても、str.lengh()から取れる値でいける)
     * @param hash_base ハッシュ値を計算する際のB進法の値
     *
     * @todo
     *        ハッシュ衝突のケア(B、Mは乱数にしないといけない？)
     */
    RollingHash(const string& str, const ll N, const ll hash_base)
        : m_digit_string(N + 1), m_hash(N + 1), m_hash_base_powers(N + 1) {
        // 入力文字列のi番目の文字をcharからintに変換
        // 0になると和差の計算上はあってもなくても変わらなくなってしまうので、
        // a=1, b=2,...z=26と対応させる
        REP3(i, 1, N + 1) m_digit_string[i] = (str[i - 1] - 'a') + 1;
        // 後の計算のためにB^iを前計算
        m_hash_base_powers[0] = 1;
        REP3(i, 1, N + 1) {
            m_hash_base_powers[i] = m_hash_base_powers[i - 1] * hash_base;
        }
        // Hash(S[1,1]),Hash(S[1,2]),...Hash(S[1,N])を前計算
        //   ここで、文字列S[1,i]はS[1,i-1]の後にT[i]を足した物なので、
        // Hash(S[1,i]) = B*Hash(S[i,i-1])+T[i]
        // ※ここで、B=B進法、T[i]=アルファベットのi番目を整数で表現した値
        // vector<mint_hash> hash(N + 1, 0);
        REP3(i, 1, N + 1) {
            m_hash[i] = (hash_base * m_hash[i - 1]) + m_digit_string[i];
        }
    }

    /**
     * @brief 指定区間[l,r]から文字列str[l,r]の部分のハッシュ値を求める
     *
     * @param l 部分文字列の先頭インデックス(閉区間、インデックスは1スタートなので注意)
     * @param r 部分文字列の末端インデックス(閉区間、インデックスは1スタートなので注意)
     * @return mint_hash
     */
    mint_hash calc_hash(const ll l, const ll r) {
        //
        return m_hash[r] - (m_hash_base_powers[r - l + 1] * m_hash[l - 1]);
    }

   private:
    // 入力文字列を1アルファベットごとに数字で表現した配列
    vector<ll> m_digit_string;
    // Hash(S[1,1]),Hash(S[1,2]),...Hash(S[1,N])のハッシュ値
    vector<mint_hash> m_hash;
    // B進法のB^iを計算した結果を保持する配列
    vector<mint_hash> m_hash_base_powers;
};

/**
 * @brief [x/m]の床関数(x/mを超えない最大の整数を求める)
 *
 * @param x
 * @param m
 * @return ll
 *
 * @note 負の整数の商を求める際に役に立つ
 *          e.g. C++の組み込みとの比較
 *          ・ll(-7 / 3) => -2
 *          ・floor(-7,3) => -3
 *          C++の組み込みは0に近い方に丸めるが、本関数は負の場合も考慮して求めている(ABC334の解答からコピー)
 *          数直線や数学的な処理を実装する際に、この関数を使って商を求めると、数学的な床関数としての結果が求めれられる
 *
 * https://math.nakaken88.com/textbook/cp-round-down-and-round-up/
 * https://zenn.dev/fjnkt98/articles/adfd2398b4eeeb
 *
 *
 */
ll floor(ll x, ll m) {
    // x を m で割った余りを計算し、m との合同を取ることで非負の余りに変換する
    ll r = (x % m + m) % m;

    // x から余りを引いて、m で割ることで商を計算する
    return (x - r) / m;
}

/**
 * @brief [x/m]の天井関数(x/mより大きい整数の中で最小の値を求める)
 *
 * @param x
 * @param m
 * @return ll
 * @note 整数同士の除算で天井関数を使いたい場合は本関数を使用するのがベター(ceilは10^15程度までしか正確に扱えない)
 */
ll ceil(ll x, ll m) { return (x + m - 1) / m; }

// nCk、組み合わせを求める関数
//
// usage:
// vector<vector<ll> > v(n + 1, vector<ll>(n + 1, 0));
// comb(v);
// v[n][k]が求めるnCkの値
void comb(vector<vector<ll> >& v) {
    for (ll i = 0; i < (ll)v.size(); i++) {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (ll k = 1; k < (ll)v.size(); k++) {
        for (ll j = 1; j < k; j++) {
            v[k][j] = (v[k - 1][j - 1] + v[k - 1][j]);
        }
    }
}

/**
 * @brief 整数numのN桁目のbitが立っているかを判定する
 *
 * @param num
 * @param N 2進数でのN桁目
 * @return true
 * @return false
 */
bool isNthBitSet(int num, int N) {
    // 1をNビット左シフトして、numとの論理積をとる
    // 結果が0でなければ、N桁目が立っている
    // ※N桁目というのは、２進数での桁数である点に注意
    //  →10進数をチェックする場合は、Nは2進数のbit数にしないといけないABC336 B問題参照
    return (num & (1 << N)) != 0;
}

/**
 * @brief int型の数値を2進数表現の文字列に変換
 *
 * @param number
 * @return std::string
 */
std::string intToBinaryString(int number) {
    return std::bitset<sizeof(int) * 8>(number).to_string();
}

/**
 * @brief 入力値の各桁の数字の和を返す
 *
 * @param num 今の所、正の整数しか考慮していないので、負の場合は絶対値で渡さないとダメかも
 * @return ll
 */
ll sum_digits(const ll num) {
    auto tmp = num;
    ll sum(0);
    while (tmp) {
        sum += tmp % 10;
        tmp /= 10;
    }
    return sum;
}

/**
 * @brief ダブリングのK回遷移した結果の値を求める時に使うラムダ式
 *
 * @param start 求めたい遷移の初期値
 * @param num_operation 求めたい遷移の回数(移動回数、操作回数...etc)
 * @note DP、MAXは参照キャプチャで取っている点に注意
 * @return ll
 */
auto calc_destination = [&](const ll start, const ll num_operation) {
    ll ans = start;
    // MAXは問題の制約を満たす様な数字を決めておく必要がある(e.g. 30など)
    REP_R(i, MAX) {
        if (isNthBitSet(num_operation, i)) ans = DP[i][ans];
    }
    return ans;
};

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};

/**
 * @brief グリッド処理などで時計回り or 反時計回り90度回転し、次の方向と移動座標を求める関数
 *
 * @param x 現在のx座標→移動先のx座標に更新される
 * @param y　現在のy座標→移動先のy座標に更新される
 * @param current_direction 現在の方向(上下左右)→次の方向に更新される
 * @param b_clockwise 時計回りに回転するか(デフォルト: true)
 */
void calc_next_direction(int& x, int& y, int& current_direction,
                         const bool b_clockwise = true) {
    if (b_clockwise) {
        // 時計回りに90度回転
        current_direction++;
    } else {
        // 反時計回りに90度回転
        current_direction += 3;
    }
    // 90度回転した方向と移動先の座標で更新する
    current_direction %= 4;
    y += dy_4[current_direction];
    x += dx_4[current_direction];
}

/**
 * @brief i番目の頂点からと繋がる辺の情報
 *
 * @note ダイクストラ法などで辺の情報を管理するのに使う
 */
struct Edge {
    // i番目の頂点とこの辺で結ばれている頂点の番号
    ll to;

    // 辺のコスト
    ll cost;
};
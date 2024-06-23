
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
void comb(vector<vector<ll>>& v) {
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

// midがkeyに対しての条件を満たすかどうか
bool isOK(ll mid, ll key) {
    // mid以下の要素を満たす物の個数を求めるラムダ式
    // ※設問によって、この関数とラムダ式の引数は拡張する必要あり
    auto count_satisfy_elements = [&](const ll x) {
        // 参照キャプチャなので外のスコープの変数もいじれる
    };
    ll result = count_satisfy_elements(mid, m, n);
    dump(result);
    // mid以下の要素を満たす物の個数が、今回求めるkeyより大きければ、境界の右側にいることを意味する
    if (result >= key) return true;
    else return false;
}

/**
 * @brief 二分探索のテンプレート(めぐる式)
 *
 * @param key   比較対象の値(a[index] >= key という条件の探索対象)
 * @param ok    条件を満たす最大の初期値
 * @param ng    条件を満たさない最小の初期値
 * @return ll
 * @note 現状は条件を満たす最小の値を求めているが、設問によっては条件を満たす最大の値を返すパターンもある
 *       その場合は調べて改造して使用する必要がある
 */
ll binary_search(const ll key, ll ok, ll ng) {
    // ok と ng のどちらが大きいかわからないことを考慮
    while (abs(ok - ng) > 1) {
        ll mid = (ok + ng) / 2;
        dump(key, ok, ng, mid);
        dump(mid);

        // 今見ているmidが条件を満たせば、右側の探索範囲を半分にする
        // そうでなければ左側の探索範囲を半分にする
        if (isOK(mid, key)) ok = mid;
        else ng = mid;
    }
    // 答えはwhileを抜けた時のokの値
    return ok;
}

/**
 * @brief 文字列の中の特定の文字を別の文字に置換する
 *
 * @param str
 * @param target
 * @param replacement
 */
void replaceChars(std::string& str, char target, char replacement) {
    size_t pos = 0;
    while ((pos = str.find(target, pos)) != std::string::npos) {
        str[pos] = replacement;
        ++pos;
    }
}

/**
 * @brief 閉区間[seg_left, seg_right]と[seg_other_left, seg_other_right]が共通区間を持つか判定する
 *
 * @param seg_right
 * @param seg_left
 * @param seg_other_right
 * @param seg_other_left
 * @return true
 * @return false
 * @note 引数の型はint, ll doubleなどでOKにできる様にautoを使用
 *
 * https://atcoder.jp/contests/abc207/editorial/2152
 */
bool has_same_area(auto seg_right, auto seg_left, auto seg_other_right,
                   auto seg_other_left) {
    return max(seg_left, seg_other_left) <= min(seg_right, seg_other_right);
}

/**
 * @brief 累積和の配列を求めるテンプレート関数
 *
 * @tparam T            任意の型(和が定義されていないとエラー or 未定義動作になる想定)
 * @param array         累積和を求める対象の配列
 * @return vector<T>    arrayの累積和を格納した配列
 */
template <typename T>
vector<T> obtain_cumulative_array(const vector<T>& array) {
    vector<T> accum_array(array.size());
    inclusive_scan(ALL(array), accum_array.begin());
    return accum_array;
}

/*
    DFSのラムダ関数のテンプレート
    頂点数N、辺数Mの場合にO(N+M)
    ※seen変数で同じ頂点を何回も訪問しない様にしないとTLEするケースが多い
    ※返り値が欲しいケースなど、設問に合わせて適宜変更する
*/
//その頂点が既に訪問済みかを表現する
// vector<bool> seen(N, false);
// auto dfs = [&](auto self, const vector<vector<ll>>& Graph, const ll vertex,
//                vector<bool>& seen) -> void {
//     // 訪問済みの頂点として記録
//     seen[vertex] = true;

//     // 何らかの処理

//     // 現在注目している頂点と隣接している頂点に対して再帰
//     for (const auto next_vertex : Graph[vertex]) {
//         if (seen[next_vertex]) continue;
//         self(self, Graph, next_vertex, seen);
//     }
// };

// // {0, 1, ..., n-1} の部分集合の全探索
// for (int bit = 0; bit < (1 << n); ++bit) {
//     /* bit で表される集合の処理を書く */

//     /* きちんとできていることを確認してみる */
//     // bit の表す集合を求める
//     vector<int> S;
//     for (int i = 0; i < n; ++i) {
//         if (bit & (1 << i)) {  // i が bit に入るかどうか
//             S.push_back(i);
//         }
//     }

//     // bit の表す集合の出力
//     cout << bit << ": {";
//     for (int i = 0; i < (int)S.size(); ++i) {
//         cout << S[i] << " ";
//     }
//     cout << "}" << endl;
// }
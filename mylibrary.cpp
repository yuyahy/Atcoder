
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
     * @param str
     *        RollingHash対象の文字列
     * @param N
     *        strの文字列長(おそらくリファクタリングすれば引数にしなくても、str.lengh()から取れる値でいける)
     * @param hash_base
     *        ハッシュ値を計算する際のB進法の値
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
     * @param l
     *        部分文字列の先頭インデックス(閉区間、インデックスは1スタートなので注意)
     * @param r
     *        部分文字列の末端インデックス(閉区間、インデックスは1スタートなので注意)
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

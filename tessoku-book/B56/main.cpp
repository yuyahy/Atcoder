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
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))

#include <bits/stdc++.h>

#include <atcoder/all>

using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

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
     * @param l 部分文字列の先頭インデックス(閉区間)
     * @param r 部分文字列の末端インデックス(閉区間)
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

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll N(0), Q(0);
    cin >> N >> Q;
    string S("");
    cin >> S;

    // 逆順文字列を生成
    string S_revered(S.rbegin(), S.rend());
    dump(S_revered);

    constexpr int hash_base = 100;
    auto rolling_hash = RollingHash(S, N, hash_base);
    auto rolling_hash_reversed = RollingHash(S_revered, N, hash_base);

    // 文字列とその文字列を反転させた物の部分文字列のハッシュ値を比較し、
    // 回文かを判定する
    ll L(0), R(0);
    REP(i, Q) {
        cin >> L >> R;
        auto hash = rolling_hash.calc_hash(L, R);
        // 文字列を逆転させた物なので、区間も反転することに注意
        swap(L, R);
        dump(N - L);
        dump(N - R);
        auto hash_reversed =
            rolling_hash_reversed.calc_hash(N - L + 1, N - R + 1);
        auto result = hash == hash_reversed ? "Yes" : "No";
        cout << result << endl;
    }
}

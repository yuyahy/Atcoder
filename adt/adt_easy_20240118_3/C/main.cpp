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

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
    // set precision (10 digit)
    cout << setprecision(10);
    ll N(0);
    cin >> N;

    // Note: 以下の方針は、Aijが1〜9の一桁の数値であれば上手くいくが、今回のケースでは0や複数の桁があるので上手くいかない
    // →数値に変換し、setでカウントする

    // Note: 計算量の見積もりが誤っており(厳しく評価しすぎた)、時間をかけてしまったが、std::setは要素の追加をO(logN)で行える
    //       そして、vector同士の比較は、仮に要素数が等しいとするとO(N)で行える。
    //       また、数列の格納に計O(ΣLi)かかるので、全体でO((N + ΣLi)logN)程度で処理できる
    //       →ポイントは、vectorの比較はO(N)だが、setを使う事で、挿入一回O(logN)で重複チェックもされるので、充分高速であるという所だと思う。
    //        また、本設問では制約がN:10^5、L:10^5なので解けるが、10^8レベルになると比較部分のO(N)がボトルネックになると考えられる
    set<vector<ll>> num_set;
    REP(i, N) {
        ll L(0), tmp(0);
        ll nums(0);
        cin >> L;
        vector<ll> array(L);
        REP(j, L) { cin >> array[j]; }
        num_set.insert(array);
    }

    dump(num_set);

    cout << num_set.size() << endl;
}

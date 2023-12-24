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

ll floor(ll x, ll m) {
    // x を m で割った余りを計算し、m との合同を取ることで非負の余りに変換する
    ll r = (x % m + m) % m;

    // x から余りを引いて、m で割ることで商を計算する
    return (x - r) / m;
}

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
    // set precision (10 digit)
    cout << setprecision(10);

    ll A(0), M(0), L(0), R(0);
    cin >> A >> M >> L >> R;
    ll ans(0);
    // すねけくんを0地点にスライドさせる
    L -= A;
    R -= A;
    A = 0;

    dump(A);
    dump(R);
    dump(L);
    // Note:
    // この問題の基本方針は以下。
    // ・{区間[L,R]の範囲内にある最も右側の木の番号} - {区間[L,R]の範囲にある最も左側の木から-1した番号}
    // しかし、この問題には以下のトラップがあり、何となくで実装してもACできない
    // ・Lが負、Rが正の場合は、単純にabs(L)/Mで最も左側の木から-1した番号を求めると不正解(少なくともC++では)
    // →e.g.  ll(-5 / 3) = -1となるが、今回は-5に最も近い範囲外の木の番号を求めたいので、もう一個外側の-2がほしい
    //
    //        (L,R)=(-7,5), M=3
    //                       ↓最も右側にある[L,R]内の木
    //       ----×-L×--×--×(原点)--×-R×-------
    //           ↑  ↑計算結果
    //           ↑ここが欲しい(最も左側にある[L,R]の一本外側の木)
    //
    // これはC++の除算の丸め方が0に近い方向に丸めるという仕様が関係している
    //　なお、L,Rが共に負の場合は、引き算をする時に上記の部分が打ち消し合うので問題ない想定。
    //
    // 以上を踏まえると、原点とL,Rを位置関係3パターン((L,R)=(正,正),(負,正),(負,負))で場合分けするのは中々面倒
    // →パターンごとに最も近い外側の位置を求めるのか、範囲内にギリギリ収まっているかが違うため
    //
    // よって、A=0に移動させた上で、更にLが負の場合は、充分に大きく(L,R)を右(正)の方向に移動させると、(L,R)=(正,正)
    // のケースだけ考えれば良くなり楽になる

    // 上記より、Lが0or負の場合に計算式を変えたくないので、正の方向にスライドさせる
    // Note: ここは適当に大きい数字 e.g. 1e18+1とかやってはいけない。
    //       なぜなら、木は原点を基準に、[0,1*M,2*M,3*M...k*M]で正と負の方向に生えているため、
    //       M+1など、Mで割り切れない量だけずらしてしまうと、境界のちょうど[L,R]上に木があるケースの結果が
    //       移動前後で変わってしまうケースがある
    //
    //       (L,R)=(-7,5), M=3, ans=4
    //
    //       ----×-L×--×--×(原点)--×-R×-------
    //
    //       ↓これを3*M + 1=10だけずらすと、、、
    //       (L,R)=(3,15), M=3, ans=5(結果が変わっている)
    //
    //       ----×--×--×--×(原点)--×(L)--×--×--×--×(R)
    //
    //       よってずらす量Xは、Lが正の値になる & X=k*Mを満たす様な値でないといけない
    if (L == 0) {
        int a = 0;
    }
    if (L <= 0) {
        // ※正(0より大きい)になる様に+1している
        auto k = ((abs(L) / M) + 1);
        auto X = k * M;
        L += X;
        R += X;
    }
    dump(R);
    dump(L);
    auto f = [&](const ll r, const ll m) { return r / m; };

    ans = f(R, M) - f(L - 1, M);
    cout << ans << endl;
}

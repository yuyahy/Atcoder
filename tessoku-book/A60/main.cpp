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

    int N(0);
    cin >> N;
    vector<int> A(N, 0);
    REP(i, N) cin >> A[i];

    // Note: 図示した棒グラフより、注目している株価から左に探索していき、
    //       最初に遭遇した自分より高い株価の日が答えになる。これを実装するには、
    //       stackを使用し、自分より前の日付の株価の中から、自分より大きい物がでるまで、最初の要素を取り除き、
    //       あればそれが求める日付、stackが空になったら該当日なしである。
    //       →左に進んでいった際に、最高値を更新する物だけ記録しておけば良いのがポイント。
    //        また、アルゴリズム的に高々要素数の分しか、要素の追加と削除は行われないのでO(N)である

    // <インデックス, 価格>
    stack<pair<int, int>> prices;
    REP(i, N) {
        // stackから直近のインデックスの物を取り出し、注目要素より大きい物を探す
        while (!prices.empty()) {
            auto top = prices.top();
            if (top.second > A[i]) {
                cout << top.first << " ";
                break;
            }
            prices.pop();
        }
        // 見つからなかった場合
        if (prices.empty()) {
            cout << -1 << " ";
        }
        prices.push({i + 1, A[i]});
    }
    cout << endl;
}

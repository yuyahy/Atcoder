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
    ll N(0), X(0);
    cin >> N >> X;
    ll L(0);
    // 各袋に各整数が何個ずつ入っているか
    vector<vector<ll>> balls(N);
    REP(i, N) {
        cin >> L;
        ll tmp(0);
        REP(j, L) {
            cin >> tmp;
            balls[i].push_back(tmp);
        }
    }

    dump(balls);

    // DFSのためのラムダ関数
    // →全頂点を探索するのにO(N)、全ての辺を探索するのにO(M)かかるので、全体の計算量はO(N+M)
    //  ※隣接行列で処理するとO(N^2)になる点に注意

    // Note: グラフ構造だけでなく、この様な多重ループ系の全探索にもDFSは適用できる
    //       ※袋の個数はパラメータによって異なるため、ネストしたforループは書けないので、DFSを採用するのがポイント
    auto dfs = [&](auto self, const vector<vector<ll>>& balls, ll product,
                   int& cnt, int bag) -> void {
        // [1, N]までのバッグを確認したら、再帰から戻る
        if (bag == N) {
            if (product == X) cnt++;
            return;
        }
        // 現在注目しているバッグとそのバッグに入っている玉に対して再帰
        for (const auto ball : balls[bag]) {
            if (product > X) continue;
            self(self, balls, product * ball, cnt, bag + 1);
        }
    };

    bool b_dfs(false);
    vector<ll> results;
    int cnt(0), bag(0);
    ll product(1);
    if (b_dfs) dfs(dfs, balls, product, cnt, bag);
    else {
        // BFSで解いたバージョン
        // 基本方針はDFSと一緒だが、こちらは再帰の代わりにqueueとwhileで全探索している
        // →DFSの方が処理は簡潔かもしれない
        // <現在までの積, 現在注目している袋の番号>
        queue<pair<ll, ll>> bfs_queue;
        for (const auto& ball : balls[bag]) bfs_queue.push({ball, bag});
        while (!bfs_queue.empty()) {
            auto [current_product, current_bag] = bfs_queue.front();
            bfs_queue.pop();
            // 葉のノードまで到達したら、積をチェック
            if (current_bag == N - 1) {
                if (current_product == X) cnt++;
                continue;
            }
            for (const auto& ball : balls[current_bag + 1]) {
                // atest_subだとOKだが、atestだと一部テストケースでオーバーフローの警告エラー発生
                if (current_product > X) continue;
                bfs_queue.push({current_product * ball, current_bag + 1});
            }
        }
    }

    cout << cnt << endl;
}

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

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0);
  cin >> N;

  // 逆から辿っていって、必要な数のポーションだけ拾っていく
  ll ti(-1);
  ll xi(-1);
  // i個目のイベントのモンスター
  vector<pair<ll, ll>> monster_events;
  int potion_Cnt(0);

  // イベントの順番と対応するイベント番号
  map<ll, ll> potion_sequence;

  int Kmin(0), K(0);

  vector<ll> events(N, 0);
  for (ll i = 0; i < N; i++) {
    cin >> ti >> xi;
    if (ti == 1) {
      // ポーション
      events[i] = xi;
    } else {
      // モンスター
      events[i] = -xi;
    }
  }
  // Note:
  // 本番中に最初に思いついた、逆から辿っていく解法で良かった
  // 途中で、先頭から辿っていく方針にしてしまったが、この場合は最小のKを満たすために、
  // stackなどを用いて、モンスター遭遇時に最も直近で拾えるポーションを使う工夫をしないといけない
  // そして、先頭から探索するとモンスター遭遇時にどのイベントのポーションを拾うorわないかが決まるので、
  // 地味にその管理が面倒(でも答えでは行動を出力しないといけない)
  //
  // また、ポーションごとの配列、モンスターごとの配列...とやっていくと管理するための変数が多くなり、
  // 結構面倒なので、一種類の配列でイベントをまとめて管理し、ポーションとモンスターで符号を反転させると
  // 実装が楽になる

  // まとめ
  // 1.最小値を求める探索系は、逆から辿って必要な最小個数だけ取得する様な方針が良さげ
  // 2.複数のコンテナを定義する前に、一種類でまとめられないかを検討する
  // 3. コメント書きながら丁寧に実装した方が良い

  // イベントを逆から辿っていき、最も近いポーションだけ拾う
  std::reverse(events.begin(), events.end());
  // 現時点のモンスターの種類とその数
  map<int, int> monster_types;
  // 現在残っているモンスターの数
  int remain_monster_cnt(0);
  // i番目のポーションを拾うか
  vector<int> used_potions;
  for (const auto& event : events) {
    if (event < 0) {
      // モンスター
      monster_types[-event]++;
      K++;
      remain_monster_cnt++;
    } else {
      // ポーション
      // 倒す必要があれば、そのポーションを拾う
      auto potion = event;
      if (monster_types[potion] > 0) {
        // 拾うパターン
        monster_types[potion]--;
        used_potions.push_back(1);
        remain_monster_cnt--;
        K--;
      } else {
        // 拾わないパターン
        used_potions.push_back(0);
      }
    }
    Kmin = max(Kmin, K);
  }
  if (remain_monster_cnt > 0) {
    cout << -1 << endl;
  } else {
    cout << Kmin << endl;
    std::reverse(used_potions.begin(), used_potions.end());
    for (const auto& elem : used_potions) {
      cout << elem << " ";
    }
    cout << endl;
  }
}

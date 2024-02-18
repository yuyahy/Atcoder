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
#define REP3R(i, m, n) for (int i = (int)(m)-1; (i) >= (int)(n); --(i))

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

// 4近傍(左上原点)
// Y = (↑, そのまま, ↓, そのまま)
// X = (そのまま, →, そのまま, ←)
const int dy_4[4] = {-1, 0, 1, 0};
const int dx_4[4] = {0, 1, 0, -1};
// 8近傍
const int dy_8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx_8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    // set precision (10 digit)
    // cout << setprecision(10);

    int N(0), K(0);
    cin >> N >> K;
    // vector<ll> A(K, 0);
    map<ll, bool> have_light;
    REP(i, K) {
        ll tmp(0);
        cin >> tmp;
        have_light[tmp] = true;
    }

    ll X(0), Y(0);
    // 探索する座標
    struct point {
        ll x;
        ll y;
    };

    vector<point> Points(N);
    vector<point> Lights;
    REP(i, N) {
        cin >> X >> Y;
        Points[i] = point(X, Y);
        if (have_light[i + 1]) Lights.push_back(point(X, Y));
    }
    // 灯りを持っていない人物から、灯りへの最短距離を求める
    // 求めた最短距離の中で最も距離が大きい物が、ギリギリ全員を照らすために必要な半径
    double longest_distance(0.0);
    REP(i, N) {
        double nearest_light(1e12);
        // 灯りを持っている人は対象外
        if (have_light[i + 1]) continue;
        for (const auto& elem : Lights) {
            double distance =
                std::hypot(elem.x - Points[i].x, elem.y - Points[i].y);
            nearest_light = std::min(nearest_light, distance);
        }
        longest_distance = std::max(longest_distance, nearest_light);
    }
    cout << longest_distance << endl;
}

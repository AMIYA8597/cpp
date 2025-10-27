// F. The Galactic Treasure Hunt
// time limit per test2 seconds
// memory limit per test512 megabytes
// Jack, a renowned space explorer, is on a quest to find the mythical Star Gem hidden deep on the planet Xylos.

// He starts his journey from his home base — the space station Alpha — and must travel through the Galactic Travel Network to reach Xylos.

// The universe is connected by a network of one-way warp-gates. Each warp-gate connects two space stations and costs some amount of Cosmic Credits to traverse.

// Jack also possesses a powerful artifact: the Galactic Coupon. He can use this coupon exactly once on any single warp-gate during his journey.

// If the warp-gate normally costs X
//  credits, then using the coupon reduces its cost to ⌊X2⌋
// .

// Your mission is to help Jack plan his route from station 1
//  (Alpha) to station n
//  (Xylos) such that the total travel cost is minimized, using the coupon exactly once.

// If there is no valid route, output -1.

// Input
// The first line contains two integers n
//  and m
//  (2≤n≤105
// , 1≤m≤2×105
// ) — the number of space stations and the number of warp-gate connections.

// Each of the next m
//  lines contains three integers u
// , v
// , and w
//  (1≤u,v≤n
// , u≠v
// , 1≤w≤109
// ) — a one-way warp-gate from station u
//  to station v
//  with cost w
// .

// You start from station 1
//  and need to reach station n
// .

// Output
// Print a single integer — the minimum total cost to travel from station 1
//  to station n
// , using the coupon exactly once.

// If there is no valid path, print -1.

// Example
// InputCopy
// 5 7
// 1 2 3
// 2 3 4
// 3 5 3
// 1 4 10
// 4 3 2
// 2 5 8
// 4 5 3
// OutputCopy
// 7
// Note
// One optimal path is 1→2→5
// .

// The total cost without using the coupon is 3+8=11
// .

// If Jack uses the coupon on the warp-gate 2→5
// , the cost of that edge becomes ⌊8/2⌋=4
// .

// So the total cost becomes 3+4=7
// , which is the minimum possible.



































#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int MOD = 1e9+7;

struct Edge {
    int v, w;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    // dist[u][0] -> min cost to reach u without using coupon
    // dist[u][1] -> min cost to reach u after using coupon
    vector<vector<int>> dist(n + 1, vector<int>(2, INF));
    dist[1][0] = 0;

    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    pq.push({0, 1, 0}); // {cost, node, couponUsed?}

    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d != dist[u][used]) continue;

        for (auto &e : g[u]) {
            int v = e.v, w = e.w;

            // 1️⃣ Normal move (no coupon used yet)
            if (d + w < dist[v][used]) {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }

            // 2️⃣ Use coupon if not yet used
            if (!used && d + w / 2 < dist[v][1]) {
                dist[v][1] = d + w / 2;
                pq.push({dist[v][1], v, 1});
            }
        }
    }

    long long ans = dist[n][1];
    if (ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}



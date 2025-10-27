// C. The Great Highway Collision
// time limit per test1 second
// memory limit per test256 megabytes
// As the traffic controller overlooking this unique stretch of highway, your task is to predict the final lineup of surviving vehicles after all collisions have played out.

// You are given an initial list of cars. The absolute value of each car's number represents its size or mass, indicating its toughness. The sign of the number determines its direction:

// A positive number means the car is driving to the right.
// A negative number means the car is driving to the left.
// Critically, all cars travel at the same speed. Consequently, crashes only ever occur when a right-moving car meets a left-moving car; cars moving in the same direction will never collide.

// When a crash happens, the outcome depends on the vehicles' sizes:

// If they are of unequal size, the car with the smaller mass is completely destroyed, and the larger car continues moving.
// If they are of equal size, both vehicles are destroyed and removed from the highway.
// Your ultimate goal is to process these destructive encounters until no more head-on collisions are possible, and then report the final list of cars still successfully driving.

// Input
// The first line contains a single integer n
//  (1≤n≤105
// ) — the number of cars on the highway.

// The second line contains n
//  integers a1,a2,…,an
//  (−103≤ai≤103
// , at least one ai≠0
// ) — representing the cars. Here, |ai|
//  denotes the mass of the car, and the sign indicates its direction (+
//  for right, −
//  for left).

// Output
// Print the final list of cars that remain after all collisions. Output the numbers in the same order as they appear from left to right, separated by spaces. If no cars remain, print an empty line.

// Example
// InputCopy
// 3
// 5 10 -5
// OutputCopy
// 5 10
// Note
// In the given example, the cars have masses of 5, 10, and 5 respectively. Cars 1 and 2 are moving to the right, and Car 3 is moving to the left. Cars 2 and 3 collide, and since 10 > 5, Car 3 is completely destroyed, leaving only Cars 1 and 2.









































#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int n;
    // cin >>n;
    // vector<int> cars(n);
    // for(int int i =0; i<n; ++i) cin >> cars[i];

    int n;
    cin >> n;
    vector<int> cars(n);
    for (int i = 0; i < n; ++i) cin >> cars[i];

    stack<int> st;
    for (int car : cars) {
        bool destroyed = false;

        while (!st.empty() && st.top() > 0 && car < 0) {
            if (abs(st.top()) < abs(car)) {
                st.pop();
                continue;
            } else if (abs(st.top()) == abs(car)) {
                st.pop();
                destroyed = true;
                break;
            } else {
                destroyed = true;
                break;
            }
        }

        if (!destroyed) st.push(car);
    }


    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    reverse(result.begin(), result.end());

    for (int i = 0; i < (int)result.size(); ++i) {
        cout << result[i] << (i + 1 == result.size() ? '\n' : ' ');
    }

    return 0;
}

// D. AlgoBlitz Seating Challenge
// time limit per test1 second
// memory limit per test256 megabytes
// AlgoBlitz, a famous coding competition, is being held in a vast hall, but only certain spots are suitable for setting up a desk and computer.

// You are given an array with unique elements of seats
// , which represents the available positions where a participant can sit. You are also given an integer k
//  which is the total number of participants.

// The organizers need to assign the k
//  participants to k
//  of the available seats such that the minimum distance between any two participants is the maximum possible.

// Your job is to determine the single greatest possible value for this "maximum minimum distance."

// Input
// The first line contains two integers N
//  and k
//  (2≤N≤105
// , 2≤k≤N
// ), representing the number of available seats and the number of participants, respectively.

// The second line contains N
//  distinct integers seats1,seats2,…,seatsN
//  (0≤seatsi≤106
// ), representing the positions of the available seats.

// Output
// Output a single integer, which is the maximum possible minimum distance between any two participants.

// Example
// InputCopy
// 5 3
// 10 1 2 7 5
// OutputCopy
// 4
// Note
// For the given example, when n=5
//  and k=3
// :

// The first participant can be placed at seat1
// .
// The second participant can be placed at seat2
// .
// The third participant can be placed at seat5
// .
// Thus, the minimum distance between any two participants in this case is 4
// , which is the largest among all possible ways.

















#include <bits/stdc++.h>
using namespace std;

bool canPlace(vector<int> &seats, int k, int dist) {
    int count = 1, last = seats[0];
    for (int i = 1; i < (int)seats.size(); i++) {
        if (seats[i] - last >= dist) {
            count++;
            last = seats[i];
            if (count == k) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> seats(n);
    for (int i = 0; i < n; i++) cin >> seats[i];
    
    sort(seats.begin(), seats.end());
    
    int low = 0, high = seats.back() - seats.front(), ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canPlace(seats, k, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}

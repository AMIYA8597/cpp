3568. Minimum Moves to Clean the Classroom
Medium
Topics
premium lock icon
Companies
Hint
You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:

'S': Starting position of the student
'L': Litter that must be collected (once collected, the cell becomes empty)
'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
'X': Obstacle the student cannot pass through
'.': Empty space
You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.

Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.

Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.

 

Example 1:

Input: classroom = ["S.", "XL"], energy = 2

Output: 2

Explanation:

The student starts at cell (0, 0) with 2 units of energy.
Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
The student collects all the litter using 2 moves. Thus, the output is 2.
Example 2:

Input: classroom = ["LS", "RL"], energy = 4

Output: 3

Explanation:

The student starts at cell (0, 1) with 4 units of energy.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of energy used and 3 units remaining.
Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to 4.
Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
The student collects all the litter using 3 moves. Thus, the output is 3.
Example 3:

Input: classroom = ["L.S", "RXL"], energy = 3

Output: -1

Explanation:

No valid path collects all 'L'.

 

Constraints:

1 <= m == classroom.length <= 20
1 <= n == classroom[i].length <= 20
classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
1 <= energy <= 50
There is exactly one 'S' in the grid.
There are at most 10 'L' cells in the grid.



























  class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        vector<pair<int, int>> litter;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } else if (classroom[r][c] == 'L') {
                    litter.push_back({r, c});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int states = 1 << k;
        int fullMask = states - 1;

        vector<int> best(m * n * states, -1);

        auto index = [&](int r, int c, int mask) {
            return (r * n + c) * states + mask;
        };

        struct State {
            int r;
            int c;
            int mask;
            int e;
        };

        queue<State> q;

        best[index(sr, sc, 0)] = energy;
        q.push({sr, sc, 0, energy});

        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                State cur = q.front();
                q.pop();

                if (cur.mask == fullMask)
                    return moves;

                if (cur.e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = cur.e - 1;
                    int nmask = cur.mask;

                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    if (classroom[nr][nc] == 'L') {
                        nmask |= 1 << id[nr][nc];
                    }

                    int idx = index(nr, nc, nmask);

                    if (ne <= best[idx])
                        continue;

                    best[idx] = ne;

                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};


















1. First understand the problem

We have a grid:

S = starting position
L = litter
R = recharge/reset
X = wall
. = empty

The student has some maximum energy:

energy = E

Every movement:

up / down / left / right

costs:

1 energy

When the student enters R:

energy = E

We need:

Minimum number of moves required to collect all litter.

There can be at most:

10 litter cells

That 10 is extremely important.

2. Why ordinary BFS isn't enough

Suppose we only stored:

(row, col)

That doesn't work.

Consider:

        L
        |
        .
        |
S ------

Imagine we reach the same cell twice:

State A:
position = (3,3)
energy = 15

State B:
position = (3,3)
energy = 2

These are not equivalent.

From A, we can travel much farther.

So we need to remember energy.

3. But energy isn't the only thing

Suppose we reach:

(3,3), energy = 10

once before collecting litter A:

mask = 000

and another time after collecting litter A:

mask = 001

These are also different.

Why?

Because the goal is to collect all litter.

Therefore we also need to know:

Which litter has already been collected?

This leads to the state:

(row, col, mask, energy)
4. What is a state?

A state describes everything that matters about the future.

We use:

(r, c, mask, e)

where:

r    = current row
c    = current column
mask = collected litter
e    = remaining energy

For example:

(5, 7, 101001, 12)

means:

position = (5,7)
some specific litter items collected
energy = 12
5. Bitmask concept

This is one of the most important concepts in this problem.

There are at most:

k <= 10

litter cells.

We can assign IDs:

L0 -> 0
L1 -> 1
L2 -> 2
L3 -> 3
...

Then use bits.

For example, with 4 litter:

mask = 0101

means:

L0 collected
L1 not collected
L2 collected
L3 not collected

Because:

0101
||||
||||
||||---- L0 = 1
|||----- L1 = 0
||------ L2 = 1
|------- L3 = 0
6. Why bitmask is perfect here

If there are k litter cells, each litter has two possibilities:

collected
not collected

Therefore number of possible combinations:

2^k

With:

k <= 10

we get:

2^10 = 1024

That's small enough.

This is a classic signal:

"At most 10 important objects" → think Bitmask.

You'll see this pattern in:

Traveling Salesman
Visit all nodes
Keys and doors
Collect all items
Maximum compatibility
Subset DP
Grid collection problems
7. How do we mark litter as collected?

Suppose litter id = 3.

We set:

mask |= (1 << 3);

1 << 3:

0001
shift left 3

1000

Then:

mask |= 1000;

If mask was:

0101

we get:

1101

Now litter 3 is marked collected.

8. How do we check whether all litter is collected?

If there are k litter cells:

int fullMask = (1 << k) - 1;

For:

k = 4

we get:

1 << 4 = 10000

minus 1:

01111

So:

mask == fullMask

means:

Every litter has been collected.

9. Why BFS?

Every movement costs exactly:

1

This is exactly what BFS is designed for.

Imagine:

level 0 → starting state
level 1 → states reachable in 1 move
level 2 → states reachable in 2 moves
level 3 → states reachable in 3 moves
...

Therefore:

The first time BFS reaches the goal, that is the minimum number of moves.

This is a fundamental BFS property.

10. Basic BFS structure

Conceptually:

queue<State> q;

q.push(start);

while (!q.empty()) {
    State cur = q.front();
    q.pop();

    for (each neighbor) {
        create next state;
        q.push(next);
    }
}

Because every edge has weight 1, this gives shortest distance.

11. Movement

For every state, there are at most 4 movements:

        UP
         ↑
LEFT ← current → RIGHT
         ↓
       DOWN

We normally write:

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

Then:

nr = r + dr[d];
nc = c + dc[d];
12. Invalid movement

We reject:

Outside grid
if (nr < 0 || nr >= m || nc < 0 || nc >= n)
    continue;
Wall
if (classroom[nr][nc] == 'X')
    continue;
13. Energy transition

Suppose:

current energy = 5

We move one cell:

5 → 4

So:

int ne = cur.e - 1;

If the new cell is R:

if (classroom[nr][nc] == 'R')
    ne = energy;

Important:

We subtract the movement cost first, then entering R resets the energy.

For example:

energy capacity = 10

current:
energy = 1

move to R:

1 - 1 = 0

enter R:

0 → 10

So the new state has:

energy = 10
14. Collecting litter

We assign every litter an ID.

For example:

L at (4,7) → ID 2

We store:

id[4][7] = 2;

Then:

if (classroom[nr][nc] == 'L') {
    int x = id[nr][nc];
    nmask |= (1 << x);
}
15. Your first solution

Your first solution used:

visited[r][c][mask][energy]

This is logically correct.

The dimensions are approximately:

20 × 20 × 1024 × 50

which is:

20,480,000

possible states.

And every state can have 4 transitions.

That's potentially around:

82 million

transitions.

Plus:

queue overhead
4D vector overhead
allocations
cache inefficiency
large memory access

So it can TLE.

And that is exactly what happened:

797 / 799

You were very close because the algorithm is correct, but the state space is too large.

16. The most important optimization

Now comes the really important concept:

Dominance

Suppose we reach exactly the same:

(row, col, mask)

twice.

First time:

energy = 15
moves = 20

Second time:

energy = 8
moves = 25

Which state is better?

Obviously:

energy 15

because it has:

more energy

and it also arrived:

earlier

The second state is completely useless.

17. Even stronger observation

Suppose:

State A:

(r,c,mask)
energy = 15
distance = 20

and:

State B:

(r,c,mask)
energy = 10
distance = 25

From A we can perform everything B can.

Why?

Because:

15 >= 10

And A is already reached earlier:

20 <= 25

Therefore B is dominated.

We don't need it.

18. What do we store instead?

Instead of:

visited[r][c][mask][energy]

we store:

best[r][c][mask]

Meaning:

Maximum energy with which we have reached (r,c,mask) so far.

Example:

best[5][7][13] = 15

means:

We've already reached (5,7) with litter mask 13 and had 15 energy.

If another state arrives:

energy = 10

we ignore it.

if (ne <= best[idx])
    continue;

If:

ne > best[idx]

then this is a better state:

best[idx] = ne;
q.push(...);
19. Why this pruning is safe

This is probably the most important reasoning to understand.

Suppose:

A = (r,c,mask,15)
B = (r,c,mask,10)

Both have exactly:

same position
same collected litter

Only energy differs.

A has more energy.

Every path B can take is also available to A.

For example, if B can make:

10 moves

before needing a reset, A can also make those 10 moves.

Therefore B cannot possibly produce a better answer.

So:

lower energy state = useless

when the position and mask are identical.

20. Why we don't compare different masks

Suppose:

A = (r,c,mask=0011,energy=20)
B = (r,c,mask=0111,energy=10)

Can we throw B away?

No.

B has collected more litter.

The states have different futures.

So:

(row, col, mask)

must remain part of the identity.

21. Why we don't simply store maximum energy globally

Suppose:

best[r][c] = 20

That's not enough.

Because one state may have:

mask = 0011

and another:

mask = 1111

The second might already be finished.

So the mask matters.

Correct:

best[r][c][mask]
22. Why the queue doesn't need distance in the state

In your original code you had:

struct State {
    int r;
    int c;
    int mask;
    int energy;
    int dist;
};

We can remove dist.

Because BFS can process level-by-level:

int moves = 0;

while (!q.empty()) {
    int sz = q.size();

    while (sz--) {
        ...
    }

    moves++;
}

All states currently in the queue have the same distance.

So:

queue
 ↓
all states at distance d
 ↓
process them
 ↓
queue new states at distance d+1

This saves memory and makes the BFS structure clearer.

23. Optimized state

Our state becomes:

struct State {
    int r;
    int c;
    int mask;
    int e;
};

And globally:

best[r][c][mask]

stores the best energy.

24. Complete optimized algorithm

The complete flow is:

                START
                  |
                  ↓
        Find S and all L
                  |
                  ↓
       Assign ID to every L
                  |
                  ↓
        Create initial mask=0
                  |
                  ↓
              BFS
                  |
          ┌───────┴────────┐
          ↓                ↓
     take a state       goal?
                           |
                       yes → answer
                           |
                          no
                           ↓
                   try 4 directions
                           |
                           ↓
                     valid cell?
                      /       \
                    no        yes
                    |          |
                  skip         ↓
                         spend 1 energy
                               |
                               ↓
                           R cell?
                          /      \
                        yes       no
                         |         |
                    reset E       keep
                         \         /
                          ↓       ↓
                       collect L?
                           |
                           ↓
                       update mask
                           |
                           ↓
                    better energy?
                      /          \
                    no           yes
                    |             |
                  skip          push
25. Full optimized code
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        vector<pair<int, int>> litter;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } else if (classroom[r][c] == 'L') {
                    litter.push_back({r, c});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int states = 1 << k;
        int fullMask = states - 1;

        vector<int> best(m * n * states, -1);

        auto index = [&](int r, int c, int mask) {
            return (r * n + c) * states + mask;
        };

        struct State {
            int r;
            int c;
            int mask;
            int e;
        };

        queue<State> q;

        best[index(sr, sc, 0)] = energy;
        q.push({sr, sc, 0, energy});

        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                State cur = q.front();
                q.pop();

                if (cur.mask == fullMask)
                    return moves;

                if (cur.e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = cur.e - 1;
                    int nmask = cur.mask;

                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    int idx = index(nr, nc, nmask);

                    if (ne <= best[idx])
                        continue;

                    best[idx] = ne;

                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};
26. Understand index()

We don't actually need a 3D vector.

We use:

vector<int> best(m * n * states, -1);

Then convert:

(r, c, mask)

into one number.

(r * n + c) * states + mask

Why?

First flatten (r,c):

r * n + c

Then each cell has states masks:

cellIndex * states + mask

So:

best[index(r,c,mask)]

is equivalent to:

best[r][c][mask]

but with one contiguous array.

This is often faster and more memory-efficient.

27. Why not use vector<vector<vector<int>>>?

You could:

vector<vector<vector<int>>> best(
    m,
    vector<vector<int>>(n, vector<int>(1 << k, -1))
);

This is logically simpler.

But the flattened version:

vector<int> best(m * n * states, -1);

has better:

cache locality
memory layout
allocation behavior
constant factors

For a problem close to the time limit, these details can matter.

28. Complexity — derive it properly

Let's define:

m = rows
n = columns
k = number of litter <= 10
E = energy <= 50
Original BFS

State:

(r,c,mask,e)

Number of possible states:

m × n × 2^k × E

Each has at most 4 transitions.

Therefore:

O(m × n × 2^k × E)

time, ignoring constant 4.

Space:

O(m × n × 2^k × E)

This is what caused your TLE.

29. Optimized complexity

Now we store:

best[r][c][mask]

There is no explicit energy dimension.

Number of stored states:

m × n × 2^k

Each successful state can cause up to 4 transitions.

So the main state-space bound is:

O(m × n × 2^k)

However, there is an important subtlety.

A (r,c,mask) can potentially be improved multiple times with increasing energy. Since energy is bounded by E, a conservative worst-case bound is:

O(m × n × 2^k × E)

for the number of successful improvements.

In practice, the dominance pruning is extremely effective, which is why this version passes where the explicit energy-state BFS can TLE.

The memory complexity is definitely:

O(m × n × 2^k)

because we store only the maximum energy for each (r,c,mask).

30. Maximum memory size

At maximum:

m = 20
n = 20
k = 10

Therefore:

20 × 20 × 1024
= 409,600

integers.

Since an int is 4 bytes:

409,600 × 4
≈ 1.64 MB

Very reasonable.

Compare that with:

20 × 20 × 1024 × 51
≈ 20.9 million

integers.

That's approximately:

83.6 MB

just for the raw integer data, before considering vector overhead and queue/state overhead.

That's why the compressed version is much better.

31. A very important general pattern

This problem teaches a reusable optimization:

State dominance

Suppose a state looks like:

(position, some_information, resource)

and you discover:

For the same position and information, having more resource is always better.

Then instead of:

visited[position][information][resource]

you can often store:

best[position][information] = maximum resource

This pattern appears with:

energy
fuel
health
money
remaining capacity
number of moves
time
battery

Whenever one resource value dominates another, ask:

"Can I eliminate the weaker state?"

32. Another important pattern: <=

Notice:

if (ne <= best[idx])
    continue;

Not:

if (ne < best[idx])

Why?

Suppose we already reached:

energy = 12

and now reach the same state with:

energy = 12

The new state is not better.

It's identical in terms of future possibilities.

So:

12 <= 12

means skip.

Only:

newEnergy > best

should be processed.

33. Why the answer can be returned immediately

Because BFS processes:

0 moves
1 move
2 moves
3 moves
...

Suppose we find:

cur.mask == fullMask

at distance:

17

Could there be an answer with:

16

that we haven't processed?

No.

BFS has already completely processed levels:

0...16

before reaching level 17.

Therefore:

return moves;

is safe.

34. Why cycles aren't a problem

The grid can contain cycles:

A → B → C
↑       ↓
└───────┘

Without visited-state control, BFS could loop forever.

Our best array handles this.

Suppose we go:

A → B → A

and return to A with less energy.

That state gets rejected.

If we return with exactly the same energy:

ne <= best

also rejected.

Therefore useless cycles disappear.

35. Why greedy doesn't work

You might think:

"Always go to the closest litter."

Not necessarily.

Suppose:

S ---- L1
|
R
|
L2

Maybe L1 is close, but after collecting it, we have no energy to reach L2.

Another route through R might be longer immediately but globally optimal.

Therefore this isn't a simple shortest path between two cells.

The important state includes:

position
+
collected litter
+
energy
36. Why we cannot just calculate distances between litter

This is another common temptation.

You might calculate:

S → L1
L1 → L2
L2 → L3

using shortest paths.

But energy constraints make paths dependent on:

reset areas
where you recharge
remaining energy
whether you can reach the next reset

So ordinary distance between litter isn't sufficient.

The BFS state approach naturally handles all of this.

37. How to recognize this problem in an interview

When you see:

Grid
+
collect all objects
+
at most 10 objects
+
movement cost = 1

immediately think:

BFS + Bitmask

Then ask:

Does another resource affect reachability?

Here:

energy

does.

So initially:

BFS state =
(row, col, mask, energy)

Then ask:

Can one resource state dominate another?

Yes.

Therefore compress:

best[row][col][mask] = maximum energy

That's the full thought process.

38. Mental template for similar problems

Memorize this pattern:

1. Identify important objects.
2. If objects <= ~15-20:
       use bitmask.
3. Identify everything that affects the future.
4. Put those things into the BFS state.
5. If all moves have equal cost:
       use BFS.
6. Check whether one state dominates another.
7. Store only non-dominated/best states.
8. Stop when the goal mask is complete.

For this problem:

Important objects = L
Number = <= 10
                ↓
             Bitmask

Movement cost = 1
                ↓
              BFS

Resource = Energy
                ↓
       Initially part of state

Same (r,c,mask), more energy is better
                ↓
         Dominance pruning

Final mask = (1<<k)-1
                ↓
              Goal
39. The most important concepts you should take away

If you're studying this problem to improve your algorithm skills, focus on these six concepts:

1. BFS shortest path

When every transition costs exactly 1:

BFS → minimum number of moves
2. State design

Don't just think:

Where am I?

Think:

"What information determines what I can do next?"

Here:

(row, col, mask, energy)
3. Bitmask

For k <= 10 objects:

2^k

is manageable.

4. State compression

Instead of storing:

energy = 0...50

explicitly:

best[r][c][mask]

stores the best possible energy.

5. Dominance

If:

same position
same mask
more energy

then the lower-energy state is useless.

6. Complexity analysis

Always calculate:

number of states × transitions per state

rather than guessing complexity.

For the original:

O(m × n × 2^k × E)

state dimensions.

For the optimized representation:

O(m × n × 2^k)

memory.

The one-line intuition

If you want to remember the entire solution:

Use BFS because every move costs 1, use a bitmask to remember which litter is collected, and for every (cell, mask) keep only the state with the maximum remaining energy because it dominates all states with less energy.













class Solution {
    int dir[5] = {-1,0,1,0,-1};
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();  // 1-20
        int n = classroom[0].size();  // 1-20
        int stx, sty;      
        int trash = 0; // pos -> index
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(classroom[i][j] == 'S'){
                    stx = i; sty = j;
                } else if(classroom[i][j] == 'L'){
                    classroom[i][j] = '0' + trash;
                    ++trash;
                }
            }
        }
        if(trash == 0)
            return 0;
        int bitMax = (1 << trash) - 1; // reach it and return
        // from hint, same status if already run bigger energy, smaller one can skip
        int maxEng[20][20][1024];    
        memset(maxEng, -1, sizeof(maxEng));

        // run BFS
        queue<tuple<int, int, int, int>> q;
        q.push({stx, sty, energy, 0});
        maxEng[stx][sty][0] = energy; // from hint
        int step = 0;

        while(!q.empty()){
            int sz = q.size();
            for(int run=0; run < sz; ++run){
                auto [x, y, en, mask] = q.front(); 
                q.pop();
                if(mask == bitMax) return step;
                if(en == 0) continue;
                for(int i=0; i<4; ++i){
                    int nextX = x + dir[i];
                    int nextY = y + dir[i+1];
                    if(nextX < 0 || nextX >= m || nextY < 0 || nextY >= n || classroom[nextX][nextY] == 'X') continue;
                    int nextEn = en - 1;
                    int nextMask = mask;
                    if(classroom[nextX][nextY] == 'R')
                        nextEn = energy;
                    else if(classroom[nextX][nextY] <= '9' && classroom[nextX][nextY] >= '0'){
                        nextMask |= 1 << (classroom[nextX][nextY] - '0');
                    }
                    if(maxEng[nextX][nextY][nextMask] < nextEn){
                        maxEng[nextX][nextY][nextMask] = nextEn;
                        q.push({nextX, nextY, nextEn, nextMask});    
                    }
                }
            }
            ++step;
        }
        return -1;
    }
};























constexpr int dir[5] {1, 0, -1, 0, 1};
int maxEng[20][20][1024];

class Solution {
public:
    int minMoves(vector<string>& classroom, const int energy) const {
        const int m = classroom.size(), n = classroom[0].size();

        int sr, sc, trash = 0;
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
            if (classroom[i][j] == 'S') {
                sr = i; sc = j;
            } else if (classroom[i][j] == 'L') {
                classroom[i][j] = '0' + trash;
                trash++;
            }
        }
        if (trash == 0) return 0;

        const int bitMax = (1 << trash) - 1;
        memset(maxEng, -1, sizeof(maxEng));

        queue<tuple<int, int, int, int>> q;
        q.emplace(sr, sc, energy, 0);
        maxEng[sr][sc][0] = energy;

        int step = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [x, y, en, mask] = q.front(); q.pop();
                
                if (mask == bitMax) return step;
                
                if (en == 0) continue;
                
                for (int i = 0; i < 4; ++i) {
                    const int nr = x + dir[i], nc = y + dir[i + 1];
                    
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n
                    || classroom[nr][nc] == 'X')
                        continue;
                    
                    int nextEn = en - 1;
                    int nextMask = mask;

                    if (classroom[nr][nc] == 'R')
                        nextEn = energy;
                    else if ('0' <= classroom[nr][nc] && classroom[nr][nc] <= '9')
                        nextMask |= 1 << (classroom[nr][nc] - '0');

                    if (maxEng[nr][nc][nextMask] < nextEn) {
                        maxEng[nr][nc][nextMask] = nextEn;
                        q.emplace(nr, nc, nextEn, nextMask);
                    }
                }
            }
            step++;
        }
        return -1;
    }
};
























// Time:  O(m * n * 2^l)
// Space: O(m * n * 2^l)

// bfs, bitmasks
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        const int m = size(classroom), n = size(classroom[0]);
        unordered_map<int, int> lookup;
        int r = -1, c = -1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    r = i;
                    c = j;
                } else if (classroom[i][j] == 'L') {
                    lookup[i * n + j] = size(lookup);
                }
            }
        }
        
        vector<vector<vector<int>>> lookup2(m, vector<vector<int>>(n, vector<int>(1 << size(lookup), -1)));
        lookup2[r][c][0] = energy;
        vector<tuple<int, int, int, int>> q = {{r, c, 0, energy}};
        for (int result = 0; !empty(q); ++result) {
            vector<tuple<int, int, int, int>> new_q;
            for (const auto& [i, j, mask, e] : q) {
                if (lookup2[i][j][mask] != e) {
                    continue;
                }
                if (mask == (1 << size(lookup)) - 1) {
                    return result;
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    int ne = e - 1;
                    if (!(0 <= ni && ni < m && 0 <= nj && nj < n && classroom[ni][nj] != 'X' && ne >= 0)) {
                        continue;
                    }
                    int new_mask = mask;
                    if (classroom[ni][nj] == 'R') {
                        ne = energy;
                    } else if (classroom[ni][nj] == 'L') {
                        new_mask |= 1 << lookup[ni * n + nj];
                    }
                    if (ne <= lookup2[ni][nj][new_mask]) {
                        continue;
                    }
                    lookup2[ni][nj][new_mask] = ne;
                    new_q.emplace_back(ni, nj, new_mask, ne);
                }
            }
            q = move(new_q);
        }
        return -1;
    }
};
























struct GridState{
    int x;
    int y;
    int taken;
    int energy;
};
class Solution {
public:
    int dir[5] = {-1,0,1,0,-1};
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();
        pair<int,int>startPos;
        int moves = 0;
        unordered_map<int,int>litterPos; //O(10)
        int litterCount = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(classroom[i][j] == 'S')
                    startPos = {i,j};
                if(classroom[i][j] == 'L')
                    litterPos[j+i*m] = litterCount++;
            }
        }
        
        vector<vector<int>>vis(n*m,vector<int>(1<<litterCount,INT_MIN));//O(n*m*2^10*energy)
        queue<GridState>q;
        q.push(GridState{startPos.first,startPos.second,0,energy});
        vis[startPos.second+startPos.first*m][0] = energy;
        while(!q.empty()){
            int p = q.size();
            while(p--){
                auto state = q.front();
                q.pop();
                if(state.energy < vis[state.y+state.x*m][state.taken])
                    continue;
                if(state.taken == (1<<litterCount)-1)
                    return moves;
                if(classroom[state.x][state.y] == 'R')
                    state.energy = energy;
                if(state.energy == 0)
                    continue;
                for(int i=0;i<4;i++){
                    int x1 = state.x + dir[i];
                    int y1 = state.y + dir[i+1];
                    if(x1<0 || y1<0 || x1>=n || y1>=m)
                        continue;
                    if(classroom[x1][y1] == 'X')
                        continue;
                    int loc = y1+x1*m;
                    int litterState = state.taken;
                    if(classroom[x1][y1] == 'L')
                        litterState|=(1<<litterPos[loc]);
                    if(vis[loc][litterState] < state.energy-1){
                        vis[loc][litterState] = state.energy-1;
                        q.push(GridState{x1,y1,litterState,state.energy-1});
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};

























class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        const int m = static_cast<int>(classroom.size());
        const int n = static_cast<int>(classroom[0].size());

        int startR = -1, startC = -1;
        vector<pair<int, int>> litPos;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                } else if (classroom[i][j] == 'L') {
                    litPos.emplace_back(i, j);
                }
            }
        }

        const int k = static_cast<int>(litPos.size());
        if (k == 0) return 0;
        const int allMask = (1 << k) - 1;

        auto bitOf = [&](int r, int c) -> int {
            for (int i = 0; i < k; ++i) {
                if (litPos[i].first == r && litPos[i].second == c) return i;
            }
            return -1;
        };

        // bestEng[r][c][mask] = max energy seen for state (pos, mask).
        vector<vector<vector<int>>> bestEng(
            m, vector<vector<int>>(n, vector<int>(1 << k, -1)));

        bestEng[startR][startC][0] = energy;
        queue<tuple<int, int, int, int, int>> q;  // r, c, mask, energy, dist
        q.emplace(startR, startC, 0, energy, 0);

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, mask, e, dist] = q.front();
            q.pop();

            if (mask == allMask) return dist;

            // Cannot move further with zero energy unless on a reset area.
            if (e == 0 && classroom[r][c] != 'R') continue;

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (classroom[nr][nc] == 'X') continue;

                int nmask = mask;
                int b = bitOf(nr, nc);
                if (b >= 0) nmask |= (1 << b);

                int ne;
                if (classroom[nr][nc] == 'R') {
                    ne = energy;
                } else {
                    if (e >= 1) {
                        ne = e - 1;
                    } else {
                        // e == 0 while on a reset area, but moving off it costs energy; from
                        // a reset area energy is already full, so e==0 here means unmovable
                        // non-R position, already skipped above.
                        continue;
                    }
                }

                if (ne > bestEng[nr][nc][nmask]) {
                    bestEng[nr][nc][nmask] = ne;
                    q.emplace(nr, nc, nmask, ne, dist + 1);
                }
            }
        }

        return -1;
    }
};






















class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        int sr = -1, sc = -1;
        int cnt = 0;

        vector<vector<int>> id(n, vector<int>(m, -1));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if(classroom[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }

        if(cnt == 0)
            return 0;

        int masks = 1 << cnt;
        int fullMask = masks - 1;

        struct State {
            int r, c, e, mask;
        };

        queue<State> q;
        q.push({sr, sc, energy, 0});

        int E = energy + 1;

        vector<char> visited(
            n * m * E * masks,
            0
        );

        auto getId = [&](int r, int c, int e, int mask) {
            return (((r * m + c) * E + e) * masks + mask);
        };

        visited[getId(sr, sc, energy, 0)] = 1;

        vector<pair<int,int>> dir = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        int moves = 0;

        while(!q.empty()) {
            int sz = q.size();

            while(sz--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if(mask == fullMask)
                    return moves;

                if(e == 0)
                    continue;

                for(auto [dr, dc] : dir) {
                    int nr = r + dr;
                    int nc = c + dc;

                    if(nr < 0 || nr >= n ||
                       nc < 0 || nc >= m)
                        continue;

                    if(classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if(classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    if(classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    int stateId = getId(nr, nc, ne, nmask);

                    if(visited[stateId])
                        continue;

                    visited[stateId] = 1;
                    q.push({nr, nc, ne, nmask});
                }
            }

            moves++;
        }

        return -1;
    }
};













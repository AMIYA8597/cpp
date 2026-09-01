2058. Find the Minimum and Maximum Number of Nodes Between Critical Points
Medium
Topics
premium lock icon
Companies
Hint
A critical point in a linked list is defined as either a local maxima or a local minima.

A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.

A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.

Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].

 

Example 1:


Input: head = [3,1]
Output: [-1,-1]
Explanation: There are no critical points in [3,1].
Example 2:


Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
- [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
- [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.
Example 3:


Input: head = [1,3,2,2,3,2,2,2,7]
Output: [3,3]
Explanation: There are two critical points:
- [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
- [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
Both the minimum and maximum distances are between the second and the fifth node.
Thus, minDistance and maxDistance is 5 - 2 = 3.
Note that the last node is not considered a local maxima because it does not have a next node.
 

Constraints:

The number of nodes in the list is in the range [2, 105].
1 <= Node.val <= 105


















  /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prev = -1;
        int minDist = INT_MAX;

        ListNode* left = head;
        ListNode* cur = head->next;
        int pos = 1;

        while (cur->next != nullptr) {
            ListNode* right = cur->next;

            if ((cur->val > left->val && cur->val > right->val) ||
                (cur->val < left->val && cur->val < right->val)) {

                if (first == -1) {
                    first = pos;
                }

                if (prev != -1) {
                    minDist = min(minDist, pos - prev);
                }

                prev = pos;
            }

            left = cur;
            cur = right;
            pos++;
        }

        if (first == -1 || first == prev) {
            return {-1, -1};
        }

        int maxDist = prev - first;

        return {minDist, maxDist};
    }
};




























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(){
           val=0;
           next=NULL;
           }
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* prev=head;
        ListNode* curr=head->next;
        int first_cp=-1;
      int prev_cp=-1;
        int mini=INT_MAX;
        int pos=1;
        while(curr->next!=NULL){
            bool isCritical= ((curr->next->val>curr->val && prev->val>curr->val)||(curr->next->val<curr->val && prev->val<curr->val));

            if(isCritical){
                if(first_cp==-1){
                    first_cp=pos;
                }
                else{
                    mini=min(mini,pos-prev_cp);
                }
                prev_cp=pos;
            }
            prev=curr;
            curr=curr->next;
            pos++;
        }

        if(first_cp==-1||prev_cp==first_cp) return {-1,-1};
        int maxi=prev_cp-first_cp;
        return {mini,maxi};
    }
};





































class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (head == NULL || head->next == nullptr)
            return {-1, -1};

        vector<int> ans;

        ListNode* temp = head;
        int data = temp->val;

        temp = temp->next;

        int pos = 1;

        while (temp->next != nullptr) {

           
            if (temp->val > data && temp->val > temp->next->val) {
                ans.push_back(pos);
            }

         
            else if (temp->val < data && temp->val < temp->next->val) {
                ans.push_back(pos);
            }

            data = temp->val;
            temp = temp->next;
            pos++;
        }

      
        if (ans.size() < 2)
            return {-1, -1};

        int mini = INT_MAX;

        for (int i = 1; i < ans.size(); i++) {
            mini = min(mini, ans[i] - ans[i - 1]);
        }

        int maxi = ans.back() - ans.front();

        return {mini, maxi};
    }
};


































/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int idx = 1;
        int fidx = -1;
        int sidx = -1;
        ListNode* a = head;
        ListNode* b = head->next;
        ListNode* c = head->next->next;
        if(c==NULL) return {-1,-1};
        while(c){
            if(b->val > a-> val && b->val > c->val || b->val < a->val && b->val < c->val){
                if(fidx==-1) fidx = idx;
                else sidx = idx;

            }
             a = a->next;
              b = b->next;
              c = c->next;
              idx++;
        }
            if(sidx==-1) return {-1,-1};
            int maxd = sidx - fidx;
            int mind = INT_MAX;
            fidx = -1;
            sidx = -1;
            idx = 1;
             a = head;
              b = head->next;
              c = head->next->next;
          

               while(c){
            if(b->val > a-> val && b->val > c->val || b->val < a->val && b->val < c->val){
                fidx = sidx;
                sidx = idx;
              if(fidx!=-1){
                 int  d = sidx -fidx;
               mind = min(mind,d);
              }
            }
             a = a->next;
             b = b->next;
             c = c->next; 
             idx++;
        }
        return {mind,maxd};
    }
    
};
























/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int maxdist=-1;
        int mindist=INT_MAX;
        ListNode* prev=head;
        ListNode* curr=prev->next;
        ListNode* nxt=curr->next;
        vector<int>index;
        vector<int>ans;
        int idx=2;
        while(nxt!=NULL){
         if(prev->val < curr->val && curr->val > nxt->val ) {
            index.push_back(idx);
            prev=prev->next;
            curr=curr->next;
            nxt=nxt->next;

         }
         else if(prev->val > curr->val && curr->val < nxt->val ) {
            index.push_back(idx);
            prev=prev->next;
            curr=curr->next;
            nxt=nxt->next;
         }
         else{
            prev=prev->next;
            curr=curr->next;
            nxt=nxt->next;
         }
         idx++;
        }

        if(index.size()<2){
            return {-1,-1};
        }


        for(int i=1;i<index.size();i++){
            mindist=min(mindist , index[i]-index[i-1]);
        }
        int n=index.size();
        maxdist=index[n-1]-index[0];
        
        ans.push_back(mindist);
        ans.push_back(maxdist);

       return ans;
    }
};























class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> pos;
        ListNode* prev = head;
        ListNode* cur = head->next;
        int idx = 1;
        while (cur && cur->next) {
            if ((cur->val > prev->val && cur->val > cur->next->val) ||
                (cur->val < prev->val && cur->val < cur->next->val))
                pos.push_back(idx);
            prev = cur;
            cur = cur->next;
            idx++;
        }
        if (pos.size() < 2) return {-1, -1};
        int minD = INT_MAX;
        for (int i = 1; i < (int)pos.size(); i++)
            minD = min(minD, pos[i] - pos[i-1]);
        return {minD, pos.back() - pos.front()};
    }
};



















/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> criticalPts;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        int pos = 0;
        while (curr->next != nullptr) {
            // 1.Traverse and find points
            if (prev != nullptr) {
                
                if ((curr->val > prev->val && curr->val > curr->next->val) ||
                    (curr->val < prev->val && curr->val < curr->next->val)) {
                    criticalPts.push_back(pos);
                }
            }
            prev = curr;
            curr = curr->next;
            pos++;
        }
        if (criticalPts.size() < 2) {
            return {-1, -1};
        }
        int minDist = INT_MAX;
        int maxDist = criticalPts.back() - criticalPts.front();
        for (int i = 1; i < criticalPts.size(); i++) {
            minDist = min(minDist, criticalPts[i] - criticalPts[i - 1]);
        }

        // return ans
        return {minDist, maxDist};
    }
};




















class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (!head || !head->next || !head->next->next)
            return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;

        while (curr->next) {
            int val = curr->val;
            if ((val > prev->val && val > curr->next->val) ||
                (val < prev->val && val < curr->next->val)) {

                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - last);
                }

                last = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (first == last)
            return ans;

        return {minDist, last - first};
    }
};
















/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> distance;
        ListNode* curr=head;
        ListNode* prev=nullptr;
        int i=1;
        while(curr!=nullptr){
            if(prev && curr->next){
                if((prev->val>curr->val && curr->val<curr->next->val) || (prev->val<curr->val && curr->val>curr->next->val) ){
                    distance.push_back(i);
                }
            }
            prev=curr;
            curr=curr->next;
            i++;
        }
        if(distance.size()<2){
            return {-1,-1};
        }        
        sort(distance.begin(),distance.end());
        int nd=distance.size();
        int mn=INT_MAX;
        for(int i=1;i<nd;i++){
            mn=min(mn,distance[i]-distance[i-1]);
        }
        return {mn,distance[nd-1]-distance[0]};
    }
};
Understand exactly what a critical point is

A node is a critical point if it is either:

a local maximum
a local minimum

Suppose we have:

previous   current   next
   ↓          ↓        ↓
   5          3        1

3 is a local maximum only when:

current > previous
AND
current > next

But here:

3 > 5  ❌

so it isn't a maximum.

For a local minimum:

current < previous
AND
current < next

Here:

3 < 5 ✅
3 < 1 ❌

so it isn't a minimum either.

2. Visual intuition

Consider:

5 → 3 → 1 → 2 → 5 → 1 → 2

Values go:

5
 \
  3
   \
    1    ← local minimum
     \
      2
       \
        5  ← local maximum
         \
          1 ← local minimum
           \
            2

Critical points are:

position 3
position 5
position 6

assuming positions are 1-indexed.

3. First important concept: local vs global

A local maximum/minimum only compares with its immediate neighbors.

For example:

10 → 5 → 7

5 is a local minimum even though there could be a value 1 somewhere later.

We don't care about the entire list.

We only care about:

previous
current
next

This is why we can solve the problem in one traversal.

4. Why first and last node cannot be critical

The first node:

head

has no previous node.

The last node:

tail

has no next node.

But the definition requires:

previous + current + next

Therefore:

first node → never critical
last node  → never critical

This is why the traversal checks only the interior nodes.

5. Linked-list traversal

Unlike an array, we cannot do:

nums[i - 1]
nums[i]
nums[i + 1]

because a linked list has pointers.

We maintain three pointers:

left       cur       right
 ↓          ↓          ↓
previous → current → next

In C++:

ListNode* left = head;
ListNode* cur = head->next;

and:

ListNode* right = cur->next;

Now we have everything needed to determine whether cur is critical.

6. Why three nodes are enough

At any point:

left -> cur -> right

we can test:

Maximum
cur->val > left->val &&
cur->val > right->val
Minimum
cur->val < left->val &&
cur->val < right->val

We don't need any earlier nodes.

We don't need any later nodes.

This is an example of a local property.

7. The actual goal

We aren't just asked to find critical points.

We need:

[minDistance, maxDistance]

between any two distinct critical points.

Suppose critical positions are:

2, 5, 8, 12

All pairwise distances are:

5 - 2 = 3
8 - 2 = 6
12 - 2 = 10

8 - 5 = 3
12 - 5 = 7

12 - 8 = 4

Minimum:

3

Maximum:

10

The question is:

Do we really need to generate all pairs?

No.

That's the biggest optimization.

8. Finding the maximum distance

For sorted positions:

p1 < p2 < p3 < ... < pk

The largest possible distance is always:

pk - p1

Why?

Because:

pk - p1

spans the entire range.

Any other pair lies inside that range.

Therefore:

maxDistance = lastCritical - firstCritical

We only need two positions:

first
last
9. Finding the minimum distance

This is a slightly more interesting observation.

Given:

p1 < p2 < p3 < p4

the minimum distance must occur between neighboring critical points:

p2 - p1
p3 - p2
p4 - p3

Why?

Suppose:

p1 < p2 < p3

Then:

p3 - p1

is always larger than:

p2 - p1

and:

p3 - p2

So a non-adjacent pair can never give the minimum.

Therefore we only need:

currentCritical - previousCritical
10. This eliminates O(k²)

A naive solution might:

vector<int> critical;

and then:

for (int i = 0; i < k; i++) {
    for (int j = i + 1; j < k; j++) {
        ...
    }
}

That costs:

O(k²)

where k is the number of critical points.

Since k <= n, worst case:

O(n²)

We don't need that.

Instead:

first critical
previous critical
current critical

allows everything to be calculated in one pass.

11. The three variables that solve everything

We maintain:

int first = -1;
int prev = -1;
int minDist = INT_MAX;

Conceptually:

first
  ↓
first critical point

prev
  ↓
most recently seen critical point

minDist
  ↓
smallest distance found so far

At the end:

last critical = prev

So:

maxDist = prev - first;
12. Why first = -1?

We need to distinguish:

no critical point found yet

from a real position.

Since positions are non-negative:

-1

is a convenient sentinel.

So:

int first = -1;

means:

We haven't encountered a critical point.

13. Processing the first critical point

Suppose we encounter a critical point at position 3.

Initially:

first = -1
prev = -1

We do:

if (first == -1)
    first = pos;

Now:

first = 3

Then:

prev = pos;

so:

prev = 3

There is no distance yet because we only have one critical point.

14. Processing the second critical point

Suppose next critical point is at position 5.

Before processing:

first = 3
prev = 3

Current position:

pos = 5

Distance:

5 - 3 = 2

So:

minDist = min(minDist, pos - prev);

Then:

prev = pos;

Now:

first = 3
prev = 5
minDist = 2
15. Processing the third critical point

Suppose the next is at:

6

Then:

6 - 5 = 1

Therefore:

minDist = min(2, 1)
        = 1

Then:

prev = 6

At the end:

first = 3
prev = 6

So:

maxDist = 6 - 3 = 3

Result:

[1, 3]
16. The complete movement of pointers

Suppose:

5 → 3 → 1 → 2 → 5 → 1 → 2

We'll use:

left
cur
right
Initial
left
 ↓
5 → 3 → 1 → 2 → 5 → 1 → 2
    ↑
   cur

Then:

right = cur->next

so:

5 → 3 → 1
    ↑   ↑
   cur right

Check 3.

Not critical.

Move forward:

left = cur;
cur = right;

Now:

5 → 3 → 1 → 2
        ↑   ↑
       cur right

Check 1.

It's a local minimum.

Then advance again.

This continues until cur->next == nullptr.

17. Why the loop condition is important

We use:

while (cur->next != nullptr)

Why?

Because we need:

cur->next

to exist.

The moment:

cur->next == nullptr

cur is the last node.

And last nodes cannot be critical.

So we stop.

18. Complete implementation
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prev = -1;
        int minDist = INT_MAX;

        ListNode* left = head;
        ListNode* cur = head->next;
        int pos = 1;

        while (cur->next != nullptr) {
            ListNode* right = cur->next;

            bool critical =
                (cur->val > left->val && cur->val > right->val) ||
                (cur->val < left->val && cur->val < right->val);

            if (critical) {
                if (first == -1) {
                    first = pos;
                }

                if (prev != -1) {
                    minDist = min(minDist, pos - prev);
                }

                prev = pos;
            }

            left = cur;
            cur = right;
            pos++;
        }

        if (first == -1 || first == prev) {
            return {-1, -1};
        }

        return {minDist, prev - first};
    }
};
19. Let's dry-run the entire code

Take:

5 → 3 → 1 → 2 → 5 → 1 → 2

Positions:

0  1  2  3  4  5  6

Critical points:

2, 4, 5

Initial:

first = -1
prev = -1
minDist = INF
Position 1
left = 5
cur = 3
right = 1

Check:

3 > 5 ❌
3 < 5 ✅
3 < 1 ❌

Not critical.

Move:

left = 3
cur = 1
Position 2
left = 3
cur = 1
right = 2

Check:

1 < 3 ✅
1 < 2 ✅

Critical.

Set:

first = 2
prev = 2

No minimum distance yet.

Position 3
left = 1
cur = 2
right = 5

Not critical.

Advance.

Position 4
left = 2
cur = 5
right = 1

Critical.

Distance:

4 - 2 = 2

So:

minDist = 2
prev = 4
Position 5
left = 5
cur = 1
right = 2

Critical.

Distance:

5 - 4 = 1

So:

minDist = 1
prev = 5

End.

Maximum:

prev - first
= 5 - 2
= 3

Answer:

[1, 3]
20. Why we don't store all critical points

You could write:

vector<int> cp;

Then append every critical position:

cp.push_back(pos);

Afterwards:

for (...)

calculate the distances.

That would work.

But we realize:

minimum → only neighboring critical points
maximum → first and last critical points

Therefore storing everything is unnecessary.

This is a common algorithmic optimization:

Don't store information that you will never need later.

21. One-pass algorithm

This is called a single-pass / one-pass algorithm.

We read each node once and immediately use it.

The structure is:

read current
     ↓
determine whether critical
     ↓
update answer
     ↓
move forward

No second pass.

No nested loop.

No extra array.

22. Streaming perspective

Another way to think about it:

Imagine the linked list is arriving one node at a time.

You don't know future nodes except the next one.

Still, we can maintain enough information to eventually calculate the answer.

We only remember:

first critical
previous critical
minimum distance

This is a type of streaming algorithm.

You process data sequentially while keeping a tiny summary of everything relevant.

23. Why minDist = INT_MAX?

Initially, we don't have any distance.

So we use:

int minDist = INT_MAX;

Then:

minDist = min(minDist, distance);

For the first valid pair, the real distance will always be smaller than INT_MAX.

You could also initialize it with some large constant, but INT_MAX is standard.

24. Handling no critical points

Example:

3 → 1

There is no node having both neighbors.

So:

first = -1
prev = -1

We return:

[-1, -1]
25. Handling exactly one critical point

Example:

1 → 3 → 2

Critical points:

position 1

Then:

first = 1
prev = 1

There is no pair of distinct critical points.

So:

first == prev

and return:

[-1, -1]
26. Why first == prev means exactly one

Every time we discover a critical point:

prev = pos;

first never changes.

So:

Zero critical points
first = -1
prev = -1
One critical point at position 7
first = 7
prev = 7
Two or more
first != prev

Therefore:

if (first == -1 || first == prev)

handles both cases.

27. Alternative condition: count

You could instead maintain:

int count = 0;

and check:

if (count < 2)
    return {-1, -1};

That's also valid.

But first and prev already give us enough information, so an extra variable isn't necessary.

28. Can we use values instead of positions?

No.

Distance is based on node positions, not value difference.

For example:

5 → 3 → 1

If critical positions were:

1 and 10

distance is:

10 - 1 = 9

not:

|value1 - value2|

So position tracking is essential.

29. Important distinction: node distance

The problem considers:

index difference

For positions:

2 and 5

distance is:

5 - 2 = 3

There are three links/edges between them.

This matches the problem's definition.

30. Could we solve with recursion?

Yes, technically.

But there is no advantage.

The list can contain up to:

10^5

nodes.

Recursive traversal could cause stack-depth problems.

Iterative traversal is preferable:

while (...)

This is another good competitive-programming habit:

For large linked lists, prefer iterative traversal unless recursion provides a clear benefit.

31. Time complexity

Let:

n = number of nodes

We visit every node at most once.

For each node we do only constant work:

compare values
update variables
move pointers

Therefore:

Time = O(n)
32. Space complexity

We use only:

first
prev
minDist
left
cur
right
pos

A constant number of variables.

Therefore:

Extra Space = O(1)

This is better than storing all critical points:

O(n)
33. Overall comparison
Naive approach
Traverse list
    ↓
store all critical positions
    ↓
compare every pair

Complexity:

Time:  O(n²)
Space: O(n)
Better approach
Traverse once
    ↓
maintain first + previous + min distance

Complexity:

Time:  O(n)
Space: O(1)

This is the optimal style for the problem.

34. The deeper algorithmic lesson

The most important lesson isn't just "find critical points."

It's this:

When a problem asks about all pairs, first ask whether mathematical properties allow you to avoid examining every pair.

Here:

Maximum
max distance = last - first
Minimum
min distance = minimum gap between adjacent critical points

That eliminates the quadratic pair comparison.

This kind of observation appears everywhere.

35. Similar patterns to recognize

When asked:

Maximum distance among sorted positions

Usually:

last - first
Minimum distance among sorted positions

Usually check:

adjacent differences
Maximum subarray

Think:

Kadane's algorithm

instead of checking every subarray.

Two Sum

Don't check all pairs:

O(n²)

Use a hash map:

O(n)
Sliding window

Don't recompute the whole window.

Maintain only what's changing.

The common theme is:

Maintain a small amount of sufficient information instead of recomputing everything.

36. The invariant of our algorithm

A very useful concept is the loop invariant.

After processing positions up to pos, we maintain:

first
=
position of the first critical point seen so far

and:

prev
=
position of the most recent critical point seen so far

and:

minDist
=
minimum distance between any two consecutive critical points seen so far

Because this remains true after every iteration, at the end we have the required answer.

Understanding invariants makes many one-pass algorithms much easier to derive.

37. A compact mental model

When you see this problem, think:

Need critical points
        ↓
Need previous/current/next node
        ↓
Traverse linked list with 3 pointers
        ↓
When critical:
        ↓
first? save it
        ↓
compare with previous
        ↓
update minimum
        ↓
previous = current
        ↓
At end:
maximum = last - first

In variable form:

first  = first critical point
prev   = last critical point seen
minD   = smallest adjacent critical-point gap

Then:

answer = [minD, prev - first]
38. What you should memorize from this problem

Don't memorize the code line-by-line.

Memorize these four ideas:

1. A critical point needs previous + current + next.

2. Minimum distance is between consecutive critical points.

3. Maximum distance is first critical to last critical.

4. Therefore one traversal + O(1) variables is enough.

That gives:

O(n) time
O(1) extra space
Final template
ListNode* left = head;
ListNode* cur = head->next;
int pos = 1;

while (cur->next != nullptr) {
    ListNode* right = cur->next;

    if (isCritical(left, cur, right)) {
        update(first, prev, minDist, pos);
    }

    left = cur;
    cur = right;
    pos++;
}











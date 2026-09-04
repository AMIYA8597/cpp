3875. Construct Uniform Parity Array I
Easy
Topics
premium lock icon
Companies
Hint
You are given an array nums1 of n distinct integers.

You want to construct another array nums2 of length n such that the elements in nums2 are either all odd or all even.

For each index i, you must choose exactly one of the following (in any order):

nums2[i] = nums1[i]
nums2[i] = nums1[i] - nums1[j], for an index j != i
Return true if it is possible to construct such an array, otherwise, return false.

 

Example 1:

Input: nums1 = [2,3]

Output: true

Explanation:

Choose nums2[0] = nums1[0] - nums1[1] = 2 - 3 = -1.
Choose nums2[1] = nums1[1] = 3.
nums2 = [-1, 3], and both elements are odd. Thus, the answer is true​​​​​​​.
Example 2:

Input: nums1 = [4,6]

Output: true

Explanation:​​​​​​​

Choose nums2[0] = nums1[0] = 4.
Choose nums2[1] = nums1[1] = 6.
nums2 = [4, 6], and all elements are even. Thus, the answer is true.
 

Constraints:

1 <= n == nums1.length <= 100
1 <= nums1[i] <= 100
nums1 consists of distinct integers.



























class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};




















Absolutely. Let's break down the **entire program for LeetCode 3875 — Construct Uniform Parity Array I** from the problem logic to every line of C++.

## 1. Complete program

```cpp
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};
```

It looks surprisingly small, so let's understand **why this is enough**.

---

# 2. What is the problem asking?

We have:

```text
nums1
```

For every element `nums1[i]`, we must choose exactly one:

```text
nums1[i]
```

or

```text
nums1[i] - nums1[j]
```

where:

```text
j != i
```

After making all choices, every element in `nums2` must be:

* all **odd**, or
* all **even**.

We only need to return whether this is possible.

---

# 3. First understand parity

Parity simply means whether a number is:

```text
Even
```

or

```text
Odd
```

Examples:

```text
2 → even
4 → even
6 → even

1 → odd
3 → odd
5 → odd
```

The most important mathematical rule is:

```text
even - even = even
odd  - odd  = even

even - odd  = odd
odd  - even = odd
```

This is the entire foundation of the solution.

---

# 4. What if all numbers are already even?

Example:

```text
nums1 = [2, 4, 8]
```

We don't have to perform subtraction.

The problem allows:

```text
nums2[i] = nums1[i]
```

So simply choose:

```text
[2, 4, 8]
```

All elements are even.

Therefore:

```text
true
```

---

# 5. What if all numbers are already odd?

Example:

```text
nums1 = [1, 5, 7]
```

Again, choose every number unchanged:

```text
[1, 5, 7]
```

All elements are odd.

Therefore:

```text
true
```

---

# 6. The interesting case: mixed parity

Suppose:

```text
nums1 = [2, 3]
```

We have:

```text
2 → even
3 → odd
```

They aren't uniform yet.

Can we change `2`?

Yes.

We can choose:

```text
nums2[0] = nums1[0] - nums1[1]
```

Therefore:

```text
2 - 3 = -1
```

And:

```text
-1 → odd
3  → odd
```

So:

```text
nums2 = [-1, 3]
```

Everything is odd.

Therefore:

```text
true
```

---

# 7. Why does the negative number matter?

This is where the earlier incorrect solution went wrong.

We had:

```text
2 - 3 = -1
```

Some reasoning incorrectly assumed that `3` had to be smaller than `2`.

But the problem does **not** say:

```text
nums1[i] > nums1[j]
```

It only says:

```text
j != i
```

So this is perfectly valid:

```text
2 - 3 = -1
```

The result can be negative.

And `-1` is odd.

---

# 8. What if we have many numbers?

Consider:

```text
nums1 = [2, 4, 7, 10]
```

We have:

```text
2  → even
4  → even
7  → odd
10 → even
```

We have at least one odd number: `7`.

We can use `7` to convert every even number into an odd number.

For `2`:

```text
2 - 7 = -5
```

`-5` is odd.

For `4`:

```text
4 - 7 = -3
```

`-3` is odd.

For `7`:

```text
7
```

Already odd.

For `10`:

```text
10 - 7 = 3
```

Odd.

So we can construct:

```text
[-5, -3, 7, 3]
```

Every element is odd.

Therefore:

```text
true
```

---

# 9. What about `j != i`?

This condition is important.

Suppose:

```text
nums1 = [2, 4, 7]
```

For `2`, we can choose `7`.

The indices are:

```text
index:    0  1  2
value:    2  4  7
```

For index `0`:

```text
j = 2
```

So:

```text
j != i
```

is satisfied.

For `4`:

```text
i = 1
j = 2
```

Again:

```text
j != i
```

is satisfied.

Because the array contains **distinct integers**, if there is an odd number and we're currently looking at an even number, that odd number must be at another index.

---

# 10. Why can we always make everything odd?

There are two types of numbers.

### Already odd

Do nothing:

```text
odd → odd
```

### Even

Choose an odd number `x` from another index:

```text
even - odd
```

By parity:

```text
even - odd = odd
```

Therefore:

```text
even → odd
```

So once an odd number exists, we can make **every element odd**.

---

# 11. Therefore, what are the possible situations?

There are only two.

### Situation A

There are no odd numbers.

Then:

```text
all numbers are even
```

So just keep them unchanged.

Result:

```text
true
```

### Situation B

There is at least one odd number.

Then:

```text
odd → keep it
even → subtract an odd number
```

Everything becomes odd.

Result:

```text
true
```

Therefore:

```text
EVERY POSSIBLE INPUT → TRUE
```

---

# 12. Now understand the C++ program

Our entire solution is:

```cpp
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};
```

Let's break down every part.

---

## 13. `class Solution`

```cpp
class Solution
```

LeetCode expects your solution inside a class called:

```text
Solution
```

This is the standard LeetCode format.

---

## 14. `{`

```cpp
class Solution {
```

This opens the body of the class.

Everything belonging to the class goes inside these braces.

---

# 15. `public:`

```cpp
public:
```

This means the function below can be accessed by LeetCode.

Without going deeply into C++ access modifiers:

```text
public
```

means accessible from outside the class.

---

# 16. The function

```cpp
bool uniformArray(vector<int>& nums1)
```

Let's break this into pieces.

### `bool`

The function returns either:

```text
true
```

or:

```text
false
```

So its return type is:

```cpp
bool
```

---

### `uniformArray`

This is the function name expected by the problem.

---

### `vector<int>& nums1`

This means the function receives an integer array.

For example:

```text
[2, 3]
```

In C++, LeetCode represents this as:

```cpp
vector<int>
```

The `&` means we pass the vector by reference rather than copying the whole array.

---

# 17. Function body

```cpp
{
    return true;
}
```

This means the function always returns:

```text
true
```

Why?

Because, mathematically, we proved that every valid input can construct a uniform-parity array.

---

# 18. Why don't we need to inspect `nums1`?

Normally, you might expect something like:

```cpp
for (int x : nums1) {
    ...
}
```

But here it isn't necessary.

The constraints guarantee:

```text
n >= 1
```

So there is always at least one element.

Every element is either:

```text
odd
```

or:

```text
even
```

If all are the same parity, we're already done.

If they are mixed, the existence of an odd number allows us to convert all even numbers into odd numbers.

Thus there is **no input for which the answer is false**.

So we don't need to calculate anything.

---

# 19. Let's prove it mathematically

Suppose there is at least one odd element `O`.

For every element `x`:

### If `x` is odd

Choose:

```text
nums2[i] = x
```

Therefore:

```text
nums2[i] is odd
```

### If `x` is even

Choose the odd element `O`:

```text
nums2[i] = x - O
```

Since:

```text
even - odd = odd
```

we get:

```text
nums2[i] is odd
```

Therefore every element of `nums2` is odd.

Hence:

```text
answer = true
```

If no odd element exists, all elements are even and we simply keep them unchanged.

Again:

```text
answer = true
```

Thus:

```text
∀ valid nums1 → answer = true
```

---

# 20. Test case 1

```text
nums1 = [2,3]
```

Mixed parity.

Choose:

```text
2 - 3 = -1
3 = 3
```

Result:

```text
[-1,3]
```

Both odd.

```text
true
```

Our program:

```cpp
return true;
```

Correct.

---

# 21. Test case 2

```text
nums1 = [4,6]
```

Both even.

Choose:

```text
4
6
```

Result:

```text
[4,6]
```

Both even.

```text
true
```

Our program:

```cpp
return true;
```

Correct.

---

# 22. Single element

Suppose:

```text
nums1 = [5]
```

We cannot use subtraction because there is no `j != i`.

But that's fine.

Simply choose:

```text
nums2 = [5]
```

All elements are odd.

So:

```text
true
```

For:

```text
nums1 = [8]
```

choose:

```text
nums2 = [8]
```

All elements are even.

Again:

```text
true
```

---

# 23. Why the solution is `O(1)` time

Our program does only:

```cpp
return true;
```

There is no loop.

There is no sorting.

There is no searching.

There is no array modification.

Therefore the running time is:

```text
O(1)
```

---

# 24. Space complexity

We don't create any additional data structure.

Therefore:

```text
O(1)
```

extra space.

---

# 25. The important lesson

This is a good example of an important competitive-programming technique:

> **Don't start coding before proving whether every input is possible.**

At first, this problem looks like it requires:

* checking every pair `i, j`
* trying different subtractions
* tracking odd/even values
* maybe using greedy

But parity completely eliminates all of that.

The key chain of thought is:

```text
Need same parity
        ↓
Subtraction changes parity when operands have different parity
        ↓
If an odd number exists:
    odd  → keep it
    even → subtract odd
        ↓
Everything becomes odd
        ↓
If no odd exists:
    everything is already even
        ↓
Answer is always TRUE
```

So the final LeetCode submission is simply:

```cpp
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};
```

This is one of those problems where **the hardest part isn't implementation — it's recognizing that the implementation becomes unnecessary after the proof.**

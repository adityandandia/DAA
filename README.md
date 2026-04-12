## Question 9 (D2): The Selection Problem Using Quickselect

---

### Task 1 — Quickselect Algorithm Design (Decrease-by-Variable-Size Strategy)

**Core Idea:**

Quickselect uses the **partition** step from Quicksort to reduce the problem size at each step without fully sorting the array. It is a classic example of the **decrease-by-variable-size** strategy because the amount by which the problem shrinks depends on where the pivot lands after partitioning.

**Algorithm Design:**

1. **Partition:** Choose a pivot (e.g., the last element). Rearrange the array so that:
   - All elements < pivot are to its left.
   - All elements > pivot are to its right.
   - The pivot is now at its correct sorted position `p`.

2. **Decrease:**
   - If `p == k−1`: the pivot **is** the k-th smallest element. Return it.
   - If `p > k−1`: the k-th smallest lies in the **left** subarray. Recurse on `arr[lo..p−1]`.
   - If `p < k−1`: the k-th smallest lies in the **right** subarray. Recurse on `arr[p+1..hi]`.

3. **Repeat** until the pivot index equals `k−1`.

This is "decrease-by-variable-size" because the problem size after each step is `p`, `p − lo`, or `hi − p`, depending on the pivot placement — not a fixed fraction.

---

### Task 2 — Algorithm Implementation

See `q9_quickselect.c`.

---

### Task 3 — Problem Size Decrease at Each Step

Let the current subarray have size `m`. After one partition step:

- Pivot lands at position `p` (0-indexed within the subarray).
- **Left subarray size:** `p` elements.
- **Right subarray size:** `m − p − 1` elements.
- We recurse on one of these two, reducing the active search space.

**Example (k = 3rd smallest, array of size 8):**

```
Step 1: Array size = 8, pivot lands at index 5 → recurse left, size = 5
Step 2: Array size = 5, pivot lands at index 1 → recurse right, size = 3
Step 3: Array size = 3, pivot lands at index 2 → found (k−1 = 2) ✓
```

In the **best case**, the pivot always lands exactly at `k−1`, and the answer is found in 1 step: O(n).

In the **average case**, pivot placement is random and roughly halves the subarray each time.

---

### Task 4 — Recurrence Relations

**Average Case:**

Assuming a random pivot uniformly splits the array, on average the recursion descends into a subarray of size `n/2`:

```
T(n) = T(n/2) + O(n)
```

Solving by the Master Theorem (Case 3 / geometric series):

```
T(n) = O(n)   [average case]
```

More precisely, summing the geometric series: `n + n/2 + n/4 + ... ≈ 2n = O(n)`.

**Worst Case:**

The worst case occurs when the pivot is always the smallest or largest element (already sorted array with naive pivot = last element), leading to a size reduction of only 1 each time:

```
T(n) = T(n−1) + O(n)
```

Solving by telescoping:

```
T(n) = n + (n−1) + (n−2) + ... + 1 = n(n+1)/2 = O(n²)   [worst case]
```

---

### Task 5 — Analysis & Comparison with Sort-then-Index

**Quickselect Summary:**

| Case         | Recurrence         | Time Complexity |
|--------------|--------------------|-----------------|
| Average case | T(n) = T(n/2) + n  | O(n)            |
| Worst case   | T(n) = T(n−1) + n  | O(n²)           |

**Sort-then-Index Approach:**

Sort the array using an O(n log n) algorithm (e.g., Merge Sort, Heap Sort), then directly access `arr[k−1]`.

| Metric             | Sort-then-Index     | Quickselect (avg) | Quickselect (worst) |
|--------------------|---------------------|-------------------|----------------------|
| Time complexity    | O(n log n)          | **O(n)**          | O(n²)               |
| Space complexity   | O(n) or O(log n)    | O(log n) stack    | O(n) stack (worst)  |
| Repeated queries?  | O(1) per query after sort | O(n) per query | O(n²) per query |
| Stability          | Stable (Merge Sort) | Not stable        | Not stable           |

**Verdict:**

- For a **single k-th order statistic query** on an unsorted array, Quickselect's O(n) average case is clearly superior to O(n log n) sort.
- For **multiple queries** on the same array, sort-then-index is better (one O(n log n) sort followed by O(1) lookups).
- **Median-of-medians** is a deterministic O(n) worst-case algorithm, but with high constants — rarely used in practice.
- For the **real-time bidding engine** scenario (single query per auction in microseconds), Quickselect with a random pivot is the right choice.

---
---

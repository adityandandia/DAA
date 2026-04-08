## Question 3 (D2): Exhaustive Search for a Minimum-Weight Hamiltonian Path

---

### Task 1 — Exhaustive Search Strategy & Search Space Enumeration

**Strategy:**

The exhaustive search (brute-force) strategy for the Minimum-Weight Hamiltonian Path problem works as follows:

1. Fix the starting depot `s` as the first node.
2. Generate **all permutations** of the remaining `(n - 1)` vertices.
3. For each permutation, prepend `s` to form a candidate path of length `n`.
4. Compute the total weight of the candidate path by summing edge weights along it.
5. Track the permutation that yields the minimum total weight.
6. Return the minimum-weight path and its cost.

**Search Space Enumeration:**

Since the depot `s` is fixed, we permute the remaining `(n − 1)` vertices. The total number of candidate paths is:

```
(n - 1)!
```

For example:
| n | Candidates (n−1)! |
|---|-------------------|
| 4 | 6                 |
| 5 | 24                |
| 10 | 362,880          |
| 15 | 87,178,291,200   |
| 20 | ~1.216 × 10¹⁷    |

Each candidate is a sequence `[s, v₁, v₂, ..., v_{n-1}]` where `{v₁, ..., v_{n-1}}` is a permutation of `V \ {s}`.

---

### Task 2 — Algorithm Implementation

See `q3_hamiltonian_path.c`.

---

### Task 3 — Number of Candidate Solutions for n Vertices

With the start vertex `s` fixed, the number of distinct candidate Hamiltonian paths is:

```
T(n) = (n − 1)!
```

This is because:
- Position 1 is fixed (depot `s`): **1** choice.
- Position 2: **(n − 1)** choices.
- Position 3: **(n − 2)** choices.
- ...
- Position n: **1** choice.

Total = `(n−1) × (n−2) × ... × 1 = (n−1)!`

---

### Task 4 — Time Complexity Analysis

Let `n` = number of vertices.

| Phase | Cost |
|-------|------|
| Generating each permutation | O(n) per permutation |
| Computing path weight | O(n) per permutation |
| Number of permutations | (n−1)! |

**Total time complexity:**

```
T(n) = O(n · (n−1)!) = O(n!)
```

**Space complexity:** O(n) for storing one permutation at a time (if done recursively with backtracking).

---

### Task 5 — Infeasibility for Large n & Problem Class

**Why it becomes infeasible:**

The `O(n!)` growth is superexponential — it dwarfs even exponential algorithms. A few data points assuming 10⁹ operations/second:

| n  | (n−1)! candidates | Approx. time      |
|----|-------------------|-------------------|
| 10 | 362,880           | < 1 ms            |
| 15 | ~8.7 × 10¹⁰      | ~87 seconds       |
| 20 | ~1.2 × 10¹⁷      | ~3,800 years      |
| 25 | ~6.2 × 10²³      | longer than the age of the universe |

For `n ≥ 20`, exhaustive search is completely impractical on any classical hardware.

**Problem Class:**

The Minimum-Weight Hamiltonian Path problem belongs to the class **NP-Hard**. It is a generalization of the **Travelling Salesman Problem (TSP)**, which is one of the most well-known NP-Hard problems.

- No polynomial-time algorithm is known for it.
- It cannot be solved exactly in polynomial time unless **P = NP**.
- For large `n`, practical approaches rely on **heuristics** (greedy nearest-neighbour), **metaheuristics** (simulated annealing, genetic algorithms), or **approximation algorithms** (Christofides' algorithm for metric TSP gives a 3/2-approximation).

---
---
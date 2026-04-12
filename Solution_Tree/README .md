## Question 20: Backtracking — Systematic Search with Constraint Checking

---

### Task 1 — How a Solution Tree is Constructed

A **solution tree** (also called a **state space tree**) is a conceptual tree structure that represents all possible states of the solution-building process:

- **Root:** Represents the empty (initial) partial solution.
- **Each node at depth d:** Represents a partial solution with `d` choices made.
- **Each edge:** Represents a single choice (assigning a value to the next variable/slot).
- **Leaf nodes:** Represent either a complete candidate solution or a dead end (constraint violation).
- **Branches** from a node represent all possible extensions of the current partial solution.

The tree has depth `n` (number of decisions) and branching factor up to `k` (number of choices per decision). Its total nodes are bounded by `O(k^n)` in the worst case, but backtracking prunes large portions of it.

---

### Task 2 — How Partial Solutions Are Expanded

Backtracking builds solutions **incrementally** using a depth-first search on the solution tree:

1. **Start** at the root (empty solution).
2. **Choose** the next variable/position to assign.
3. **Try** each possible value for that variable in order.
4. **Check constraints** immediately after each assignment (pruning condition):
   - If the current partial solution **violates a constraint**, **backtrack** — undo the last assignment and try the next value.
   - If no values remain, backtrack further up the tree.
5. **Recurse** deeper if the partial solution is still valid.
6. **Record** the solution when a complete, constraint-satisfying assignment is found.

The key advantage over exhaustive search is **early termination**: subtrees that cannot possibly lead to a valid solution are pruned without being explored.

---

### Task 3 — Illustrated Search Tree (N-Queens, n = 4)

Place 4 queens on a 4*4 board so no two attack each other. Columns are placed row by row.

```
                        [ ]  ← Root (no queens placed)
          ┌──────────┬──────────┬──────────┐
         Q@(1,1)  Q@(1,2)  Q@(1,3)  Q@(1,4)
            │       │         │        │
          [Row 2] [Row 2]   [Row 2]  [Row 2]
            │       │         │        │
          ✗(1,1)  ✗(2,1)  Q@(2,1)✗ Q@(2,1)✗
                    │         │
                  Q@(2,3)✗  Q@(2,2)✗
                    │
                  Q@(2,4)
                    │
                  [Row 3]
                    │
                  Q@(3,2)
                    │
                  [Row 4]
                    │
                  Q@(4,4)✗ (attacks)
```

The two valid solutions for 4-Queens are:

```
Solution 1: Q at columns [2, 4, 1, 3]
Solution 2: Q at columns [3, 1, 4, 2]
```

At every node, before placing a queen, we check:
- No same column as a previous queen.
- No diagonal conflict with any previous queen.

If a conflict is found, that branch is pruned (marked ✗) and the search backtracks.

---

### Task 4 — Complexity Analysis

**Worst-case (no pruning):**

If backtracking degenerates to exhaustive search, complexity is O(k^n), where k is the branching factor and n is the solution depth.

**For N-Queens:**

- Naive: O(n^n) — place a queen in any of n columns for each of n rows.
- With column constraint only: O(n!) — reduces to permutations.
- With full diagonal pruning: empirically much smaller; the number of nodes explored grows roughly as O(n!/ some pruning factor).

**General Backtracking:**

| Metric | Complexity |
|--------|------------|
| Worst case (no pruning) | O(k^n) |
| Best case (heavy pruning) | O(n) — linear path to solution |
| Space (recursion stack) | O(n) — depth of recursion |

The effectiveness of backtracking is problem-dependent. Constraint propagation techniques (like **forward checking** and **arc consistency**) can dramatically reduce the search space beyond simple backtracking.

---

### Task 5 — Practical Applications

Backtracking is widely used in problems where solutions must satisfy a set of hard constraints and exhaustive search is too slow:

| Application | Description |
|-------------|-------------|
| **N-Queens / Chess puzzles** | Place pieces without conflict on a board |
| **Sudoku solver** | Fill a 9×9 grid satisfying row/column/box constraints |
| **Graph Coloring** | Assign colors to vertices so no two adjacent vertices share a color (used in register allocation in compilers) |
| **Constraint Satisfaction Problems (CSP)** | General framework used in AI planning, scheduling, timetabling |
| **Subset Sum / Knapsack** | Find subsets of numbers that sum to a target |
| **Hamiltonian Path / TSP** | Find routes visiting all nodes (as in Question 3 above) |
| **Cryptarithmetic** | Assign digits to letters to satisfy arithmetic equations (e.g., SEND + MORE = MONEY) |
| **SAT Solvers (DPLL algorithm)** | Boolean satisfiability — backbone of hardware verification and automated reasoning |
| **Parsing in compilers** | Backtracking parsers for ambiguous grammars |
| **Crossword puzzle generation** | Fill grid words satisfying crossing-letter constraints |

Backtracking is the foundation of many modern constraint programming libraries (e.g., OR-Tools, Choco Solver) and is embedded in logic programming languages like Prolog.

---

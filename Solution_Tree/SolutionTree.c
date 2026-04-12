/* ============================================================
 *  QUESTION 20
 *  Backtracking — N-Queens Problem
 *
 *  Construct a solution tree by placing queens row by row.
 *  At each node (row), try all column positions.
 *  Prune (backtrack) immediately if a placement is attacked.
 *
 *  Complexity (worst case): O(n!)  with significant pruning in practice.
 * ============================================================ */

#define Q20_N 8     /* Board size — change to any value */

int q20_board[Q20_N];   /* board[row] = column of queen in that row */
int q20_solutions;      /* Count of solutions found                 */
int q20_nodes_visited;  /* Count of nodes explored in search tree   */

/* Check if placing a queen at (row, col) is safe */
int q20_is_safe(int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = q20_board[r];
        /* Same column or same diagonal */
        if (c == col || abs(c - col) == abs(r - row))
            return 0;
    }
    return 1;
}

/* Print the board for one solution */
void q20_print_board(void) {
    printf("  Solution %d: [", q20_solutions);
    for (int r = 0; r < Q20_N; r++) {
        printf("(%d,%d)", r + 1, q20_board[r] + 1);
        if (r < Q20_N - 1) printf(", ");
    }
    printf("]\n");
}

/*
 * Backtracking solver.
 * row  : current row being processed (0-indexed)
 * print: if 1, print every solution found
 */
void q20_solve(int row, int print_solutions) {
    q20_nodes_visited++;

    if (row == Q20_N) {
        /* All rows filled — valid solution */
        q20_solutions++;
        if (print_solutions) q20_print_board();
        return;
    }

    for (int col = 0; col < Q20_N; col++) {
        if (q20_is_safe(row, col)) {
            q20_board[row] = col;        /* Place queen   */
            q20_solve(row + 1, print_solutions); /* Recurse */
            q20_board[row] = -1;         /* Remove queen (backtrack) */
        }
    }
}

/* Small 4-Queens demo to illustrate the search tree */
void q20_demo_4queens(void) {
    printf("\n  --- 4-Queens Illustrated Search Tree Demo ---\n");
    printf("  (Only showing first 3 rows of search for brevity)\n\n");

    int demo_n = 4;
    int demo_board[4] = { -1, -1, -1, -1 };
    int demo_solutions = 0;

    /* Manually trace Row 0 */
    for (int c0 = 0; c0 < demo_n; c0++) {
        demo_board[0] = c0;
        printf("  Row 0: Queen @ col %d\n", c0 + 1);

        for (int c1 = 0; c1 < demo_n; c1++) {
            /* Check row 1 */
            int safe1 = (c1 != c0 && abs(c1 - c0) != 1);
            printf("    Row 1: col %d -> %s\n", c1 + 1, safe1 ? "safe" : "PRUNE");
            if (!safe1) continue;
            demo_board[1] = c1;

            for (int c2 = 0; c2 < demo_n; c2++) {
                int safe2 = (c2 != c0 && c2 != c1
                             && abs(c2 - c0) != 2
                             && abs(c2 - c1) != 1);
                printf("      Row 2: col %d -> %s\n", c2 + 1, safe2 ? "safe" : "PRUNE");
                if (!safe2) continue;
                demo_board[2] = c2;

                for (int c3 = 0; c3 < demo_n; c3++) {
                    int safe3 = (c3 != c0 && c3 != c1 && c3 != c2
                                 && abs(c3 - c0) != 3
                                 && abs(c3 - c1) != 2
                                 && abs(c3 - c2) != 1);
                    if (!safe3) continue;
                    demo_board[3] = c3;
                    demo_solutions++;
                    printf("        Row 3: col %d -> SOLUTION %d: [%d,%d,%d,%d]\n",
                           c3 + 1, demo_solutions,
                           demo_board[0]+1, demo_board[1]+1,
                           demo_board[2]+1, demo_board[3]+1);
                }
            }
        }
    }
    printf("\n  4-Queens total solutions: %d (out of 256 naive candidates)\n",
           demo_solutions);
}

void run_q20(void) {
    printf("\n");
    printf("==============================================\n");
    printf("  Q20 — Backtracking (N-Queens Problem)\n");
    printf("  Board size N = %d\n", Q20_N);
    printf("==============================================\n");

    /* 4-Queens illustrated demo */
    q20_demo_4queens();

    /* Full N-Queens solve */
    printf("\n  --- Full %d-Queens Solve ---\n", Q20_N);
    q20_solutions     = 0;
    q20_nodes_visited = 0;
    memset(q20_board, -1, sizeof(q20_board));

    /* Print solutions only for small N to avoid flooding the output */
    int print = (Q20_N <= 6) ? 1 : 0;
    q20_solve(0, print);

    printf("\n  Results for %d-Queens:\n", Q20_N);
    printf("    Total solutions    : %d\n", q20_solutions);
    printf("    Nodes visited      : %d\n", q20_nodes_visited);
    printf("    Naive search space : ");
    long long naive = 1;
    for (int i = 0; i < Q20_N; i++) naive *= Q20_N;
    printf("%lld  (N^N = %d^%d)\n", naive, Q20_N, Q20_N);
    printf("    Nodes pruned       : %lld  (%.1f%% of naive space)\n",
           naive - q20_nodes_visited,
           100.0 * (naive - q20_nodes_visited) / naive);

    printf("\n  Complexity Analysis:\n");
    printf("    Worst case (no pruning)  : O(N^N)\n");
    printf("    With column constraint   : O(N!)\n");
    printf("    With full pruning (diag) : Much smaller — empirically ~O(N!/ c)\n");
    printf("    Recursion stack space    : O(N)\n");

    printf("\n  Practical Applications:\n");
    printf("    - Sudoku solving\n");
    printf("    - Graph coloring (register allocation in compilers)\n");
    printf("    - Constraint Satisfaction Problems (AI planning, scheduling)\n");
    printf("    - SAT solvers (DPLL algorithm — hardware verification)\n");
    printf("    - Cryptarithmetic (e.g., SEND + MORE = MONEY)\n");
    printf("    - Subset sum / 0-1 Knapsack\n");
}
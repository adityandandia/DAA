#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_V 10          /* Maximum vertices supported */
#define INF   INT_MAX     /* Represents no edge         */

/* --------------- Q3 Globals --------------- */
int  q3_n;                                /* Number of vertices           */
int  q3_graph[MAX_V][MAX_V];              /* Adjacency / weight matrix    */
int  q3_perm[MAX_V];                      /* Current permutation (indices 1..n-1) */
int  q3_best_path[MAX_V];                 /* Best path found              */
long long q3_min_cost;                    /* Minimum path cost found      */
long long q3_candidates_examined;         /* Counter for task 3           */

/* Swap two integers */
void q3_swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

/* Compute total weight of path [0, perm[0], perm[1], ..., perm[n-2]] */
long long q3_path_weight(void) {
    long long cost = 0;
    int prev = 0;   /* depot is vertex 0 */
    for (int i = 0; i < q3_n - 1; i++) {
        int cur = q3_perm[i];
        if (q3_graph[prev][cur] == INF) return (long long)INF * q3_n; /* invalid path */
        cost += q3_graph[prev][cur];
        prev = cur;
    }
    return cost;
}

/*
 * Generate all permutations of q3_perm[start..n-2] using
 * Heap's algorithm (iterative-style recursive).
 */
void q3_permute(int start) {
    if (start == q3_n - 1) {
        /* Leaf node — evaluate this candidate */
        q3_candidates_examined++;
        long long cost = q3_path_weight();
        if (cost < q3_min_cost) {
            q3_min_cost = cost;
            q3_best_path[0] = 0; /* depot */
            for (int i = 0; i < q3_n - 1; i++)
                q3_best_path[i + 1] = q3_perm[i];
        }
        return;
    }
    for (int i = start; i < q3_n - 1; i++) {
        q3_swap(&q3_perm[start], &q3_perm[i]);
        q3_permute(start + 1);
        q3_swap(&q3_perm[start], &q3_perm[i]); /* backtrack */
    }
}

void run_q3(void) {
    printf("\n");
    printf("==============================================\n");
    printf("  Q3 (D2) — Min-Weight Hamiltonian Path\n");
    printf("  Exhaustive Search\n");
    printf("==============================================\n");

    /* Example: 4-city delivery network (0 = depot) */
    q3_n = 4;
    int w[4][4] = {
        {  0,  10,  15,  20 },
        { 10,   0,  35,  25 },
        { 15,  35,   0,  30 },
        { 20,  25,  30,   0 }
    };
    for (int i = 0; i < q3_n; i++)
        for (int j = 0; j < q3_n; j++)
            q3_graph[i][j] = w[i][j];

    /* Initialise perm with vertices 1..n-1 */
    for (int i = 0; i < q3_n - 1; i++)
        q3_perm[i] = i + 1;

    q3_min_cost            = (long long)INF * q3_n;
    q3_candidates_examined = 0;

    q3_permute(0);

    printf("Graph (weight matrix, vertex 0 = depot):\n");
    printf("     ");
    for (int j = 0; j < q3_n; j++) printf("%4d", j);
    printf("\n");
    for (int i = 0; i < q3_n; i++) {
        printf("  %2d:", i);
        for (int j = 0; j < q3_n; j++) printf("%4d", q3_graph[i][j]);
        printf("\n");
    }

    printf("\nMinimum-weight Hamiltonian path: ");
    for (int i = 0; i < q3_n; i++) {
        printf("%d", q3_best_path[i]);
        if (i < q3_n - 1) printf(" -> ");
    }
    printf("\nPath cost            : %lld\n", q3_min_cost);
    printf("Candidates examined  : %lld  (should be (n-1)! = %d)\n",
           q3_candidates_examined, 1 * 2 * 3 /* (4-1)! = 6 */);
    printf("Time complexity      : O(n!)\n");
    printf("n = %d  =>  (n-1)! = %lld candidates\n",
           q3_n, q3_candidates_examined);
}
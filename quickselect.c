/* ============================================================
 *  QUESTION 9 (D2)
 *  k-th Smallest Element Using Quickselect
 *
 *  Strategy (Decrease-by-Variable-Size):
 *    - Partition array around a pivot.
 *    - Recurse only on the partition that contains rank k.
 *
 *  Average-case recurrence : T(n) = T(n/2) + O(n)  =>  O(n)
 *  Worst-case recurrence   : T(n) = T(n-1) + O(n)  =>  O(n^2)
 * ============================================================ */

/*
 * Partition arr[lo..hi] around arr[hi] as pivot.
 * Returns the pivot's final index.
 */
int q9_partition(int *arr, int lo, int hi) {
    int pivot = arr[hi];
    int i     = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1]; arr[i + 1] = arr[hi]; arr[hi] = tmp;
    return i + 1;
}

/*
 * Quickselect: returns the k-th smallest element (1-indexed k).
 * Operates in-place; modifies arr.
 */
int q9_quickselect(int *arr, int lo, int hi, int k) {
    if (lo == hi) return arr[lo]; /* Single element */

    int p = q9_partition(arr, lo, hi);

    int rank = p - lo + 1; /* 1-based rank of pivot within [lo..hi] */

    if (rank == k) {
        return arr[p];              /* Pivot IS the k-th smallest */
    } else if (k < rank) {
        return q9_quickselect(arr, lo, p - 1, k);       /* Search left */
    } else {
        return q9_quickselect(arr, p + 1, hi, k - rank); /* Search right */
    }
}

void run_q9(void) {
    printf("\n");
    printf("==============================================\n");
    printf("  Q9 (D2) — Quickselect (k-th Smallest)\n");
    printf("  Decrease-by-Variable-Size Strategy\n");
    printf("==============================================\n");

    /* Simulated bids from a real-time auction */
    int bids[] = { 42, 17, 93, 5, 68, 31, 76, 24, 55, 88 };
    int n      = sizeof(bids) / sizeof(bids[0]);
    int k      = 4; /* Find the 4th lowest bid (reserve price) */

    printf("Bids received (%d bids): ", n);
    for (int i = 0; i < n; i++) printf("%d ", bids[i]);
    printf("\n");
    printf("Finding the %d-th lowest bid...\n\n", k);

    /* Make a copy so we can also verify by sorting */
    int bids_copy[20];
    memcpy(bids_copy, bids, n * sizeof(int));

    int result = q9_quickselect(bids, 0, n - 1, k);
    printf("Quickselect result  : %d-th smallest bid = %d\n", k, result);

    /* Verification by sorting */
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (bids_copy[j] > bids_copy[j + 1]) {
                int t = bids_copy[j]; bids_copy[j] = bids_copy[j+1]; bids_copy[j+1] = t;
            }
    printf("Sorted verification : ");
    for (int i = 0; i < n; i++) printf("%d ", bids_copy[i]);
    printf("\nSort-then-index[%d]  = %d  (matches: %s)\n",
           k - 1, bids_copy[k - 1], result == bids_copy[k - 1] ? "YES" : "NO");

    printf("\nComplexity Summary:\n");
    printf("  Average case : T(n) = T(n/2) + O(n)  =>  O(n)\n");
    printf("  Worst case   : T(n) = T(n-1) + O(n)  =>  O(n^2)\n");
    printf("  Sort-then-idx: O(n log n) for sort + O(1) lookup\n");
    printf("  => Quickselect is faster for a single k-th query on average.\n");
}
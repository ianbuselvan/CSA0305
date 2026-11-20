# Data Structures Assignment 3 – CO3

Seven standalone C programs for the assignment. Each question is in its own `.c` file.

## Files
- `Q1_Binary_Search_Tree.c` – BST insertion, search/comparison count, traversals, height, deletion and saving sorted data.
- `Q2_AVL_Tree.c` – AVL insertion with LL, RR, LR and RL rotations; sorted 100,000-key test.
- `Q3_B_Tree.c` – B-tree (minimum degree 2) insertion, splitting, search and node-visit count.
- `Q4_Red_Black_Tree.c` – Red-black insertion fix-up, inorder display and minimum-key lookup.
- `Q5_Splay_Tree.c` – Splay insertion, search and adaptive root updates.
- `Q6_Trie.c` – Trie insertion, exact search, prefix count, autocomplete and deletion.
- `Q7_Dictionary.c` – Dictionary design using a trie for exact lookup/autocomplete and a sorted array for range listing.

## Compile and run
Use GCC (Linux, macOS, or Windows with MinGW):

```bash
gcc -std=c11 -Wall -Wextra -O2 Q1_Binary_Search_Tree.c -o q1
./q1
```

Replace the filename and executable name for Q2–Q7. On Windows, run `q1.exe` instead of `./q1`.

## Notes
- These programs are independent; compile each file separately because each contains its own `main()`.
- Q3 uses a B-tree of minimum degree 2 (order 4), as specified in the assignment.
- Q7 demonstrates the selected combined design with a small sample dictionary. Increase the sample/input handling for a full 200,000-word dataset and measure memory/time on your system before reporting experimental results.
- Do not report timings or measurements unless you have run the programs on your own system.

# bkt_through_tetris
  Backtracking code that generates all the possible ways of filling
a tetris board with tetris tiles.

###the tiles used:
  In total there have been 5 pieces used as such:
  
  The I lengthwise and heightwise
  The one square position
  The L in the 4 possible orientations
  The Z in the 4 possible orientations
  The T in the 4 possible orientations
  
  Resulting in a total of 15 distict shapes on the tetris board

###the structure and complexity
  There are two main libraries in this project, one containing all of the printing functions and the other one the basic utility ones. In the tetris.c file are: the main, backtracking and indexing functions.

  As this is a backtracking code, its complexity is very large. Let's consider a total of 15 distinct programmed pieces and a tetris board containing m lines and n columns. The best way of reaching a relevant number that would work on large inputs is to approximate each piece to a single square in the m X n matrix. Then, the piece-placing method is best approximated by permutations of 15 for each square. With that in mind, the algorithm reaches O((15 * m * n)!), or O((m * n)!).

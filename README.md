  ## Input Format

  Input is read from the keyboard. The first line of input is the number of test cases `K`. Each of the `K` test cases is written in the following format:

  ```
  n
  city 1
  city 2
  .
  .
  .
  city n
  d11 d12 ... d1n d21 d22 ... d2n .
  .
  .
  dn1 dn2 ... dnn
  ```

  The first line of each test case is the number of cities `n` in the graph. The next `n` lines are the names of each city. City names consist only of alphabetic characters. Following the list of `n` city names is an `nxn` distance matrix where each distance `d_ij` is an integer value in the range `[0, 10000]` representing the distance of the road connecting city `i` to city `j`. A distance `d_ij = 0` indicates that there does not exist any road connecting city `i` to city `j`. For this project, all roads will be undirected, which means `d_ij = d_ji` for all cities `i` and `j`. As a result, every input distance matrix will be symmetric.

  ## Output Format

  For each test case, output a space delimited list of all the city names in the shortest path connecting city 1 and city n followed by the integer distance of the path. City 2 names should be listed in order of when they are to be visited starting from city 1 and ending with city n. If city 1 has multiple shortest paths to city n, just output one of them. Also note that in every test case, there will always be a path connecting city 1 to city n.

  ## Sample Test Cases

  Use input redirection to redirect commands written in a file to the standard input, e.g. `$ ./a.out < input1.dat`.

  ### Input 1
  ```
  1
  4
  Akron Athens Columbus Cleveland
  0120 1056 2507 0670
  ```

  ### Output 1
  ```
  Akron Athens Cleveland 7
  ```
def solve(N: int, Q: int, L: list[int], R: list[int]):
    """
    Output the resulting array A_1, A_2, ... , A_N after
    all fib-queries have completed.

    N: the length of the array A_1, A_2, ... , A_N
    Q: the number of fib-queries
    L: the list of L_i values involved with each fib-query
    R: the list of R_i values involved with each fib-query
    """
    # YOUR CODE HERE
    return


def main():
    T = int(input())
    for _ in range(T):
        info = input().strip().split()
        N, Q = int(info[0]), int(info[1])
        L, R = [], []
        for _ in range(Q):
            fibq = input().strip().split()
            L.append(int(fibq[0]))
            R.append(int(fibq[1]))
        solve(N, Q, L, R)

if __name__ == '__main__':
    main()

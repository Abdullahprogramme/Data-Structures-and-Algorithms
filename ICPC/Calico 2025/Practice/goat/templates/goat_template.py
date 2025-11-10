def solve(N: int, Q: int, P: list[int], A: list[int], G: list[int]) -> int:
    """
    Given a rooted tree, with each vertex labeled A_1, A_2, .., A_N,
    find the result of all Q GOAT queries.
    
    N: the size of the tree
    Q: the number of GOAT queries
    P: the list of parent nodes for each vertex
    A: the list of labels on the vertices of the tree
    G: the list of each GOAT query
    """
    # YOUR CODE HERE
    return


def main():
    T = int(input())
    for _ in range(T):
        info = input().strip().split(' ')
        N, Q = int(info[0]), int(info[1])
        P = [int(x) for x in input().strip().split(' ')]
        A = [int(x) for x in input().strip().split(' ')]
        G = [int(x) for x in input().strip().split(' ')]
        solve(N, Q, P, A, G)

if __name__ == '__main__':
    main()

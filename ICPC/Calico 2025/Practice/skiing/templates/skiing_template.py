def solve(N: int, M: int, X: list[int], Y: list[int], Z: list[int]):
    """
    Output the true difficulty of each trail given
    a mountain range with N checkpoints and M trails
    between them.

    N: the number of checkpoints on the mountain
    M: the number of available trails between checkpoints
    X: the list of X_i, the checkpoints at the start of each trail
    Y: the list of Y_i, the checkpoints at the end of each trail
    Z: the list of Z_i, the skill levels needed to traverse each trail
    """
    # YOUR CODE HERE
    return

def main():
    T = int(input())
    for _ in range(T):
        info = input().strip().split(' ')
        N, M = int(info[0]), int(info[1])
        X, Y, Z = [], [], []
        for i in range(M):
            info = input().strip().split(' ')
            X.append(int(info[0]))
            Y.append(int(info[1]))
            Z.append(int(info[2]))
        solve(N, M, X, Y, Z)

if __name__ == '__main__':
    main()

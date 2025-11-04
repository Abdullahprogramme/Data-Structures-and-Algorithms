def solve(Q: int, N: int, M: int, X: list[str], R: list[int], U: list[int]):
    '''
    Output the number of times each user is pinged in the server after
    all actions.

    Q: the total number of actions
    N: the number of roles in the server
    M: the number of users in the server
    X: the list of actions performed at each timestep
    R: the list of roles involved at each timestep
    U: the list of users involved at each timestep, or -1 if the action is a ping
    '''
    # YOUR CODE HERE

def main():
    T = int(input())
    for _ in range(T):
        info = input().strip().split(' ')
        Q, N, M = int(info[0]), int(info[1]), int(info[2])
        X = [None for _ in range(Q)]
        R = [None for _ in range(Q)]
        U = [None for _ in range(Q)]
        for i in range(Q):
            info = input().strip().split(' ')
            X[i] = info[0]
            R[i], U[i] = int(info[1]), -1 if X[i] == 'P' else int(info[2])
        solve(Q, N, M, X, R, U)

if __name__ == '__main__':
    main()

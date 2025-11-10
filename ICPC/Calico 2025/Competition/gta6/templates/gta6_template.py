Y_0 = 2026
M_0 = 11
D_0 = 19

def solve(E: str, D: int, M: int, Y: int) -> str:

    """

    E: The name of the event
    Y: Year
    M: Month
    D: Day
    """
    # YOUR CODE HERE
    before = 'we got ' + E + ' before gta6'
    after = 'we got gta6 before ' + E

    return before if Y < Y_0 or (Y == Y_0 and M < M_0) or (Y == Y_0 and M == M_0 and D < D_0) else after

def main():
    T = int(input())
    for _ in range(T):
        E = input()
        temp = input().split()
        Y, M, D = int(temp[0]), int(temp[1]), int(temp[2])
        print(solve(E, Y, M, D))

if __name__ == 'main':
    main()
def solve(N: int, D: int, L: list[int]) -> int:
    """
    NOTE: This template reads in values as int. You may want to change this for
    bonus test sets.
    
    Find the largest D digit number that does not contain any unlucky number
    from L.

    N: the number of unlucky numbers
    D: the number of digits in the number to find
    L: the list of unlucky numbers
    """
    # YOUR CODE HERE
    return -1


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N, D = int(temp[0]), int(temp[1])
        L = [int(l) for l in input().split()]
        print(solve(N, D, L))


if __name__ == '__main__':
    main()

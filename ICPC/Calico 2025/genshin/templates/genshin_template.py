def solve(P: int) -> None:
    """
    Starting with P primogems, get Baizhu through wishing without buying more
    primogems than necessary.
    
    Call the buy and wish functions below to make buy and wish queries. This
    template handles parsing P and checking for CORRECT after you get Baizhu.
    
    P: the number of starting primogems
    """
    # YOUR CODE HERE


def buy() -> int:
    """
    Buy primogems. Returns the number of primogems you got.
    """
    print('buy', flush=True)
    response = input()
    if response == 'WRONG_ANSWER':
        exit()
    you, got, amount, primogems = response.split()
    return int(amount)


def wish() -> str:
    """
    Wish for a random item. Returns the name of the item you got.
    """
    print('wish', flush=True)
    response = input()
    if response == 'WRONG_ANSWER':
        exit()
    you, got, item = response.split()
    return item


def main():
    T = int(input())
    for _ in range(T):
        P = int(input())
        solve(P)
        response = input()
        if response == 'WRONG_ANSWER':
            exit()


if __name__ == '__main__':
    main()

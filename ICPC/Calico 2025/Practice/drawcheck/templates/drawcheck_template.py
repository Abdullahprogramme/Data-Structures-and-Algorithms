def solve() -> None:
    """
    Find the number on the judge's card through draw and check queries while
    minimizing the average number of queries needed.
    
    Call the draw and check functions below to make draw and check queries. Return
    from this function when you see check() return ABSENT. This template also
    handles reading the final verdict at the end.
    """
    # YOUR CODE HERE


def draw() -> list[int]:
    """
    Shuffle the deck and draw the top 17 cards.
    """
    print('draw', flush=True)
    response = input()
    if response == 'WRONG_ANSWER':
        exit()
    return list(map(int, response.split()))


def check(card: int) -> str:
    """
    Check if a card exists within the deck.
    """
    print('check', card, flush=True)
    response = input()
    if response == 'WRONG_ANSWER':
        exit()
    return response


def main():
    T = int(input())
    for _ in range(T):
        solve()
    verdict = input()


if __name__ == '__main__':
    main()

def compute_grundy(L, C):
    # Precompute Grundy numbers for all positions
    grundy = [[0] * (C + 1) for _ in range(L + 1)]
    for l in range(L + 1):
        for c in range(C + 1):
            reachable = set()
            for u in range(1, max(L, C) + 1):
                if l - u >= 0:
                    reachable.add(grundy[l - u][c])  # Move vertically
                if c - u >= 0:
                    reachable.add(grundy[l][c - u])  # Move horizontally
                if l - u >= 0 and c - u >= 0:
                    reachable.add(grundy[l - u][c - u])  # Move diagonally
            # Calculate minimum excluded value (mex)
            grundy[l][c] = 0
            while grundy[l][c] in reachable:
                grundy[l][c] += 1
    return grundy

def emperor_game(N, positions, L, C):
    # Compute Grundy numbers for the entire board
    grundy = compute_grundy(L, C)
    
    # XOR the Grundy numbers of all starting positions
    xor_sum = 0
    for l, c in positions:
        xor_sum ^= grundy[l][c]
    
    # Determine if the Emperor can win
    return "Y" if xor_sum != 0 else "N"

# Input
N = int(input())
positions = [tuple(map(int, input().split())) for _ in range(N)]

# Constants for board dimensions (100x100 grid)
L, C = 100, 100

# Output result
print(emperor_game(N, positions, L, C))

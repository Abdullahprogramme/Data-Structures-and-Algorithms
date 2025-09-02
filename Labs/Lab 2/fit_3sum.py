# Calculate a and b for T(n) = a * n^b using last two data points
import math

def fit_power_law(n1, t1, n2, t2):
    # log(T2/T1) = b 
    b = math.log(t2/t1, 2)
    a = t2 / (n2 ** b)
    return a, b

# Data from user
n1, t1 = 8000, 21.5648
n2, t2 = 16000, 169.666

a, b = fit_power_law(n1, t1, n2, t2)
print(f"a = {a}")
print(f"b = {b}")
print(f"T(n) ≈ {a:.6g} * n^{b:.3f}")

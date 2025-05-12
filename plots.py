import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = {
  "Input Sizes": [1, 2, 5, 10, 15, 20, 25, 26, 35, 50, 100, 200],
  "Held-Karp Runtimes (s)": [
      0.000002, 0.000003, 0.000028, 0.001911,
      0.112411, 5.938734, 287.409284, 221.282872,
      None, None, None, None
  ],
  "Local Search Runtimes (s)": [
      0, 0, 0, 0,
      0, 0.001, 0.001, 0.002,
      0.005, 0.015, 0.110, 1.029
  ]
}

def HKApprox(n):
    return np.exp(0.75 * n) * 1.57e-6

def LSApprox(n):
    a = 1.6917e-7
    b = -1.0726e-5
    c = 5.6465e-4
    d = 0.0083
    
    result = a * n**3
    result += b * n**2
    result += c * n
    result += d
    
    return result

df = pd.DataFrame(data)

# Clean the data - remove None values
valid_data = df["Held-Karp Runtimes (s)"].notna()
valid_hk_data = df[valid_data]

# Create plot
plt.figure()

# Plot actual data points
plt.plot(valid_hk_data["Input Sizes"], valid_hk_data["Held-Karp Runtimes (s)"], 'ro', label="Held-Karp (Actual)")
plt.plot(df["Input Sizes"], df["Local Search Runtimes (s)"], 'bo', label="Local Search (Actual)")

# Plot approximation functions
n_vals = np.linspace(1, 30, 100)
hk_est = HKApprox(n_vals)
plt.plot(n_vals, hk_est, 'r-', label="Held-Karp (Approximation)")

n_vals = np.linspace(1, 200, 100)
ls_est = LSApprox(n_vals)
plt.plot(n_vals, ls_est, 'b-', label="Local Search (Approximation)")

# Labels and formatting
plt.xlabel("Input Size (n)")
plt.ylabel("Runtime (seconds)")
plt.title("TSP Algorithm Runtimes")
plt.legend()
plt.grid(True)

# Use logarithmic scale for y-axis due to large differences in magnitude
plt.yscale('log')

plt.show()
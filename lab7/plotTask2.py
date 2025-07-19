import matplotlib.pyplot as plt

# Data
n_values = [4, 14, 15, 17, 22]
recursive_times = [24, 87178291200, 1307674368000, 355687428096000, 17196083355034583040]
iterative_times = [24, 1278945280, 2004310016, 18446744073421029376, 18446744073186836480]

# Plot
plt.figure(figsize=(10, 6))
plt.plot(n_values, recursive_times, marker='o', label='Recursive')
plt.plot(n_values, iterative_times, marker='s', label='Iterative')

# Labels and title
plt.xlabel('n (Factorial Input)')
plt.ylabel('Result (Factorial Value)')
plt.title('Recursive vs Iterative Factorial Calculation')
plt.yscale('log')  # Use logarithmic scale to handle large numbers
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Show plot
plt.tight_layout()
plt.show()

import matplotlib.pyplot as plt

n_values = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
recursive_times = [108, 82, 89, 111, 125, 83, 151, 91, 118, 99]
iterative_times = [76, 103, 101, 76, 103, 118, 168, 132, 116, 116]

plt.figure(figsize=(10, 6))
plt.plot(n_values, recursive_times, marker='o', label='Recursive')
plt.plot(n_values, iterative_times, marker='s', label='Iterative')

plt.title('Fibonacci Time Comparison: Recursive vs Iterative')
plt.xlabel('n')
plt.ylabel('Time (microseconds)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

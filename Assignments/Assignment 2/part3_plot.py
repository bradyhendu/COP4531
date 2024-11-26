import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Load the results from the CSV file
data = pd.read_csv("part3_results.csv")

# Extract the data
hash_table_sizes = data["Hash Table Size"]
average_search_lengths = data["Average Search Length"]

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(hash_table_sizes, average_search_lengths, marker='o', label="Average Search Length")

# Add labels and title
plt.title("Average Search Length vs Hash Table Size")
plt.xlabel("Hash Table Size (log scale)")
plt.ylabel("Average Search Length")
plt.xscale("log", base=2)
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.legend()

# Save and show the plot
plt.savefig("part3_plot.png")
plt.show()

import csv
import matplotlib.pyplot as plt
import numpy as np

# Read data from a CSV file
def read_csv(filename):
    load_factors = []
    avg_probes = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip the header
        for row in reader:
            load_factors.append(float(row[0]))
            avg_probes.append(float(row[1]))
    return load_factors, avg_probes

# Calculate the theoretical best-case model
def calculate_theoretical(load_factors):
    return [1 / (1 - alpha) for alpha in load_factors]

# Plot the results
def plot_results(load_factors, observed, theoretical, title, output_file):
    plt.figure(figsize=(10, 6))
    plt.plot(load_factors, observed, marker='o', label='Observed Probes')
    plt.plot(load_factors, theoretical, linestyle='--', label='Theoretical Probes (1 / (1 - α))')

    # Add labels, title, legend
    plt.xlabel('Load Factor (α)')
    plt.ylabel('Average Number of Probes')
    plt.title(title)
    plt.legend()
    plt.grid(True)

    # Save and show the plot
    plt.savefig(output_file)
    plt.show()

# Main function to process and plot a specific file
def process_and_plot(filename, title, output_file):
    # Read data
    load_factors, avg_probes = read_csv(filename)

    # Calculate theoretical values
    theoretical = calculate_theoretical(load_factors)

    # Plot the results
    plot_results(load_factors, avg_probes, theoretical, title, output_file)

# Main driver function
if __name__ == "__main__":
    # Plot for linear probing results
    process_and_plot(
        filename="linear_probing_results.csv",
        title="Linear Probing: Observed vs Theoretical Performance",
        output_file="linear_probing_plot.png"
    )

    process_and_plot(
        filename="quadratic_probing_results.csv",
        title="Quadratic Probing: Observed vs Theoretical Performance",
        output_file="quadratic_probing_plot.png"
    )
    
    process_and_plot(
        filename="double_hashing_results.csv",
        title="Double Hashing: Observed vs Theoretical Performance",
        output_file="double_hashing_plot.png"
    )
    
    process_and_plot(
        filename="part1_probing_results.csv",
        title="My h1(k): Observed vs Theoretical Performance",
        output_file="part1_plot.png"
    )


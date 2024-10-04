import pandas as pd
import matplotlib.pyplot as plt


def big_o(file_path):
    data = pd.read_csv(file_path)
    print(data)

    plt.figure(figsize=(10,6))
    plt.plot(data['ArraySize'], data['TimeMicroseconds'], marker='o', linestyle='-', color='b')

        # Add titles and labels
    plt.title('Sorting Time vs Array Size')
    plt.xlabel('Array Size')
    plt.ylabel('Time (Microseconds)')
    plt.grid(True)

    # Show the plot
    plt.xscale('log')  # Use logarithmic scale for better visualization
    plt.yscale('log')  # Use logarithmic scale for better visualization
    plt.xticks(data['ArraySize'], rotation=45)  # Rotate x-axis labels for better readability
    plt.tight_layout()  # Adjust layout for better fitting
    plt.show()

if __name__ == "__main__":
    big_o('sorting_times.csv')
import matplotlib.pyplot as plt
import pandas as pd

#read CSV
def read_csv(file):
    data = pd.read_csv(file)
    print(data)
    return data

#plot data
def plot_data(data, title):
    x = data['Array Size']
    y = data['Time']
    plt.plot(x, y, label=title)
    plt.xlabel('Array Size')
    plt.ylabel('Time (s)')
    plt.title('Array Size vs Time')
    plt.show()
    
if __name__ == "__main__":
    data = read_csv("insertion.csv")
    plot_data(data, "Insertion Sort")
    
    


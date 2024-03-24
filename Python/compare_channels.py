from matplotlib import pyplot as plt
import json
import os
#import plotly.graph_objects as go
import pyfar as pf

sample_rate = 48000

# Get the directory of the current Python script
current_directory = os.path.dirname(os.path.realpath(__file__))

# List all files and directories in the current directory
files_in_directory = os.listdir(current_directory)
file_path = os.path.join(os.getcwd(), "psx.json")

with open(file_path, "r") as read_file:
    psx = json.load(read_file)

binRevL = psx["binRevL"]
binRevR = psx["binRevR"]

binRevL = pf.Signal(binRevL)
binRevR = pf.Signal(binRevR)
diff = binRevL - binRevR

def plot_time(data, name):
    ax = pf.plot.time(data)
    plt.close() # close down to avoid plotting in the same fig over and over again
    fig = ax.get_figure() # Get the figure from the existing axes
    fig.suptitle(name, fontsize=16)
    fig.savefig(name, bbox_inches='tight')

plot_time(binRevL, 'binRevL')
plot_time(binRevR, 'binRevR')
plot_time(diff, 'diff')
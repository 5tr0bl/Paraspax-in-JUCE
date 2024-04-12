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

file_path = os.path.join(current_directory, "psx.json")
file_path_buffer = os.path.join(current_directory, "binRevBuffer.json")
file_path_weighted = os.path.join(current_directory, "binRevWeighted.json")
file_path_weightedNew = os.path.join(current_directory, "binRevWeightedNew.json")
file_path_wfInv = os.path.join(current_directory, "wfInv.json")

with open(file_path, "r") as read_file:
    psx = json.load(read_file)
binRevLeft = psx["binRevL"]
binRevRight = psx["binRevR"]
binRevL = pf.Signal(binRevLeft, sample_rate)
binRevR = pf.Signal(binRevRight, sample_rate)
diff = binRevL - binRevR
sum = pf.Signal([binRevLeft,binRevRight], sample_rate)

with open(file_path_weightedNew, "r") as read_file:
    juceBinRevBufferWeightedNew = json.load(read_file)
juceBinRevWeightedNew = pf.Signal([juceBinRevBufferWeightedNew["leftChannel"],juceBinRevBufferWeightedNew["rightChannel"]], sample_rate)
'''

with open(file_path_buffer, "r") as read_file:
    juceBinRevBuffer = json.load(read_file)
juceBinRev = pf.Signal([juceBinRevBuffer["leftChannel"],juceBinRevBuffer["rightChannel"]], sample_rate)

with open(file_path_weighted, "r") as read_file:
    juceBinRevBufferWeighted = json.load(read_file)
juceBinRevWeighted = pf.Signal([juceBinRevBufferWeighted["leftChannel"],juceBinRevBufferWeighted["rightChannel"]], sample_rate)

with open(file_path_wfInv, "r") as read_file:
    juceWfInvJson = json.load(read_file)
juceWfInv = pf.Signal(juceWfInvJson, sample_rate)
'''

def plot_time(data, name):
    ax = pf.plot.time(data)
    ax.set_xlim([0, 0.2])
    plt.close() # close down to avoid plotting in the same fig over and over again
    fig = ax.get_figure() # Get the figure from the existing axes
    fig.suptitle(name, fontsize=16)
    fig.savefig(name, bbox_inches='tight')

#plot_time(binRevL, "binRevL")
#plot_time(binRevR, 'binRevR')
#plot_time(diff, 'diff')
#plot_time(sum, 'sum')
    
#plot_time(juceBinRev, 'binRev')
#plot_time(juceBinRevWeighted, 'binRevWeighted')
plot_time(juceBinRevWeightedNew, 'binRevWeighted 2nd Recommendation')
#plot_time(juceWfInv, 'wfInv')

'''
sineA = pf.signals.sine(100, sample_rate, sampling_rate=sample_rate)
sineB = pf.signals.sine(100, sample_rate, sampling_rate=sample_rate)
sineDiff = sineA - sineB
plot_time(sineDiff, 'sineDiff')
'''
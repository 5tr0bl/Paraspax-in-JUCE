'''
Same as measurements_eval.py, but without compensation of an input signal
'''

from matplotlib import pyplot as plt
import os
import pyfar as pf

sample_rate = 48000
PLOT_TYPE = 'time' #'mag' 'gd' 

measurement_paths = []
measurement_paths.append("Python\Measurements\SOFA samples")

plots_paths = []
plots_paths.append("Python\Plots\SOFA samples")



def process_and_plot_wav(wav_file_path, plot_path, plot_type):
    path_references = "Python\ReferenceInputs"
    file_path = os.path.splitext(os.path.basename(wav_file_path))[0]
    plot_file_name = os.path.join(plot_path, file_path + '.png')
    print(f"Processing file: {file_path}")

    # Get signals as pyfar Signals
    output_signal = pf.io.read_audio(wav_file_path)
    
    # plotting
    if (plot_type == 'mag'):
        ax = pf.plot.freq(output_signal) # returns --> ax : matplotlib.pyplot.axes

    elif (plot_type == 'time'):
        ax = pf.plot.time(output_signal)
        #ax.set_xlim([0, 0.5])

    elif (plot_type == 'gd'):
        ax = pf.plot.group_delay(output_signal)

    plt.close()
    fig = ax.get_figure() # Get the figure from the existing axes
    fig.suptitle(file_path, fontsize=16)
    fig.savefig(plot_file_name, bbox_inches='tight')

for measurement_path, plot_path in zip(measurement_paths, plots_paths):
    print(f"Processing files in {measurement_path}:")
    os.makedirs(plot_path, exist_ok=True)

    for filename in os.listdir(measurement_path):
        if filename.endswith(".wav"):
            wav_file_path = os.path.join(measurement_path, filename)
            print(f"Processing file: {wav_file_path}")
            process_and_plot_wav(wav_file_path, plot_path, PLOT_TYPE)
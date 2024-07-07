import numpy as np
import os
import pyfar as pf
import matplotlib.pyplot as plt

'''
This script looks for JUCE/Matlab-measurement pairs representing the same scenario (like "spatialized" & "specular only")
It compares the energies of the two signals and plots the deviation of the JUCE transfer function relative to the Matlab transfer function
'''

sample_rate = 48000

def find_input_reference(wav_file_path, path_references):
    wav_prefix = os.path.basename(wav_file_path).split('_')[0]
    for ref_filename in os.listdir(path_references):
        ref_prefix = ref_filename.split('_')[0]
        if ref_prefix == wav_prefix:
            print(f"Reference input file: {ref_filename}")
            return ref_filename
    # FileNotFoundError
    print(f"No input reference found for {wav_file_path}")
    return None

def adjust_energy(signal, target_energy, current_energy):
    adjustment_factor = target_energy / current_energy
    return signal * adjustment_factor, adjustment_factor

def get_energy(wav_file_path, energy_type, total_num_samples):
    path_references = "Python\ReferenceInputs"
    file_path = os.path.splitext(os.path.basename(wav_file_path))[0]

    # Get signals as pyfar Signals
    output_signal = pf.io.read_audio(wav_file_path)
    input_reference_path = os.path.join(path_references, 
                                        find_input_reference(wav_file_path=file_path,
                                                             path_references=path_references))
    input_signal = pf.io.read_audio(input_reference_path)
    
    if input_signal.sampling_rate != sample_rate:
        input_signal = pf.dsp.resample(input_signal, sample_rate)

    # Pad zeros to the shorter signal to make both signals have the same length
    # Note: in this version of the function the signals will be padded to an externally determined value
    # since two signals (JUCE/Matlab) will be compared, so the longer one of these determines the length here
    max_length = total_num_samples # max(output_signal.n_samples, input_signal.n_samples)
    if output_signal.n_samples < max_length:
        output_signal = pf.dsp.pad_zeros(output_signal, max_length - output_signal.n_samples)
    if input_signal.n_samples < max_length:
        input_signal = pf.dsp.pad_zeros(input_signal, max_length - input_signal.n_samples)
    print(f"Length Output: {output_signal.n_samples} Samples.")
    print(f"Length Input: {input_signal.n_samples} Samples.")

    # get regularized inverse of input for --- H = (1/X) * Y
    input_signal_reg_inv = pf.dsp.regularized_spectrum_inversion(input_signal,
                                                                 freq_range=(0, input_signal.sampling_rate/2))

    # H = (1/X) * Y
    transfer_function = input_signal_reg_inv * output_signal

    if(energy_type == 'rms'):
        energy = pf.dsp.rms(transfer_function)
    elif(energy_type == 'energy'):
        energy = pf.dsp.energy(transfer_function)
    elif(energy_type == 'power'):
        energy = pf.dsp.power(transfer_function)
    
    return energy, transfer_function

measurement_paths = []
measurement_paths.append("Python\\Measurements\\Dirac_CR2_FacingSource")
measurement_paths.append("Python\\Measurements\\Dirac_CR3_FacingSource")
measurement_paths.append("Python\\Measurements\\Dirac_CR4_FacingSource")

# New base path for plots and text files
new_base_path = "Python\\Plots\\EnergyDeviation"

if measurement_paths:
    for measurement_path in measurement_paths:
        measurement_files = [f for f in os.listdir(measurement_path) if f.endswith(".wav")]

        # Define the new directory structure
        new_path = measurement_path.replace("Python\\Measurements", new_base_path)
        os.makedirs(new_path, exist_ok=True)
        
        # Open a text file to write the output
        with open(os.path.join(new_path, 'energy_deviation_output.txt'), 'w') as output_file:
            # Group files by scenario (excluding method prefix)
            scenarios = {}
            for filename in measurement_files:
                method = filename.split('_')[1]
                scenario = '_'.join(filename.split('_')[2:])
                if scenario not in scenarios:
                    scenarios[scenario] = {}
                scenarios[scenario][method] = filename
            
            for scenario, methods in scenarios.items():
                if 'juce' in methods and 'matlab' in methods:
                    juce_file = os.path.join(measurement_path, methods['juce'])
                    matlab_file = os.path.join(measurement_path, methods['matlab'])

                    # check which file is longer, than pass that num_samples into function for padding
                    juce_file_length = pf.io.read_audio(juce_file).n_samples
                    matlab_file_length = pf.io.read_audio(matlab_file).n_samples
                    total_num_samples = np.max([juce_file_length, matlab_file_length])
                    
                    juce_energy, juce_transfer_function = get_energy(juce_file, 'rms', total_num_samples)
                    matlab_energy, matlab_transfer_function = get_energy(matlab_file, 'rms', total_num_samples)
                    
                    mean_juce_energy = np.mean(juce_energy)
                    mean_matlab_energy = np.mean(matlab_energy)
                    
                    output_file.write(f'\nRMS energy for {methods["juce"]} = {mean_juce_energy}\n')
                    output_file.write(f'RMS energy for {methods["matlab"]} = {mean_matlab_energy}\n')
                    
                    if mean_juce_energy > mean_matlab_energy:
                        output_file.write(f'Adjusting energy of {methods["matlab"]} to match {methods["juce"]}\n')
                        adjusted_signal, adjustment_factor = adjust_energy(pf.io.read_audio(matlab_file), mean_juce_energy, mean_matlab_energy)
                        #adjusted_transfer_function = adjusted_signal * matlab_transfer_function / mean_matlab_energy
                        matlab_transfer_function *= adjustment_factor
                        output_file.write(f'Energy of {methods["matlab"]} adjusted by {adjustment_factor}\n')
                    else:
                        output_file.write(f'Adjusting energy of {methods["juce"]} to match {methods["matlab"]}\n')
                        adjusted_signal, adjustment_factor = adjust_energy(pf.io.read_audio(juce_file), mean_matlab_energy, mean_juce_energy)
                        #adjusted_transfer_function = adjusted_signal * juce_transfer_function / mean_juce_energy
                        juce_transfer_function *= adjustment_factor
                        output_file.write(f'Energy of {methods["juce"]} adjusted by {adjustment_factor}\n')
                
                   # Compute the difference between the transfer functions
                    juce_freq_response = juce_transfer_function.freq
                    matlab_freq_response = matlab_transfer_function.freq
                    difference = np.abs(juce_freq_response - matlab_freq_response)**2 / np.abs(matlab_freq_response)**2
                    
                    # Plotting the difference
                    '''
                    plt.figure(figsize=(8, 6))
                    plt.semilogx(matlab_transfer_function.frequencies, difference)
                    plt.title(f'Deviation between JUCE and MATLAB Transfer Functions - {scenario}')
                    plt.xlabel('Frequency (Hz)')
                    plt.ylabel('Deviation')
                    plt.grid(True)
                    '''
                    ax = pf.plot.freq(
                        pf.FrequencyData(difference, juce_transfer_function.frequencies),
                        dB=False,
                        log_prefix='log10'
                    )
                    fig = ax.get_figure() # Get the figure from the existing axes
                    fig.suptitle(f'{scenario}_deviation', fontsize=16)
                    
                    plot_file_name = os.path.join(new_path, f'{scenario}_deviation.png')
                    plt.savefig(plot_file_name, bbox_inches='tight')
                    plt.close()
                
                else:
                    output_file.write(f'\nSkipping comparison for scenario {scenario} as not both scenarios are represented.\n')
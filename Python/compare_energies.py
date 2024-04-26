import numpy as np
import os
import pyfar as pf

sample_rate = 48000

# these were given out by the processing below
rms_juce_diff = 0.0073198488240996465
rms_juce_full = 0.00757840865292856
rms_juce_spec = 0.002723093948926579
rms_matlab_diff = 0.009398949713085336
rms_matlab_full = 0.009934842619160777
rms_matlab_spec = 0.007881204629664526
# newer values for juce after attenuating diffuse part with factor 0.444
rms_juce_diff = 0.0032988879689772287
rms_juce_full = 0.0042064859162549584
rms_juce_spec = 0.0027929382427982104

print(f'The ratio of diff_matlab/diff_juce is {rms_matlab_diff/rms_juce_diff}')
print(f'The ratio of spec_matlab/spec_juce is {rms_matlab_spec/rms_juce_spec}')
print(f'The ratio of diff_matlab/spec_matlab is {rms_matlab_diff/rms_matlab_spec}')
print(f'The ratio of diff_juce/spec_juce is {rms_juce_diff/rms_juce_spec}')

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

def get_energy(wav_file_path, energy_type):
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
    max_length = max(output_signal.n_samples, input_signal.n_samples)
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
    
    return energy


measurement_paths = []
#measurement_paths.append("Python\Measurements\Dirac_JUCE_1604")
#measurement_paths.append("Python\Measurements\Matlab BRIRs")
#measurement_paths.append("Python\Measurements\Dirac_JUCE_2304")

if measurement_paths:
    for measurement_path in measurement_paths:
        for filename in os.listdir(measurement_path):
            if filename.endswith(".wav"):
                wav_file_path = os.path.join(measurement_path, filename)
                e = get_energy(wav_file_path, 'rms')
                mean = np.mean(e)
                print(f'Energy for {filename} = {e}')
                print(f'Mean energy for both channels of {filename} = {mean}')
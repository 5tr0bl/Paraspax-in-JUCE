import librosa
from matplotlib import pyplot as plt
import numpy as np
import os
import pyfar as pf

sennheiser_bw = [25,15000]
processing_bw = [100, 15000]

raw_path = os.path.join(os.path.dirname(__file__),"Raw")
bandlim_path = os.path.join(os.path.dirname(__file__),"Bandlimited")
wav_files = [f for f in os.listdir(raw_path) if f.endswith('.wav')]

for i in range(len(wav_files)):
    file_path = os.path.join(raw_path, wav_files[i])

    ### Librosa for spectral analysis
    y, sample_rate = librosa.load(file_path, sr=None)  # sr=None keeps the original sample rate
    duration = librosa.get_duration(y=y, sr=sample_rate)
    spectral_bandwidth = librosa.feature.spectral_bandwidth(y=y, sr=sample_rate)
    avg_bandwidth = np.mean(spectral_bandwidth)
    print(f"File {i + 1}: {wav_files[i]}")
    print(f"  - Sample Rate: {sample_rate} Hz")
    print(f"  - Duration: {duration:.2f} seconds")
    print(f"  - Estimated Bandwidth: {avg_bandwidth:.2f} Hz")

    ### Pyfar for filtering
    signal = pf.io.read_audio(file_path)

    # create Butter Bandpass
    filtered_signal = pf.dsp.filter.butterworth(
        signal=signal,
        N=4,
        frequency=processing_bw,
        btype="bandpass"
    )
    #filtered_signal = pf.dsp.filter.signal_filter(signal, butterworth_filter)
    output_path = os.path.join(bandlim_path, f"{wav_files[i]}_bandlimited.wav")
    pf.io.write_audio(filtered_signal, output_path)

    # Plotting
    fig, axs = plt.subplots(2, 1, figsize=(10, 8))
    signal_smoothed = pf.dsp.smooth_fractional_octave(signal, 12)[0]
    pf.plot.freq(signal_smoothed, ax=axs[0])
    axs[0].set_title('Original Bandwidth')

    filtered_signal_smoothed = pf.dsp.smooth_fractional_octave(filtered_signal, 12)[0]
    pf.plot.freq(filtered_signal_smoothed, ax=axs[1])
    axs[1].set_title('Limited Bandwidth')

    fig.tight_layout()
    plt.show()

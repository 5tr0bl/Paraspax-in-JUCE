from matplotlib import pyplot as plt
import os
import pyfar as pf

__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
ir_raw = pf.io.read_audio(os.path.join(__location__, "BOL_IR_raw.wav"))
ir_postPro = pf.io.read_audio(os.path.join(__location__, "BOL_IR_postProcessed.wav"))

ir_raw_2 = pf.io.read_audio(os.path.join(__location__, "CR2_IR_raw.wav"))
ir_postPro_2 = pf.io.read_audio(os.path.join(__location__, "CR2_IR_postProcessed.wav"))

fig, axs = plt.subplots(2, 2, figsize=(20, 16))

pf.plot.time(ir_raw_2, ax=axs[0][0])
axs[0][0].set_title('Raw IR time-domain')
axs[0][0].set_xlim([0.0, 0.2])

pf.plot.freq(ir_raw_2, ax=axs[0][1])
axs[0][1].set_title('Raw IR freq-domain')

pf.plot.time(ir_postPro_2, ax=axs[1][0])
axs[1][0].set_title('Processed IR time-domain')
axs[1][0].set_xlim([0.0, 0.2])

pf.plot.freq(ir_postPro_2, ax=axs[1][1])
axs[1][1].set_title('Processed IR freq-domain')

fig.tight_layout()

plot_file_name = os.path.join(__location__, 'ir_analysis_CR2L.png')
plt.savefig(plot_file_name, bbox_inches='tight')
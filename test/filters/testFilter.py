import math
import numpy as np
import matplotlib.pyplot as plt

freq = []
sig_flt_1st = []
sig_flt_2nd = []
gains_1st = []
gains_2nd = []

with open('/tmp/filter-freq-analysis.txt') as f:
    for line in f:
        content = line.rstrip().split("=")
        #print(content[0])
        if content[0].rstrip() == "freq":
            freq.append(float(content[1]))
            if sig_flt_1st:
                sig_flt_1st = [abs(ele) for ele in sig_flt_1st]
                gain = 20*math.log10(max(sig_flt_1st))
                gains_1st.append(gain)
            sig_flt_1st = []
            if sig_flt_2nd:
                sig_flt_2nd = [abs(ele) for ele in sig_flt_2nd]
                gain = 20*math.log10(max(sig_flt_2nd))
                gains_2nd.append(gain)
            sig_flt_2nd = []
        else:
            content = line.rstrip().split("\t")
            sig_flt_1st.append(float(content[0]))
            sig_flt_2nd.append(float(content[1]))
    gain = max(sig_flt_1st)
    gains_1st.append(20*math.log10(gain))
    gain = max(sig_flt_2nd)
    gains_2nd.append(20*math.log10(gain))

freq = np.array(freq)
gains_1st = np.array(gains_1st)

plt.plot(freq, gains_1st)
plt.plot(freq, gains_2nd)
plt.grid()
plt.show()



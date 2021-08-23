import math, subprocess
import numpy as np
import matplotlib.pyplot as plt

class bwLowPassFltAnalyzor:
    def __init__(self, cutOffFreq, sampleFreq):
        self.run_analysis(cutOffFreq, sampleFreq)
        self.freq = []
        self.sig_flt_1st = []
        self.sig_flt_2nd = []
        self.gains_1st = []
        self.gains_2nd = []
        
    def run_analysis(self, cutOffFreq, sampleFreq):
        subprocess.check_output(["./../../build/test/filters/filtersFreqAnalysis.out", "-c", str(cutOffFreq), "-s", str(sampleFreq)])

    def load_freq_response(self):
        with open('/tmp/filter-freq-analysis.txt') as f:
            for line in f:
                content = line.rstrip().split("=")
                if content[0].rstrip() == "freq":
                    self.freq.append(float(content[1]))
                    if self.sig_flt_1st:
                        self.sig_flt_1st = [abs(ele) for ele in self.sig_flt_1st]
                        gain = 20*math.log10(max(self.sig_flt_1st))
                        self.gains_1st.append(gain)
                    self.sig_flt_1st = []
                    if self.sig_flt_2nd:
                        self.sig_flt_2nd = [abs(ele) for ele in self.sig_flt_2nd]
                        gain = 20*math.log10(max(self.sig_flt_2nd))
                        self.gains_2nd.append(gain)
                    self.sig_flt_2nd = []
                else:
                    content = line.rstrip().split("\t")
                    self.sig_flt_1st.append(float(content[0]))
                    self.sig_flt_2nd.append(float(content[1]))
            gain = max(self.sig_flt_1st)
            self.gains_1st.append(20*math.log10(gain))
            gain = max(self.sig_flt_2nd)
            self.gains_2nd.append(20*math.log10(gain))

        self.freq = np.array(self.freq)
        self.gains_1st = np.array(self.gains_1st)
        self.gains_2nd = np.array(self.gains_2nd)


    def plot_freq_response(self):
        plt.plot(self.freq, self.gains_1st, label="1st order")
        plt.plot(self.freq, self.gains_2nd, label="2nd order")
        plt.xlabel("frequency")
        plt.ylabel("gain")
        plt.title("frequency response of butterworth low pass filters")
        plt.legend()
        plt.grid()
        plt.show()

if __name__ == "__main__":
    bwLowPassFltAnalysis = bwLowPassFltAnalyzor(200, 20000)
    bwLowPassFltAnalysis.load_freq_response()
    bwLowPassFltAnalysis.plot_freq_response()


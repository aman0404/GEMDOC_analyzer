# GEMDOC Analyzer
## This requires only root and can be run either offline/locally or in CMSSW

```
cmsrel CMSSW_11_2_0
cd CMSSW_11_2_0/src
git clone https://github.com/aman0404/GEMDOC_analyzer.git
cd Analyzer
sh compile_script.sh
```

This will produce OfflineMain.exe executable file. To run the executable to get the required plots:

```
./OfflineMain.exe input.root output.root
or
./OfflineMain.exe input_file_list.txt output.root
```

This will generate required histograms defined in gem_analysis.C.

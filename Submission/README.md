#Script to submit condor jobs at lxplus
# This script will submit condor jobs for all the files listed in 'files.txt'

Change path name for your OfflineMain.C code in  submit_script.sh

```
git clone https://github.com/aman0404/GEMDOC_analyzer.git
cd Submission
cmsenv
mkdir log
source submit_script.sh files
```

You can track the status of the jobs using command 'condor_q username' and see the output/error in log directory

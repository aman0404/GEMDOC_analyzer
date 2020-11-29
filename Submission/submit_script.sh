#!/bin/bash
FNAME=$1
cat > Job_${FNAME}_bash.sh <<EOF
#!/bin/bash
cd /afs/cern.ch/work/a/amkaur/gem_doc_Analysis/CMSSW_11_1_2_patch2/src/OfflineAnalyzer
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval \`scramv1 runtime -sh\`
./OfflineMain.exe ${FNAME}.txt out_${FNAME}.root
EOF
chmod +x Job_${FNAME}_bash.sh


cat>condor_${FNAME}<<EOF
Universe = vanilla
Executable = /afs/cern.ch/work/a/amkaur/gem_doc_Analysis/CMSSW_11_1_2_patch2/src/OfflineAnalyzer/Job_${FNAME}_bash.sh
Error = log/job.err.\$(Cluster)_${FNAME}
Output = log/job.out.\$(Cluster)_${FNAME}
Log = log/job.log.\$(Cluster)_${FNAME}
+JobFlavour = "longlunch"
Queue 1

EOF

condor_submit condor_${FNAME}

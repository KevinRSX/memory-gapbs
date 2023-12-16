#!/usr/bin/python3
import sys
import os
import subprocess

usage = "python3 per_process_huge.py <pid>"
if len(sys.argv) != 2:
    print(usage)
    exit(1)

pid = sys.argv[1]
huge = 0
with open(os.path.join("/proc", pid, "smaps"), 'r') as f:
    rows = f.readlines()
    for r in rows:
        rlist = r.split(' ')
        if rlist[0] == "AnonHugePages:":
            huge += float(rlist[-2])

total_out = subprocess.check_output("numastat -p " + pid, \
        shell=True).decode("utf-8").split('\n')
total = total_out[9]
total = total.split(' ')
total = float(list(filter(None, total))[1])

print("Total: ", total / 1024) # Total is in MB
print("AnonHugePages: ", huge / 1024 / 1024) # AnonHugePages is in KB

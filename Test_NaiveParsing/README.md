## Test_NaiveParsing
This speedtest project directory contains a naive parser for [FakeAnaData](../workdir/proto/fake_anadata.proto),  
&nbsp; which sums up the number of `FakeAnaData.history` entries and profiles the `box.cost`.

### C++
```
#in container
root@X:/work-dir# scripts/build_cppclasses.sh
...
root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_cppnaiveparsing.sh
...
processing /data/fakedata_7.txt.gz......
processing /data/fakedata_8.txt.gz......
processing /data/fakedata_9.txt.gz......
bin_10log10 21:1025
bin_10log10 22:29815914
bin_10log10 23:32227653
bin_10log10 24:14
bin_10log10 nboxes:20664138
bin_10log10 nevents:1070435
...
```
```
real    2m9.062s  |  real    2m8.139s  |  real    2m8.643s
user    2m0.602s  |  user    2m0.959s  |  user    2m1.563s
sys     0m7.923s  |  sys     0m7.170s  |  sys     0m7.070s
```

### python
```
#in container
root@X:/work-dir# scripts/build_pyclasses.sh

root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_pynaiveparsing.sh
...
processing /data/fakedata_4.txt.gz...
processing /data/fakedata_2.txt.gz...
defaultdict(<class 'int'>, {'nevents': 1070435, 'nboxes': 20664138, 22: 29815914, 23: 32227653, 21: 1025, 24: 14})
...
```
```
real    17m31.188s
user    17m29.464s
sys     0m1.540s
```

### C#
```
#in container
root@X:/work-dir# scripts/build_csharpclasses.sh

root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_csharpnaiveparsing.sh
...
Processing /data/fakedata_4.txt.gz...
Processing /data/fakedata_2.txt.gz...
nevents:1070435
nboxes:20664138
22:29815914
23:32227653
21:1025
24:14
```
```
real    1m12.829s  |  real    1m12.028s  |  real    1m12.613s
user    1m8.627s   |  user    1m7.853s   |  user    1m8.638s
sys     0m4.270s   |  sys     0m4.238s   |  sys     0m4.035s
```


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
bin_10log10 21:971
bin_10log10 22:29856462
bin_10log10 23:32247244
bin_10log10 24:4
bin_10log10 nboxes:20692964
bin_10log10 nevents:1071943
...
```
```
real    2m51.222s  |  real      2m53.494s  |  real      2m54.885s
user    2m43.434s  |  user      2m45.929s  |  user      2m46.773s
sys     0m7.581s   |  sys       0m7.345s   |  sys       0m7.847s
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
defaultdict(<class 'int'>, {'nevents': 1071943, 'nboxes': 5, 23: 32247244, 22: 29856462, 21: 971, 24: 4})
...
```
```
real    1m58.856s  |  real      1m56.101s  |  real      1m56.221s
user    1m56.353s  |  user      1m53.510s  |  user      1m53.703s
sys     0m2.281s   |  sys       0m2.437s   |  sys       0m2.394s
```

### note
Even when testing with a base64 decoded binary as a std::string,  
&nbsp; the `cppobj.ParseFromString` method is qualitative slower than `pyobj.FromString` in 100K and 1M loops,  
&nbsp; based on my environment's build versions.

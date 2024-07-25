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
bin_10log10 21:965
bin_10log10 22:29807019
bin_10log10 23:32227323
bin_10log10 24:16
bin_10log10 nboxes:20665497
bin_10log10 nevents:1071875
...
```
```
real    2m56.238s  |  real      2m49.779s  |  real      2m51.916s
user    2m48.565s  |  user      2m42.142s  |  user      2m43.691s
sys     0m7.626s   |  sys       0m7.625s   |  sys       0m8.112s
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
defaultdict(<class 'int'>, {'nevents': 1071875, 'nboxes': 20665497, 23: 32227323, 22: 29807019, 21: 965, 24: 16})
...
```
```
real    1m58.262s  |  real      1m59.002s  |  real      1m58.881s
user    1m55.947s  |  user      1m56.696s  |  user      1m56.712s
sys     0m2.140s   |  sys       0m2.267s   |  sys       0m2.152s
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
nevents:1071875
nboxes:20665497
23:32227323
22:29807019
21:965
24:16
```
```
real    1m16.641s  |  real      1m14.507s  |  real      1m15.440s
user    1m12.323s  |  user      1m10.162s  |  user      1m11.382s
sys     0m4.273s   |  sys       0m4.428s   |  sys       0m4.001s
```

### note
Even when testing with a base64 decoded binary as a std::string,  
&nbsp; the `cppobj.ParseFromString` method is qualitative slower than `pyobj.FromString` in 100K and 1M loops,  
&nbsp; based on my environment's build versions.

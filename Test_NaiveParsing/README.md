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
real    2m48.907s  |  real      2m48.584s  |  real      2m48.328s
user    2m41.533s  |  user      2m41.191s  |  user      2m40.831s
sys     0m7.352s   |  sys       0m7.383s   |  sys       0m7.446s
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
real    1m57.521s  |  real      1m56.101s  |  real      1m55.019s
user    1m54.797s  |  user      1m53.420s  |  user      1m52.392s
sys     0m2.676s   |  sys       0m2.648s   |  sys       0m2.620s
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
real    1m13.091s  |  real      1m12.970s  |  real      1m12.219s
user    1m9.034s   |  user      1m8.809s   |  user      1m8.390s
sys     0m4.084s   |  sys       0m4.208s   |  sys       0m3.884s
```

* reference : dotnets command to initialize solutions/projects  
  [scripts/init_csharpenv.sh](scripts/init_csharpenv.sh) , [learn.microsoft.com](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-new) 

### note
Even when testing with a base64 decoded binary as a std::string,  
&nbsp; the `cppobj.ParseFromString` method is qualitative slower than `pyobj.FromString` in 100K and 1M loops,  
&nbsp; based on my environment's build versions.

After speedtest with protobuf v20.2, performace is improved arround 30% in old version. [branch test/v20.2](https://github.com/chiyi/speedtest_protobuf/tree/test/v20.2/Test_NaiveParsing)  
&nbsp; It's implied the depencies/versions have to be tunned further when building C++ environments/codes.

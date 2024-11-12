## Test_NaiveParsing
This speedtest project directory contains a naive parser for [FakeAnaData](../workdir/proto/fake_anadata.proto),  
&nbsp; which sums up the number of `FakeAnaData.history` entries and profiles the `box.cost`.

### C++
```
#in container
root@X:/work-dir# scripts/build_cppclasses.sh
Print fake data
(...)
root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_cppnaiveparsing.sh
building...
testing...
(...)
bin_10log10 24:5
bin_10log10 nboxes:20689735
bin_10log10 nevents:1072981
(...) log in test_cpp_naiveparsing.log
```
```
real    1m44.373s  |  real    1m44.048s  |  real    1m44.007s
user    1m43.551s  |  user    1m43.197s  |  user    1m43.229s
sys     0m0.814s   |  sys     0m0.844s   |  sys     0m0.773s
```

### python
```
#in container
root@X:/work-dir# scripts/build_pyclasses.sh

root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_pynaiveparsing.sh
/work-dir/src/src_py/proto_class:/opt/root/lib:
testing...
processing /data/fakedata_4.txt.gz...
processing /data/fakedata_2.txt.gz...
defaultdict(<class 'int'>, {'nevents': 1072981, 'nboxes': 20689735, 23: 32257554, 22: 29901867, 21: 929, 24: 5})
(...) log in test_py_naiveparsing.log
```
```
real    1m56.637s  |  real    1m56.675s  |  real    1m58.888s
user    1m53.900s  |  user    1m53.815s  |  user    1m55.834s
sys     0m2.728s   |  sys     0m2.851s   |  sys     0m3.045s
```

### C#
```
#in container
root@X:/work-dir# scripts/build_csharpclasses.sh
(...)
MSBuild version 17.8.5+b5265ef37 for .NET
  Determining projects to restore...
  All projects are up-to-date for restore.
  proto_class -> /work-dir/src/src_csharp_sln/proto_class/bin/Release/net8.0/linux-x64/proto_class.dll
  proto_class -> /work-dir/src/src_csharp_sln/proto_class/bin/Release/net8.0/linux-x64/publish/


root@X:/work-dir# cd Test_NaiveParsing
root@X:/work-dir/Test_NaiveParsing# scripts/test_csharpnaiveparsing.sh
building...
Project already has a reference to `..\..\..\..\src\src_csharp_sln\proto_class\proto_class.csproj`.
MSBuild version 17.8.5+b5265ef37 for .NET
(...)
built_file = bin/Release/net8.0/linux-x64/publish/Test_NaiveParsing
testing...
22:29901867
21:929
24:5
(...) log in test_csharp_naiveparsing.log . compare logs
```
```
real    1m16.579s  |  real    1m16.940s  |  real    1m16.733s
user    1m12.648s  |  user    1m12.748s  |  user    1m12.027s
sys     0m4.003s   |  sys     0m4.267s   |  sys     0m4.779s
```

* reference : dotnets command to initialize solutions/projects  
  [scripts/init_csharpenv.sh](scripts/init_csharpenv.sh) , [learn.microsoft.com](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-new) 

### note
Even when testing with a base64 decoded binary as a std::string,
&nbsp; the performance of `cppobj.ParseFromString` is roughly equivalent to `pyobj.FromString` for both 100K and 1M loops,
&nbsp; based on my current environment's build versions.

In the older version, protobuf v20.2, performance was already satisfactory without additional performance-enhancing implementations like TurboBase64 or any specific tuning.[branch test/v20.2](https://github.com/chiyi/speedtest_protobuf/tree/test/v20.2/Test_NaiveParsing). 
&nbsp; However, tuning of the dependencies and versions is still required for building C++ environments/codes to potentially achieve better results.

## Test_SimAnaTable
This speedtest project directory contains a simulation that generates an analysis table at runtime.  
&nbsp; The table is based on the specific field [hashed_name](../workdir/proto/fake_anadata.proto). 

### C++
```
#in container
root@X:/work-dir# scripts/build_cppclasses.sh
(...)
root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_SimAnaTable# scripts/test_cppsimanatable.sh
building...
testing...
processing /data/fakedata_7.txt.gz......
processing /data/fakedata_8.txt.gz......
processing /data/fakedata_9.txt.gz......
(...) log in test_cpp_simanatable.log 
```
```
real    1m46.899s  |  real    1m46.721s  |  real    1m46.822s
user    1m46.005s  |  user    1m45.836s  |  user    1m45.968s
sys     0m0.870s   |  sys     0m0.860s   |  sys     0m0.830s
```

### python
```
#in container
root@X:/work-dir# scripts/build_pyclasses.sh
(...)
root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_SimAnaTable# scripts/test_pysimanatable.sh
/work-dir/src/src_py/proto_class:/opt/root/lib:
testing...
(...) log in test_pysimanatable.log
```
```
real    1m50.238s  |  real    1m49.799s  |  real    1m49.971s
user    1m48.572s  |  user    1m48.066s  |  user    1m48.274s
sys     0m1.612s   |  sys     0m1.710s   |  sys     0m1.673s
```

### C#
```
#in container
root@X:/work-dir# scripts/build_csharpclasses.sh
(...)
root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_NaiveParsing# scripts/test_csharpsimanatable.sh
building...
Project already has a reference to `..\..\..\..\src\src_csharp_sln\proto_class\proto_class.csproj`.
MSBuild version 17.8.5+b5265ef37 for .NET
(...)
built_file = bin/Release/net8.0/linux-x64/publish/Test_SimAnaTable
testing...
(...) log in test_csharpsimanatable.log . comparing logs
```
```
real    1m18.654s  |  real    1m17.949s  |  real    1m18.081s
user    1m14.233s  |  user    1m13.515s  |  user    1m13.868s
sys     0m4.545s   |  sys     0m4.579s   |  sys     0m4.360s
```

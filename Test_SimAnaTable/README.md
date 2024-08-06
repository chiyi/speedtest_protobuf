## Test_SimAnaTable
This speedtest project directory contains a simulation that generates an analysis table at runtime.  
&nbsp; The table is based on the specific field [hashed_name](../workdir/proto/fake_anadata.proto). 

### C++
```
#in container
root@X:/work-dir# scripts/build_cppclasses.sh
...
root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_SimAnaTable# scripts/test_cppsimanatable.sh
...
processing /data/fakedata_7.txt.gz......
processing /data/fakedata_8.txt.gz......
processing /data/fakedata_9.txt.gz......
...
```
```
real    2m14.763s  |  real    2m14.590s  |  real    2m14.539s
user    2m7.533s   |  user    2m7.301s   |  user    2m7.413s
sys     0m7.212s   |  sys     0m7.273s   |  sys     0m7.109s
```

### python
```
#in container
root@X:/work-dir# scripts/build_pyclasses.sh

root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_SimAnaTable# scripts/test_pysimanatable.sh
...
```
```
real    18m28.153s
user    18m26.247s
sys     0m1.444s
```

### C#
```
#in container
root@X:/work-dir# scripts/build_csharpclasses.sh

root@X:/work-dir# cd Test_SimAnaTable
root@X:/work-dir/Test_NaiveParsing# scripts/test_csharpsimanatable.sh
building...
Project already has a reference to `..\..\..\..\src\src_csharp_sln\proto_class\proto_class.csproj`.
MSBuild version 17.8.5+b5265ef37 for .NET
  Determining projects to restore...
...
```
```
real    1m14.605s  |  real    1m14.209s  |  real    1m13.157s
user    1m10.352s  |  user    1m10.586s  |  user    1m9.376s
sys     0m4.283s   |  sys     0m3.691s   |  sys     0m3.903s
```

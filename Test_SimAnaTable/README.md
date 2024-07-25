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
real    2m50.632s  |  real      2m48.988s  |  real      2m49.377s
user    2m43.090s  |  user      2m41.458s  |  user      2m41.954s
sys     0m7.486s   |  sys       0m7.488s   |  sys       0m7.412s
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
real    1m47.451s  |  real      1m46.695s  |  real      1m47.266s
user    1m46.308s  |  user      1m45.620s  |  user      1m46.240s
sys     0m1.108s   |  sys       0m1.064s   |  sys       0m1.004s
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
real    1m14.867s  |  real      1m13.765s  |  real      1m14.935s
user    1m10.534s  |  user      1m9.899s   |  user      1m10.940s
sys     0m4.411s   |  sys       0m3.979s   |  sys       0m4.129s
```

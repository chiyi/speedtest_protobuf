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
real    2m51.307s  |  real      2m51.789s  |  real      2m51.225s
user    2m43.481s  |  user      2m43.703s  |  user      2m43.310s
sys     0m7.808s   |  sys       0m7.879s   |  sys       0m7.886s
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
real    1m48.339s  |  real      1m48.527s  |  real      1m47.049s
user    1m47.259s  |  user      1m47.534s  |  user      1m45.970s
sys     0m0.984s   |  sys       0m0.976s   |  sys       0m1.060s
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
real    1m15.118s  |  real      1m15.667s  |  real      1m15.566s
user    1m10.416s  |  user      1m11.573s  |  user      1m11.047s
sys     0m4.737s   |  sys       0m4.281s   |  sys       0m4.604s
```

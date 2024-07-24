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
real    2m50.308s  |  real      2m48.850s  |  real      2m52.878s
user    2m42.096s  |  user      2m41.923s  |  user      2m45.384s
sys     0m7.721s   |  sys       0m6.912s   |  sys       0m7.439s
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
real    1m48.380s  |  real      1m47.933s  |  real      1m48.111s
user    1m47.015s  |  user      1m46.367s  |  user      1m46.497s
sys     0m1.352s   |  sys       0m1.492s   |  sys       0m1.576s
```

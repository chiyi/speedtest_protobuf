# speedtest_protobuf
This is a containerized environment for running speedtest to evaluate the performance of protobuf deserialization across different package versions.

* Build image from [PrepareImage](PrepareImage)
* [project:CreateFakeData](CreateFakeData) generates a fake dataset for this repository using the specified [proto-files](workdir/proto)

## speedtest
* [Test_NaiveParsing](Test_NaiveParsing) : naively parsing and sum up
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m48.907s` | `real    2m48.584s` | `real    2m48.328s` |
  |                | `user    2m41.533s` | `user    2m41.191s` | `user    2m40.831s` |
  |                | `sys     0m 7.352s` | `sys     0m 7.383s` | `sys     0m 7.446s` |
  | python classes | `real    1m57.521s` | `real    1m56.101s` | `real    1m55.019s` |
  |                | `user    1m54.797s` | `user    1m53.420s` | `user    1m52.392s` |
  |                | `sys     0m 2.676s` | `sys     0m 2.648s` | `sys     0m 2.620s` |
  | C# classes     | `real    1m13.091s` | `real    1m12.970s` | `real    1m12.219s` |
  |                | `user    1m 9.034s` | `user    1m 8.809s` | `user    1m 8.390s` |
  |                | `sys     0m 4.084s` | `sys     0m 4.208s` | `sys     0m 3.884s` |


  
* [Test_SimAnaTable](Test_SimAnaTable) : complicated scanning as the simulation
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m50.632s` | `real    2m48.988s` | `real    2m49.377s` |
  |                | `user    2m43.090s` | `user    2m41.458s` | `user    2m41.954s` |
  |                | `sys     0m 7.486s` | `sys     0m 7.488s` | `sys     0m 7.412s` |
  | python classes | `real    1m47.451s` | `real    1m46.695s` | `real    1m47.266s` |
  |                | `user    1m46.308s` | `user    1m45.620s` | `user    1m46.240s` |
  |                | `sys     0m 1.108s` | `sys     0m 1.064s` | `sys     0m 1.004s` |
  | C# classes     | `real    1m14.867s` | `real    1m13.765s` | `real    1m14.935s` |
  |                | `user    1m10.534s` | `user    1m 9.899s` | `user    1m10.940s` |
  |                | `sys     0m 4.411s` | `sys     0m 3.979s` | `sys     0m 4.129s` |

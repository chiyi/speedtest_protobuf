# speedtest_protobuf
This is a containerized environment for running speedtest to evaluate the performance of protobuf deserialization across different package versions.

* Build image from [PrepareImage](PrepareImage)
* [project:CreateFakeData](CreateFakeData) generates a fake dataset for this repository using the specified [proto-files](workdir/proto)

## speedtest
* [Test_NaiveParsing](Test_NaiveParsing) : naively parsing and sum up
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m51.222s` | `real    2m53.494s` | `real    2m54.885s` |
  |                | `user    2m43.434s` | `user    2m45.929s` | `user    2m46.773s` |
  |                | `sys     0m 7.581s` | `sys     0m 7.345s` | `sys     0m 7.847s` |
  | python classes | `real    1m58.856s` | `real    1m56.101s` | `real    1m56.221s` |
  |                | `user    1m56.353s` | `user    1m53.510s` | `user    1m53.703s` |
  |                | `sys     0m 2.281s` | `sys     0m 2.437s` | `sys     0m 2.394s` | 
  
* [Test_SimAnaTable](Test_SimAnaTable) : complicated scanning as the simulation
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m50.308s` | `real    2m48.850s` | `real    2m52.878s` |
  |                | `user    2m42.096s` | `user    2m41.923s` | `user    2m45.384s` |
  |                | `sys     0m 7.721s` | `sys     0m 6.912s` | `sys     0m 7.439s` |
  | python classes | `real    1m48.380s` | `real    1m47.933s` | `real    1m48.111s` |
  |                | `user    1m47.015s` | `user    1m46.367s` | `user    1m46.497s` |
  |                | `sys     0m 1.352s` | `sys     0m 1.492s` | `sys     0m 1.576s` |

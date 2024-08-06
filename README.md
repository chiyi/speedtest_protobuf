# speedtest_protobuf
This is a containerized environment for running speedtest to evaluate the performance of protobuf deserialization across different package versions.

* Build image from [PrepareImage](PrepareImage)
* [project:CreateFakeData](CreateFakeData) generates a fake dataset for this repository using the specified [proto-files](workdir/proto)

## speedtest
* [Test_NaiveParsing](Test_NaiveParsing) : naively parsing and sum up
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m 9.062s` | `real    2m 8.139s` | `real    2m 8.643s` |
  |                | `user    2m 0.602s` | `user    2m 0.959s` | `user    2m 1.563s` |
  |                | `sys     0m 7.923s` | `sys     0m 7.170s` | `sys     0m 7.070s` |
  | python classes | `real   17m31.188s` |  |  |
  |                | `user   17m29.464s` |  |  |
  |                | `sys     0m 1.540s` |  |  |
  | C# classes     | `real    1m12.829s` | `real    1m12.028s` | `real    1m12.613s` |
  |                | `user    1m 8.627s` | `user    1m 7.853s` | `user    1m 8.638s` |
  |                | `sys     0m 4.270s` | `sys     0m 4.238s` | `sys     0m 4.035s` |



* [Test_SimAnaTable](Test_SimAnaTable) : complicated scanning as the simulation
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    2m14.763s` | `real    2m14.590s` | `real    2m14.539s` |
  |                | `user    2m 7.533s` | `user    2m 7.301s` | `user    2m 7.413s` |
  |                | `sys     0m 7.212s` | `sys     0m 7.273s` | `sys     0m 7.109s` |
  | python classes | `real   18m28.153s` |  |  |
  |                | `user   18m26.247s` |  |  |
  |                | `sys     0m 1.444s` |  |  |
  | C# classes     | `real    1m14.605s` | `real    1m14.209s` | `real    1m13.157s` |
  |                | `user    1m10.352s` | `user    1m10.586s` | `user    1m 9.376s` |
  |                | `sys     0m 4.283s` | `sys     0m 3.691s` | `sys     0m 3.903s` |

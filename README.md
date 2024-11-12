# speedtest_protobuf
This is a containerized environment for running speedtest to evaluate the performance of protobuf deserialization across different package versions.

* Build image from [PrepareImage](PrepareImage)
  * testing on [protobuf v28.3](https://github.com/protocolbuffers/protobuf/tree/v28.3)
* [project:CreateFakeData](CreateFakeData) generates a fake dataset for this repository using the specified [proto-files](workdir/proto)

## speedtest
* [Test_NaiveParsing](Test_NaiveParsing) : naively parsing and sum up
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    1m44.373s` | `real    1m44.048s` | `real    1m44.007s` |
  |                | `user    1m43.551s` | `user    1m43.197s` | `user    1m43.229s` |
  |                | `sys     0m 0.814s` | `sys     0m 0.844s` | `sys     0m 0.773s` |
  | python classes | `real    1m56.637s` | `real    1m56.675s` | `real    1m58.888s` |
  |                | `user    1m53.900s` | `user    1m53.815s` | `user    1m55.834s` |
  |                | `sys     0m 2.728s` | `sys     0m 2.851s` | `sys     0m 3.045s` |
  | C# classes     | `real    1m16.579s` | `real    1m16.940s` | `real    1m16.733s` |
  |                | `user    1m12.648s` | `user    1m12.748s` | `user    1m12.027s` |
  |                | `sys     0m 4.003s` | `sys     0m 4.267s` | `sys     0m 4.779s` |


  
* [Test_SimAnaTable](Test_SimAnaTable) : complicated scanning as the simulation
  | class language |         1st         |         2nd         |         3rd         |
  |:--------------:|:-------------------:|:-------------------:|:-------------------:|
  | C++ classes    | `real    1m46.899s` | `real    1m46.721s` | `real    1m46.822s` |
  |                | `user    1m46.005s` | `user    1m45.836s` | `user    1m45.968s` |
  |                | `sys     0m 0.870s` | `sys     0m 0.860s` | `sys     0m 0.830s` |
  | python classes | `real    1m50.238s` | `real    1m49.799s` | `real    1m49.971s` |
  |                | `user    1m48.572s` | `user    1m48.066s` | `user    1m48.274s` |
  |                | `sys     0m 1.612s` | `sys     0m 1.710s` | `sys     0m 1.673s` |
  | C# classes     | `real    1m18.654s` | `real    1m17.949s` | `real    1m18.081s` |
  |                | `user    1m14.233s` | `user    1m13.515s` | `user    1m13.868s` |
  |                | `sys     0m 4.545s` | `sys     0m 4.579s` | `sys     0m 4.360s` |

## speed
* After speedtest, the performance of protobuf_v28.3 C++ parsing with some performance tuning is now roughly equivalent to protobuf_v20.2 C++ in this environment.
  * For more details on settings for protobuf_v20.2, see the branch[[test/v20.2](https://github.com/chiyi/speedtest_protobuf/tree/test/v20.2)].
* Python classes without C++ implementation are significantly slower in protobuf_v20.2.
  * about 9 times elapsed time [speedtest on protobuf v20.2](https://github.com/chiyi/speedtest_protobuf/blob/test/v20.2/README.md)

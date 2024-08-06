## CreateFakeData

### Build proto-files
(after building the image from [PrepareImage](../PrepareImage))
```
./run_container.sh

#in container
root@X:/work-dir# scripts/build_cppclasses.sh
  
Print fake data
AAA
BlueE
BlueE
16829
fake ana data
1721401251
0.997
```

### Create my fake dataset (same data generated with protobuf v27.2)
```
root@X:/work-dir# cd CreateFakeData
root@X:/work-dir/CreateFakeData# scripts/build_faker.sh
Naive checks
JobsHandler.h
job.h job.cpp
job_fakedata.h job_fakedata.cpp
jobs_scheduler.h jobs_scheduler.cpp
Build

root@X:/work-dir/CreateFakeData# time ./create_fakedata 100000 /data/fakedata 10000 5
Generating 100000 records of fake data with 10 partitions, where each partition has 10000 records, except for the tail partition (0 records)
[Thu Jul 25 14:52:59 2024]: Waiting for another complete jobs before adding, NJobs_running=5
...
[Thu Jul 25 14:55:01 2024]: NJobs_running=5
[Thu Jul 25 14:55:02 2024]: NJobs_running=4
[Thu Jul 25 14:55:03 2024]: NJobs_running=3
[Thu Jul 25 14:55:03 2024]: NJobs_running=2
[Thu Jul 25 14:55:03 2024]: NJobs_running=1

real	2m5.211s
user	9m28.609s
sys	0m31.838s
```

### Test reading
```
root@X:/work-dir# ls -hl /data/fakedata_*.gz
-rw-r--r-- 1 root root 434M Jul 25 14:53 /data/fakedata_1.txt.gz
-rw-r--r-- 1 root root 434M Jul 25 14:55 /data/fakedata_10.txt.gz
-rw-r--r-- 1 root root 431M Jul 25 14:53 /data/fakedata_2.txt.gz
-rw-r--r-- 1 root root 431M Jul 25 14:53 /data/fakedata_3.txt.gz
-rw-r--r-- 1 root root 431M Jul 25 14:53 /data/fakedata_4.txt.gz
-rw-r--r-- 1 root root 431M Jul 25 14:53 /data/fakedata_5.txt.gz
-rw-r--r-- 1 root root 431M Jul 25 14:54 /data/fakedata_6.txt.gz
-rw-r--r-- 1 root root 433M Jul 25 14:55 /data/fakedata_7.txt.gz
-rw-r--r-- 1 root root 433M Jul 25 14:55 /data/fakedata_8.txt.gz
-rw-r--r-- 1 root root 429M Jul 25 14:54 /data/fakedata_9.txt.gz

root@X:/work-dir/CreateFakeData# scripts/test_readfile.sh
processing /data/fakedata_1.txt.gz......
... (json strings) ...
     {
      "id": "UCardW_102",
      "name": "W 66",
      "cat": "ZTZ",
      "count": 3,
      "value_1": 3045,
      "value_2": 4175,
      "value_3": 7
     }
    ],
    "score": 0.953897968275327,
    "target": "A",
    "version": "0.0.0",
    "id_1": "id1_18",
    "id_2": "id2_3C",
    "id_3": "id3_8"
   },
   "score": 0.953897968275327
  }
 ]
}

} //record end
```

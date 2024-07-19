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

### Create my fake dataset
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
[Fri Jul 19 16:26:32 2024]: Waiting for another complete jobs before adding, NJobs_running=5
...
writing /data/fakedata_7.txt.gz...
writing /data/fakedata_8.txt.gz...
writing /data/fakedata_6.txt.gz...
writing /data/fakedata_10.txt.gz...
writing /data/fakedata_9.txt.gz...
[Fri Jul 19 16:28:46 2024]: NJobs_running=5
[Fri Jul 19 16:28:46 2024]: NJobs_running=4
[Fri Jul 19 16:28:46 2024]: NJobs_running=3
[Fri Jul 19 16:28:46 2024]: NJobs_running=2
[Fri Jul 19 16:28:46 2024]: NJobs_running=1

real    2m14.763s
user    10m30.420s
sys     0m28.696s

```

### Test reading
```
root@X:/work-dir# ls -hl /data/fakedata_*.gz
-rw-r--r-- 1 root root 432M Jul 19 16:27 /data/fakedata_1.txt.gz
-rw-r--r-- 1 root root 432M Jul 19 16:28 /data/fakedata_10.txt.gz
-rw-r--r-- 1 root root 433M Jul 19 16:27 /data/fakedata_2.txt.gz
-rw-r--r-- 1 root root 434M Jul 19 16:27 /data/fakedata_3.txt.gz
-rw-r--r-- 1 root root 435M Jul 19 16:27 /data/fakedata_4.txt.gz
-rw-r--r-- 1 root root 430M Jul 19 16:27 /data/fakedata_5.txt.gz
-rw-r--r-- 1 root root 434M Jul 19 16:28 /data/fakedata_6.txt.gz
-rw-r--r-- 1 root root 428M Jul 19 16:28 /data/fakedata_7.txt.gz
-rw-r--r-- 1 root root 431M Jul 19 16:28 /data/fakedata_8.txt.gz
-rw-r--r-- 1 root root 434M Jul 19 16:28 /data/fakedata_9.txt.gz

root@X:/work-dir/CreateFakeData# scripts/test_readfile.sh
processing /data/fakedata_1.txt.gz......
... (json strings) ...
     "boxes": [ 
    {
     "color": "Orange",
     "cost": 193.71608195074623,
     "count": 2 
    },
    {
     "color": "Pink",
     "cost": 197.94886069359026,
     "count": 1 
    }
   ]
  }
 ]
}

} //record end

```

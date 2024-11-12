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
JobsHandler.cpp
job.cpp
(...)
job_fakedata.cpp
Build

root@X:/work-dir/CreateFakeData# time ./create_fakedata 100000 /data/fakedata 10000 5
Generating 100000 records of fake data with 10 partitions, where each partition has 10000 records, except for the tail partition (0 records)
[Tue Nov 12 05:39:51 2024]: Waiting for another complete jobs before adding, NJobs_running=5
(...)
writing /data/fakedata_6.txt.gz...
writing /data/fakedata_10.txt.gz...
writing /data/fakedata_8.txt.gz...
writing /data/fakedata_7.txt.gz...
writing /data/fakedata_9.txt.gz...
[Tue Nov 12 05:41:49 2024]: NJobs_running=5
[Tue Nov 12 05:41:50 2024]: NJobs_running=4
[Tue Nov 12 05:41:50 2024]: NJobs_running=3
[Tue Nov 12 05:41:50 2024]: NJobs_running=2
[Tue Nov 12 05:41:50 2024]: NJobs_running=1

real	1m58.604s
user	9m0.409s
sys	0m32.309s
```

### Test reading
```
root@X:/work-dir# ls -hl /data/fakedata_*.gz
-rw-r--r-- 1 ubuntu ubuntu 433M Nov 12 05:40 /data/fakedata_1.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 431M Nov 12 05:41 /data/fakedata_10.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 436M Nov 12 05:40 /data/fakedata_2.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 434M Nov 12 05:40 /data/fakedata_3.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 432M Nov 12 05:40 /data/fakedata_4.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 434M Nov 12 05:40 /data/fakedata_5.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 435M Nov 12 05:41 /data/fakedata_6.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 434M Nov 12 05:41 /data/fakedata_7.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 434M Nov 12 05:41 /data/fakedata_8.txt.gz
-rw-r--r-- 1 ubuntu ubuntu 431M Nov 12 05:41 /data/fakedata_9.txt.gz

root@X:/work-dir/CreateFakeData# scripts/test_readfile.sh
processing /data/fakedata_1.txt.gz......
... (json strings) ...
    {
     "color": "Orange",
     "cost": 187.08762040361762,
     "count": 1
    },
    {
     "color": "Black",
     "cost": 201.43207507613297,
     "count": 2 
    }
   ] 
  } 
 ]  
}    
     
} //record end
```

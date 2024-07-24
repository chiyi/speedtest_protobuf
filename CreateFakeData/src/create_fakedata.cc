#include <iostream>

#include "TSystem.h"
#include "TROOT.h"
#include "TString.h"
#include "TRandom3.h"

// user-defined functions
#define b_DEBUG 3
bool chk_para(int argc, char *argv[]);
void protection(int &nrows_part, int &nthreads);
void usage();
#include "job.h"
#include "job.cpp"
#include "job_fakedata.h"
#include "job_fakedata.cpp"
#include "jobs_scheduler.h"
#include "jobs_scheduler.cpp"


int main(int argc, char *argv[])
{
 int nrows=0, nrows_part=0, nrows_tail=0, nparts=0, nthreads=1;
 TRandom3 rndm;
 Job_fakedata::Settings_fakedata settings;
 JobsScheduler<Job_fakedata> *scheduler;


 if(!chk_para(argc, argv))
 {
  usage();
  return 2;
 }

 //ROOT::EnableImplicitMT(nthreads); // Enable multi-threading
 ROOT::EnableImplicitMT(); // Enable multi-threading
 ROOT::EnableThreadSafety();

 rndm.SetSeed(13931);
 nrows = TString(argv[1]).Atoi();
 nrows_part = TString(argv[3]).Atoi();
 nthreads = TString(argv[4]).Atoi();
 nrows_tail = nrows % nrows_part;
 nparts = nrows / nrows_part + (nrows_tail > 0) * 1;

 std::cout << "Generating " << nrows << " records of fake data ";
 std::cout << "with " << nparts << " partitions, where each partition has " << nrows_part << " records, except for the tail partition (" << nrows_tail << " records)" << std::endl;

 settings.nparts = nparts;
 settings.nrows_part = nrows_part;
 settings.nrows_tail = nrows_tail;
 settings.out_prefix = argv[2];

 scheduler = new JobsScheduler<Job_fakedata>(nparts, nthreads, &rndm, Job_fakedata(0, &rndm, settings));
 scheduler->run_jobs();

 return 0;
}


bool chk_para(int argc, char *argv[])
{
 const int min_args=5, max_nrows=1000, max_threads=1;
 int nrows=0, nrows_part=0, nthreads=1;
 TString outdir;

 if(argc<min_args)
  return false;

 nrows = TString(argv[1]).Atoi();
 if(nrows<=0)
 {
  std::cout << "nrows=" << nrows << " <= 0\n";
  return false;
 }
 
 outdir = gSystem->GetDirName(argv[2]);
 if(gSystem->AccessPathName(outdir))
 {
  std::cout << "Invalid output directory " << outdir << ".\n";
  return false;
 }

 nrows_part = TString(argv[3]).Atoi();
 if(nrows_part<=0)
 {
  std::cout << "nrows_part=" << nrows_part << " <= 0\n";
  return false;
 }

 nthreads = TString(argv[4]).Atoi();
 if(nthreads<=0)
 {
  std::cout << "nthreads=" << nthreads << " <= 0\n";
  return false;
 }

 //REMOVE or COMMENT-OUT THIS ACTION FOR SPEED WHEN HAVING CAPABLE MEMORY
 protection(nrows_part, nthreads);

 return true;
}

void usage()
{
 std::cout << "usage(): ./create_fakedata 10 /data/fakedata 1 7\n";
 std::cout << "./create_fakedata {number of records} {output filename prefix} {number of records per partition} {maximum working threads for creation}" << std::endl;
}

void protection(int &nrows_part, int &nthreads)
{
 const int max_nrows = 1000;
 const int max_nthreads = 1;
 TString warn = "Consider removing this protection in the code if you're already monitoring memory usage for larger cases.";

 if(nrows_part > max_nrows)
 {
  std::cout << "nrows_part=" << nrows_part << " > " << max_nrows << ". \n" << warn << std::endl;
  nrows_part = max_nrows;
 }

 if(nthreads > max_nthreads)
 {
  std::cout << "Protected by limiting threads to " << max_nthreads << " for `fake_data::analysis::FakeAnaData` creation . \n" << warn << std::endl;
  nthreads = max_nthreads;
 }
}


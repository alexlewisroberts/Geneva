message(STATUS "downloading...
     src='http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.08.tar.gz'
     dst='/Users/Hannes/Documents/Geneva/trunk/external/HepMC/HepMC-2.06.08.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.08.tar.gz"
  "/Users/Hannes/Documents/Geneva/trunk/external/HepMC/HepMC-2.06.08.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=a2e889114cafc4f60742029d69abd907
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://lcgapp.cern.ch/project/simu/HepMC/download/HepMC-2.06.08.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")

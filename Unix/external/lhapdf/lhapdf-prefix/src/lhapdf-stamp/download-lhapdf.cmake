message(STATUS "downloading...
     src='http://www.hepforge.org/archive/lhapdf/LHAPDF-6.0.3.tar.gz'
     dst='/Users/Hannes/Documents/Geneva/trunk/external/lhapdf/LHAPDF-6.0.3.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://www.hepforge.org/archive/lhapdf/LHAPDF-6.0.3.tar.gz"
  "/Users/Hannes/Documents/Geneva/trunk/external/lhapdf/LHAPDF-6.0.3.tar.gz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=b2de5580b947d91891b2cd81a02c4014
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://www.hepforge.org/archive/lhapdf/LHAPDF-6.0.3.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")

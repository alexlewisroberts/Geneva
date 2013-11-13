message(STATUS "downloading...
     src='http://www.hepforge.org/archive/lhapdf/pdfsets/6.0/CT10nlo.tar.gz'
     dst='/Users/Hannes/Documents/Geneva/trunk/external/share/LHAPDF/CT10nlo/CT10nlo.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://www.hepforge.org/archive/lhapdf/pdfsets/6.0/CT10nlo.tar.gz"
  "/Users/Hannes/Documents/Geneva/trunk/external/share/LHAPDF/CT10nlo/CT10nlo.tar.gz"
  SHOW_PROGRESS
  # no EXPECTED_HASH
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://www.hepforge.org/archive/lhapdf/pdfsets/6.0/CT10nlo.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")

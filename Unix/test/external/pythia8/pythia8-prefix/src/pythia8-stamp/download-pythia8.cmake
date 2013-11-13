message(STATUS "downloading...
     src='http://home.thep.lu.se/~torbjorn/pythia8/pythia8170.tgz'
     dst='/Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170.tgz'
     timeout='none'")




file(DOWNLOAD
  "http://home.thep.lu.se/~torbjorn/pythia8/pythia8170.tgz"
  "/Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170.tgz"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=d8b4994b2976f9789e84fd00019337ee
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://home.thep.lu.se/~torbjorn/pythia8/pythia8170.tgz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")

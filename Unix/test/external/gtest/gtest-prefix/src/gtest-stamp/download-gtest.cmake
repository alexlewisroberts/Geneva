message(STATUS "downloading...
     src='http://googletest.googlecode.com/files/gtest-1.6.0.zip'
     dst='/Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0.zip'
     timeout='none'")




file(DOWNLOAD
  "http://googletest.googlecode.com/files/gtest-1.6.0.zip"
  "/Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0.zip"
  SHOW_PROGRESS
  EXPECTED_HASH;MD5=4577b49f2973c90bf9ba69aa8166b786
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://googletest.googlecode.com/files/gtest-1.6.0.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")

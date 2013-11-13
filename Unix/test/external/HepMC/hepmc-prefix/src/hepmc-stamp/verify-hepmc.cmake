set(file "/Users/Hannes/Documents/Geneva/trunk/external/HepMC/HepMC-2.06.08.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "a2e889114cafc4f60742029d69abd907")
file(MD5 "${file}" actual_value)
if("${actual_value}" STREQUAL "${expect_value}")
  message(STATUS "verifying file... done")
else()
  message(FATAL_ERROR "error: MD5 hash of
  ${file}
does not match expected value
  expected: ${expect_value}
    actual: ${actual_value}
")
endif()

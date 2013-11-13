set(file "/Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170.tgz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "d8b4994b2976f9789e84fd00019337ee")
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

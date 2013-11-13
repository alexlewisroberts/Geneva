set(file "/Users/Hannes/Documents/Geneva/trunk/external/lhapdf/LHAPDF-6.0.3.tar.gz")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "b2de5580b947d91891b2cd81a02c4014")
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

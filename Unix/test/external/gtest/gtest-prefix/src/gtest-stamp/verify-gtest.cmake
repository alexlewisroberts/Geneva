set(file "/Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0.zip")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "4577b49f2973c90bf9ba69aa8166b786")
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

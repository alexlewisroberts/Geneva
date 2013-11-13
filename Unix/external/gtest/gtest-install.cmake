MESSAGE (STATUS "Installing gtest ...")

file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0/libgtest.a DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/lib)
file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0/libgtest_main.a DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/lib)
file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0/include/gtest DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/include)

MESSAGE (STATUS "Installing gtest ... done")

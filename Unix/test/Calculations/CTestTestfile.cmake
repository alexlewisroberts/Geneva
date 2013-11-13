# CMake generated Testfile for 
# Source directory: /Users/Hannes/Documents/Geneva/trunk/test/Calculations
# Build directory: /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/Calculations
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(mainTest_LO_pythia "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcLO --pythia on --Analyzer Rates --num 10")
ADD_TEST(mainTest_SCETee234_pythia "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcSCETee234 --pythia on --UserHookRestriction SCETee234 --Analyzer SCETee234 --num 10")
ADD_TEST(mainTest_NLOeejj "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcNLOeejj --Analyzer Rates --num 10")
ADD_TEST(mainTest_NLOeejjj "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcNLOeejjj --Analyzer Rates --num 10")
ADD_TEST(mainTest_NLOeejjjNew "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcNLOeejjjNew --Analyzer Rates --num 10")
ADD_TEST(mainTest_SCETee234 "/Users/Hannes/Documents/Geneva/trunk/bin/main_pythia" "--calc CalcSCETee234 --Analyzer Rates --num 10")
ADD_TEST(CalceeRegressionTest "/Users/Hannes/Documents/Geneva/trunk/test/bin/CalceeRegressionTest" "--gtest_color=yes")
ADD_TEST(CalcNLOeejjjNewTest "/Users/Hannes/Documents/Geneva/trunk/test/bin/CalcNLOeejjjNewTest" "--gtest_color=yes")

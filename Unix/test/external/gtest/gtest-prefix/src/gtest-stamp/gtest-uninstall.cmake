MESSAGE (STATUS "Deinstalling gtest ...")

file (GLOB libs /Users/Hannes/Documents/Geneva/trunk/external/lib/libgtest*)

foreach (lib ${libs})
   MESSAGE (STATUS "Removing: ${lib}")
   file (REMOVE ${lib})
endforeach (lib)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/include/gtest")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/include/gtest)

MESSAGE (STATUS "Deinstalling gtest ... done")

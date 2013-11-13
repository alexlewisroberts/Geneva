MESSAGE (STATUS "Deinstalling MadGraph ee_4jets ...")

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/lib/libmadgraph_ee_4jets.dylib")
file (REMOVE /Users/Hannes/Documents/Geneva/trunk/external/lib/libmadgraph_ee_4jets.dylib)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/include/MadGraph")
file (REMOVE /Users/Hannes/Documents/Geneva/trunk/external/include/MadGraph/madMatrixElement_ee_4jets.h;MadConstants_ee_4jets.h)

MESSAGE (STATUS "Deinstalling MadGraph ee_4jets ... done")

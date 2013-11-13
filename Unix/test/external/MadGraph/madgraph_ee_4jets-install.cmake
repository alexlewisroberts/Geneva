MESSAGE (STATUS "Installing MadGraph ee_4jets ...")

file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/MadGraph/process_ee_4jets/libmadgraph_ee_4jets.dylib DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/lib)

foreach (header madMatrixElement_ee_4jets.h;MadConstants_ee_4jets.h)
   file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/MadGraph/process_ee_4jets/${header} DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/include/MadGraph)
endforeach (header)

MESSAGE (STATUS "Installing MadGraph ee_4jets ... done")

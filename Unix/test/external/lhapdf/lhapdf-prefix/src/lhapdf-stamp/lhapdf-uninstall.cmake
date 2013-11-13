MESSAGE (STATUS "Deinstalling LHAPDF ...")

set (bins /Users/Hannes/Documents/Geneva/trunk/external/bin/lhapdf-config)

foreach (bin ${bins})
   MESSAGE (STATUS "Removing: ${bin}")
   file (REMOVE ${bin})
endforeach (bin)

file (GLOB libs /Users/Hannes/Documents/Geneva/trunk/external/lib/libLHAPDF.*)

foreach (lib ${libs})
   MESSAGE (STATUS "Removing: ${lib}")
   file (REMOVE ${lib})
endforeach (lib)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/include/LHAPDF")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/include/LHAPDF)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/share/LHAPDF")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/share/LHAPDF)

MESSAGE (STATUS "Deinstalling LHAPDF ... done")

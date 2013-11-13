MESSAGE (STATUS "Deinstalling Pythia8 ...")

file (GLOB libs /Users/Hannes/Documents/Geneva/trunk/external/lib/libpythia8.* /Users/Hannes/Documents/Geneva/trunk/external/lib/liblhapdfdummy.* /Users/Hannes/Documents/Geneva/trunk/external/lib/libhepmcinterface.*)

foreach (lib ${libs})
   MESSAGE (STATUS "Removing: ${lib}")
   file (REMOVE ${lib})
endforeach (lib)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/include/pythia8")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/include/pythia8)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/share/pythia8")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/share/pythia8)

MESSAGE (STATUS "Deinstalling Pythia8 ... done")

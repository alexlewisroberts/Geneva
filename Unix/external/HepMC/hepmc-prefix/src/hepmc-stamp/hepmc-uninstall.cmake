MESSAGE (STATUS "Deinstalling HepMC ...")

file (GLOB libs /Users/Hannes/Documents/Geneva/trunk/external/lib/libHepMC*)

foreach (lib ${libs})
   MESSAGE (STATUS "Removing: ${lib}")
   file (REMOVE ${lib})
endforeach (lib)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/include/HepMC")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/include/HepMC)

MESSAGE (STATUS "Removing: /Users/Hannes/Documents/Geneva/trunk/external/share/HepMC")
file (REMOVE_RECURSE /Users/Hannes/Documents/Geneva/trunk/external/share/HepMC)

MESSAGE (STATUS "Deinstalling HepMC ... done")

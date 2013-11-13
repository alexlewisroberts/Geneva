MESSAGE (STATUS "Installing Pythia8 ...")

file (GLOB shared_libs
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/libpythia8.*
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/liblhapdfdummy.*
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/libhepmcinterface.*
)
file (GLOB static_libs
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/archive/libpythia8.*
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/archive/liblhapdfdummy.*
   /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/lib/archive/libhepmcinterface.*
)
set (libs ${shared_libs} ${static_libs})

if (APPLE)
   foreach (lib ${shared_libs})
	   get_filename_component (lib_name ${lib} NAME)
	   EXECUTE_PROCESS(COMMAND install_name_tool -id /Users/Hannes/Documents/Geneva/trunk/external/lib/${lib_name} ${lib})
   endforeach(lib)
endif (APPLE)

file (INSTALL ${libs} DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/lib)
file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/include/ DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/include/pythia8)
file (INSTALL /Users/Hannes/Documents/Geneva/trunk/external/pythia8/pythia8170/xmldoc/ DESTINATION /Users/Hannes/Documents/Geneva/trunk/external/share/pythia8)

MESSAGE (STATUS "Installing Pythia8 ... done")

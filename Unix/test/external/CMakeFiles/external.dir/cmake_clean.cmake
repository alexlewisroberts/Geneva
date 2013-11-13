FILE(REMOVE_RECURSE
  "CMakeFiles/external"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/external.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)

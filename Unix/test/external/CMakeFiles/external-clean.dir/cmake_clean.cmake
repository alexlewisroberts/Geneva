FILE(REMOVE_RECURSE
  "CMakeFiles/external-clean"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/external-clean.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)

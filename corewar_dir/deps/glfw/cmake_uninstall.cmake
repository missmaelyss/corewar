
if (NOT EXISTS "/Users/qduperon/Desktop/testlib/deps/glfw/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/Users/qduperon/Desktop/testlib/deps/glfw/install_manifest.txt\"")
endif()

file(READ "/Users/qduperon/Desktop/testlib/deps/glfw/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/private/var/folders/zz/zyxvpxvq6csfxvn_n0001rj0000f48/T/AppTranslocation/DBFFC3EA-66ED-43BC-B479-7D9BD657D620/d/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/private/var/folders/zz/zyxvpxvq6csfxvn_n0001rj0000f48/T/AppTranslocation/DBFFC3EA-66ED-43BC-B479-7D9BD657D620/d/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()


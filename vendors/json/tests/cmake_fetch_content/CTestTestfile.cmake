# CMake generated Testfile for 
# Source directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content
# Build directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(cmake_fetch_content_configure "C:/Program Files/CMake/bin/cmake.exe" "-G" "Visual Studio 16 2019" "-DCMAKE_CXX_COMPILER=D:/Software/Microsoft/Visual Studio/VS2019/Pro/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" "-Dnlohmann_json_source=D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json" "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/project")
  set_tests_properties(cmake_fetch_content_configure PROPERTIES  FIXTURES_SETUP "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;2;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(cmake_fetch_content_configure "C:/Program Files/CMake/bin/cmake.exe" "-G" "Visual Studio 16 2019" "-DCMAKE_CXX_COMPILER=D:/Software/Microsoft/Visual Studio/VS2019/Pro/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" "-Dnlohmann_json_source=D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json" "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/project")
  set_tests_properties(cmake_fetch_content_configure PROPERTIES  FIXTURES_SETUP "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;2;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(cmake_fetch_content_configure "C:/Program Files/CMake/bin/cmake.exe" "-G" "Visual Studio 16 2019" "-DCMAKE_CXX_COMPILER=D:/Software/Microsoft/Visual Studio/VS2019/Pro/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" "-Dnlohmann_json_source=D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json" "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/project")
  set_tests_properties(cmake_fetch_content_configure PROPERTIES  FIXTURES_SETUP "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;2;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(cmake_fetch_content_configure "C:/Program Files/CMake/bin/cmake.exe" "-G" "Visual Studio 16 2019" "-DCMAKE_CXX_COMPILER=D:/Software/Microsoft/Visual Studio/VS2019/Pro/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" "-Dnlohmann_json_source=D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json" "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/project")
  set_tests_properties(cmake_fetch_content_configure PROPERTIES  FIXTURES_SETUP "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;2;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
else()
  add_test(cmake_fetch_content_configure NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(cmake_fetch_content_build "C:/Program Files/CMake/bin/cmake.exe" "--build" ".")
  set_tests_properties(cmake_fetch_content_build PROPERTIES  FIXTURES_REQUIRED "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;9;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(cmake_fetch_content_build "C:/Program Files/CMake/bin/cmake.exe" "--build" ".")
  set_tests_properties(cmake_fetch_content_build PROPERTIES  FIXTURES_REQUIRED "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;9;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(cmake_fetch_content_build "C:/Program Files/CMake/bin/cmake.exe" "--build" ".")
  set_tests_properties(cmake_fetch_content_build PROPERTIES  FIXTURES_REQUIRED "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;9;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(cmake_fetch_content_build "C:/Program Files/CMake/bin/cmake.exe" "--build" ".")
  set_tests_properties(cmake_fetch_content_build PROPERTIES  FIXTURES_REQUIRED "cmake_fetch_content" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;9;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/cmake_fetch_content/CMakeLists.txt;0;")
else()
  add_test(cmake_fetch_content_build NOT_AVAILABLE)
endif()

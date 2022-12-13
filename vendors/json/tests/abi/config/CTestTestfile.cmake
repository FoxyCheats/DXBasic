# CMake generated Testfile for 
# Source directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config
# Build directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test-abi_config_default "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Debug/abi_config_default.exe")
  set_tests_properties(test-abi_config_default PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;6;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test-abi_config_default "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Release/abi_config_default.exe")
  set_tests_properties(test-abi_config_default PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;6;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test-abi_config_default "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/MinSizeRel/abi_config_default.exe")
  set_tests_properties(test-abi_config_default PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;6;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test-abi_config_default "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/RelWithDebInfo/abi_config_default.exe")
  set_tests_properties(test-abi_config_default PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;6;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
else()
  add_test(test-abi_config_default NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test-abi_config_noversion "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Debug/abi_config_noversion.exe")
  set_tests_properties(test-abi_config_noversion PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;13;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test-abi_config_noversion "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Release/abi_config_noversion.exe")
  set_tests_properties(test-abi_config_noversion PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;13;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test-abi_config_noversion "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/MinSizeRel/abi_config_noversion.exe")
  set_tests_properties(test-abi_config_noversion PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;13;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test-abi_config_noversion "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/RelWithDebInfo/abi_config_noversion.exe")
  set_tests_properties(test-abi_config_noversion PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;13;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
else()
  add_test(test-abi_config_noversion NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test-abi_config_custom "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Debug/abi_config_custom.exe")
  set_tests_properties(test-abi_config_custom PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;20;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test-abi_config_custom "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/Release/abi_config_custom.exe")
  set_tests_properties(test-abi_config_custom PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;20;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test-abi_config_custom "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/MinSizeRel/abi_config_custom.exe")
  set_tests_properties(test-abi_config_custom PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;20;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test-abi_config_custom "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/RelWithDebInfo/abi_config_custom.exe")
  set_tests_properties(test-abi_config_custom PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;20;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/json/tests/abi/config/CMakeLists.txt;0;")
else()
  add_test(test-abi_config_custom NOT_AVAILABLE)
endif()

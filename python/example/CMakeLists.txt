configure_file(${CMAKE_CURRENT_SOURCE_DIR}/camera.py ${CMAKE_CURRENT_BINARY_DIR}/camera.py COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/camera.xml ${CMAKE_CURRENT_BINARY_DIR}/camera.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/file.py ${CMAKE_CURRENT_BINARY_DIR}/file.py COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/file.xml ${CMAKE_CURRENT_BINARY_DIR}/file.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lenna.jpg ${CMAKE_CURRENT_BINARY_DIR}/lenna.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/observer.py ${CMAKE_CURRENT_BINARY_DIR}/observer.py COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/simple.py ${CMAKE_CURRENT_BINARY_DIR}/simple.py COPYONLY)

add_test(NAME python_example_camera COMMAND python camera.py)
add_test(NAME python_example_file COMMAND python file.py)
add_test(NAME python_example_observer COMMAND python observer.py)
add_test(NAME python_example_simple COMMAND python simple.py)

set_tests_properties(python_example_camera PROPERTIES ENVIRONMENT "${PYTHON_TEST_ENVIRONMENT}")
set_tests_properties(python_example_file PROPERTIES ENVIRONMENT "${PYTHON_TEST_ENVIRONMENT}")
set_tests_properties(python_example_observer PROPERTIES ENVIRONMENT "${PYTHON_TEST_ENVIRONMENT}")
set_tests_properties(python_example_simple PROPERTIES ENVIRONMENT "${PYTHON_TEST_ENVIRONMENT}")
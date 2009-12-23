find_path(CPPUNIT_INCLUDE_DIR TestSuite.h
	/usr/include/cppunit
	/usr/local/include/cppunit)

find_library(CPPUNIT_LIBRARY cppunit PATHS
    /usr/lib/
    /usr/local/lib)
    
if(CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)
	set(CPPUNIT_FOUND TRUE)
endif()


if(CPPUNIT_FOUND)
   if(NOT CPPUNIT_FIND_QUIETLY)
      message(STATUS "Found CPPUnit: ${CPPUNIT_LIBRARY}")
   endif()
else(CPUNIT_FOUND)
   if(CPPUNIT_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find CPPUNIT")
   endif()
endif()



macro(build_doxygen INPUT_FILES PROJECT_VERSION PROJECT_DESCRIPTION DOC_LOGO)
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
	    find_program(DOT_PATH dot)
	    if(DOT_PATH)
	        set(HAVE_DOT "YES")
	    else()
	        set(HAVE_DOT "NO")
	        message(AUTHOR_WARNING "Doxygen: to generate UML diagrams please install graphviz")
	    endif()	          

        # generate list with spaces as separators
        string(REPLACE ";" " " DOXY_INPUT "${INPUT_FILES}")

	   	set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/doc/Doxyfile.in)
	    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	    # note the option ALL which allows to build the docs together with the application
	    add_custom_target(doc ALL
	        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

		# make other arguments into variables
		set(PROJECT_VERSION ${PROJECT_VERSION})
		set(PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION})
		set(DOC_LOGO ${DOC_LOGO})	        

	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	    
	else (DOXYGEN_FOUND)
	    message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endmacro()




include(CMakeParseArguments)

#GENERATE_PLUGIN_DESCRIPTION(SRC_FILE, DEST_FILE)
function (GENERATE_PLUGIN_DESCRIPTION)
    # Set PLUGIN_SRC and PLUGIN_OUTPUT)
    CMAKE_PARSE_ARGUMENTS(PLUGIN "" "SRC;OUTPUT" "" ${ARGN} )
    set_source_files_properties(${PLUGIN_SRC} PROPERTIES GENERATED TRUE)
    find_package(catkin REQUIRED COMPONENTS templated_transports)
    #message("PLUGIN SRC: ${PLUGIN_SRC}")
    #message("PLUGIN OUT: ${PLUGIN_OUTPUT}")

    execute_process(COMMAND m4 "${templated_transports_SOURCE_DIR}/default_plugins_template.m4" "${PLUGIN_SRC}" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" OUTPUT_FILE "${PLUGIN_OUTPUT}")

ENDFUNCTION (GENERATE_PLUGIN_DESCRIPTION)



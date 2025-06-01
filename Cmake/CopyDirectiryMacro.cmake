
macro(copy_directory src dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${src} ${dst}
        RESULT_VARIABLE ret
        OUTPUT_VARIABLE out
        ERROR_VARIABLE  err
    )
    if(ret)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${err}")
    endif()
endmacro()

# macro(COPY_DLL name from to)
#     file(GLOB dll_name ${from}/${name}*.dll)
#     if (dll_name STREQUAL "")
#         message("ERROR: ASSIMP DLL COULD NOT BE COPIED")
#     else ()
#         get_filename_component(dll_name ${dll_name} NAME)
#         message("COPY TO ${to}/${dll_name}")
#         file(COPY ${from}/${dll_name} DESTINATION ${to})
#     endif ()
# endmacro()



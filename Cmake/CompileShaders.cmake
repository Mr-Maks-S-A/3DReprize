cmake_minimum_required(VERSION 4.0 FATAL_ERROR)


function(Compile_Shaders)
    cmake_parse_arguments(PR "SILENC" "SERCH_DIRECTORY" "OUTPUT_DIRECTORY" "EXTENSIONS" ${ARGN})


    if(NOT PR_SERCH_DIRECTORY)
		  message(FATAL_ERROR "compile_shaders: SerchDirectory not specified")
	  endif()
    
    if(NOT PR_OUTPUT_DIRECTORY)
      message(STATUS "compile_shaders: OUTPUT_DIRECTORY not specified, using ${PR_SERCH_DIRECTORY}")
		  set(PR_OUTPUT_DIRECTORY ${PR_SERCH_DIRECTORY})
	  endif()




    find_package(Vulkan REQUIRED QUIET COMPONENTS glslc)
    if (NOT Vulkan_glslc_FOUND)
      message(FATAL_ERROR "compile_shaders: Vulkan glslc not found")
    else()
      message(STATUS "compile_shaders: Found Vulkan glslc at ${Vulkan_GLSLC_EXECUTABLE}")
    endif()


    set(PR_EXENSIONS ".vert" ".frag" ".geom" ".tesc" ".tese" ".comp")
    list(APPEND PR_EXENSIONS ${PR_EXTENSIONS})

    #Serch GLSL SHaders
    set(PR_SHADERS_GLSL)
    foreach(EXTENTION IN LISTS PR_EXENSIONS)
      file(GLOB_RECURSE tmp CONFIGURE_DEPENDS ${PR_SERCH_DIRECTORY}/*${EXTENTION})
      list(APPEND PR_SHADERS_GLSL ${tmp})
    endforeach()

    list(LENGTH PR_SHADERS_GLSL PR_SHADERS_GLSL_COUNT)
    message(STATUS "compile_shaders: Compiling ${PR_SHADERS_GLSL_COUNT} shaders from ${PR_SERCH_DIRECTORY} to ${PR_OUTPUT_DIRECTORY}")
  

    #compiling glsl to spirv
    set(_log)
    foreach(PR_SHADER_GLSL IN LISTS PR_SHADERS_GLSL)
      
      get_filename_component(PR_SHADER_GLSL_NAME ${PR_SHADER_GLSL} NAME)
      
      if(PR_OUTPUT_DIRECTORY)
          set(output_file ${PR_OUTPUT_DIRECTORY}/${PR_SHADER_GLSL_NAME}.spv)
        else()
          set(output_file ${PR_SHADER_GLSL}.spv)
      endif()
      

      if(NOT EXISTS ${output_file} OR ${PR_SHADER_GLSL} IS_NEWER_THAN ${output_file})
        message(STATUS "compile_shaders: Compiling ${PR_SHADER_GLSL} to ${output_file}")
        execute_process(
          COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${PR_SHADER_GLSL} -o ${output_file}
          OUTPUT_VARIABLE _output
          RESULT_VARIABLE result
        )
        if(result)
        	list(APPEND _log "compile_shaders: ❌ ${PR_SHADER_GLSL_NAME} -> ${PR_SHADER_GLSL_NAME}.spv (${result})")
        	message(WARNING ${_output})
        else()
        	list(APPEND _log "compile_shaders: ✅ ${PR_SHADER_GLSL_NAME} -> ${PR_SHADER_GLSL_NAME}.spv")
        endif()
      else()
      	list(APPEND _log "compile_shaders: ♻️ ${PR_SHADER_GLSL_NAME} -> ${PR_SHADER_GLSL_NAME}.spv (up to date)")
      endif()
	endforeach()


endfunction()



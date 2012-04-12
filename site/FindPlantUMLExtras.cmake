# Render PlantUML diagrams to PNG.
function(add_diagram target source)
  if(Java_JAVA_EXECUTABLE AND PLANTUML_JARFILE)
    set(plantuml ${Java_JAVA_EXECUTABLE} -jar ${PLANTUML_JARFILE})
    get_filename_component(output ${source} NAME_WE)
    add_custom_command(
      OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/${output}.png
      COMMAND
        ${plantuml} -o ${CMAKE_CURRENT_BINARY_DIR} -tpng ${source}
      MAIN_DEPENDENCY
        ${source}
      COMMENT
        "Rendering UML diagram '${output}'."
    )
    add_custom_target(${target}
      ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${output}.png
    )
  endif()
endfunction()

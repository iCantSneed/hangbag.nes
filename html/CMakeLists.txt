set(HTML_OUT_DIR "${CMAKE_BINARY_DIR}/html_out")
add_custom_target(html
  COMMAND ${CMAKE_COMMAND} -E make_directory ${HTML_OUT_DIR}
  COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/generate_html.sh"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.nes"
    "${CMAKE_CURRENT_SOURCE_DIR}/index.html"
    "${HTML_OUT_DIR}/${PROJECT_NAME}.html"
  DEPENDS ${PROJECT_NAME}
)
add_custom_target(html
  COMMAND /bin/sh "${CMAKE_CURRENT_SOURCE_DIR}/generate_html.sh"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.nes"
    "${CMAKE_CURRENT_SOURCE_DIR}/index.html"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.html"
  DEPENDS ${PROJECT_NAME}
)
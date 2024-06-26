cmake_minimum_required(VERSION 3.8)
set(PROJECT_NAME as2_knowledge_graph)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#Find dependencies
set(PROJECT_DEPENDENCIES
  ament_cmake
  rclcpp
  backward_ros
  knowledge_graph
  knowledge_graph_msgs
  rosidl_default_generators
  ament_cmake_gtest
  as2_core
  as2_knowledge_graph_msgs
)

set(SUBPROJECT_NAME
  as2_knowledge_graph_service_client_main
  as2_knowledge_graph_node_server_main
)

foreach(DEPENDENCY ${PROJECT_DEPENDENCIES})
  find_package(${DEPENDENCY} REQUIRED)
endforeach()

#Include directories
include_directories(
  include
  include/${PROJECT_NAME}
  include/${SUBPROJECT_NAME}
)

set(SOURCE_CPP_FILES
  src/${SUBPROJECT_NAME}.cpp
)



ament_export_dependencies(rosidl_default_runtime)

# Library
add_library(${PROJECT_NAME} SHARED src/as2_knowledge_graph_service_client.cpp src/as2_knowledge_graph_node_server.cpp)
# Include headers in the library
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(${PROJECT_NAME} ${PROJECT_DEPENDENCIES})



add_executable(as2_knowledge_graph_node_server_main src/as2_knowledge_graph_node_server_main.cpp)
ament_target_dependencies(as2_knowledge_graph_node_server_main ${PROJECT_DEPENDENCIES})
target_link_libraries(as2_knowledge_graph_node_server_main  ${PROJECT_NAME})

add_executable(as2_knowledge_graph_service_client_main src/as2_knowledge_graph_service_client_main.cpp)
ament_target_dependencies(as2_knowledge_graph_service_client_main  ${PROJECT_DEPENDENCIES})
target_link_libraries(as2_knowledge_graph_service_client_main ${PROJECT_NAME})


#Install
install(
  DIRECTORY include/
  DESTINATION include
)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
  ${SUBPROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${PROJECT_NAME}
)

ament_export_targets(
  export_${PROJECT_NAME}
)


install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  file(GLOB_RECURSE EXCLUDE_FILES
    build/*
    install/*
  )
  set(AMENT_LINT_AUTO_FILE_EXCLUDE ${EXCLUDE_FILES})
  ament_lint_auto_find_test_dependencies()
  add_subdirectory(tests)
endif()

ament_package()
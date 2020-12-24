project(protobuf_tutorial)
cmake_minimum_required(VERSION 3.18)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS addressbook.proto)

add_library(addressbook_proto
	${PROTO_SRCS}
	${PROTO_HDRS}
)

target_link_libraries(addressbook_proto
	${Protobuf_LIBRARIES}
)

add_executable(write_message
	"WriteMessage.cpp"
)

target_link_libraries(write_message
	addressbook_proto
)

add_executable(read_message
	"ReadMessage.cpp"
)

target_link_libraries(read_message
	addressbook_proto
)

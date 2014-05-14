cmake_minimum_required(VERSION 2.8)
project( Message )

#	Google Protocol Buffers
find_package( Protobuf REQUIRED )
include_directories(${PROTOBUF_INCLUDE_DIR})
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})

add_library(message
        ${ProtoSources} 
        ${ProtoHeaders}
)
        
target_link_libraries(message ${PROTOBUF_LIBRARIES})

install(TARGETS message
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)

 
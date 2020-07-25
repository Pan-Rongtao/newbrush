file(GLOB PROTO_FILES ${GAPI_PROTO_DIR}/*.proto)
function(grpc_gen)
    foreach(_proto ${PROTO_FILES})
        execute_process(COMMAND ${TOOLDIR}/protoc.exe --proto_path=${PROTO_PATH} -I=${GAPI_PROTO_DIR} --grpc_out=${GAPI_GEN_DIR} --plugin=protoc-gen-grpc=${TOOLDIR}/grpc_cpp_plugin.exe ${_proto}
            RESULT_VARIABLE _result0
        )
        execute_process(COMMAND ${TOOLDIR}/protoc.exe --proto_path=${PROTO_PATH} -I=${GAPI_PROTO_DIR} --cpp_out=${GAPI_GEN_DIR} ${_proto} RESULT_VARIABLE _result1)

        if(${_result0} OR ${_result1})
             message(FATAL_ERROR "[${PROJECT_NAME}] - GAPI_GEN fail on ${_proto}: ${_result0}, ${_result1}")
        endif()
    endforeach()
endfunction()

grpc_gen()
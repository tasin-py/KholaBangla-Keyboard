include_directories(../riti/include ../../shared ${IBUS_INCLUDE_DIRS})
add_executable(ibus-engine-kholabangla main.cpp)
target_link_libraries(ibus-engine-kholabangla riti libShared Qt5::Core ${IBUS_LIBRARIES} dl pthread)

configure_file(${CMAKE_SOURCE_DIR}/data/kholabangla.xml.in ${CMAKE_BINARY_DIR}/data/kholabangla.xml)

install(FILES ${CMAKE_BINARY_DIR}/data/kholabangla.xml
        DESTINATION "${DATADIR}/ibus/component")

install(TARGETS ibus-engine-kholabangla
        RUNTIME DESTINATION ${LIBEXECDIR})

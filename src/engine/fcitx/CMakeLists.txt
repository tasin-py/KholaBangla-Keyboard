include("${FCITX_INSTALL_CMAKECONFIG_DIR}/Fcitx5Utils/Fcitx5CompilerSettings.cmake")

find_package(Pthread REQUIRED)
find_package(DL REQUIRED)

add_library(kholabangla MODULE kholabangla.cpp)
target_link_libraries(kholabangla Fcitx5::Core riti Pthread::Pthread DL::DL)
target_include_directories(kholabangla PRIVATE ../riti/include)
set_target_properties(kholabangla PROPERTIES PREFIX "")
install(TARGETS kholabangla DESTINATION "${FCITX_INSTALL_LIBDIR}/fcitx5")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/kholabangla.conf" DESTINATION "${FCITX_INSTALL_PKGDATADIR}/inputmethod")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/kholabangla-addon.conf" RENAME kholabangla.conf DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon")

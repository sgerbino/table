set(CPACK_PACKAGE_NAME "libtable")
set(CPACK_PACKAGE_VENDOR "${TABLE_MAINTAINER}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${TABLE_MAINTAINER}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${TABLE_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${TABLE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${TABLE_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${TABLE_PATCH_VERSION}")
set(CPACK_PACKAGE_VERSION "${TABLE_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
include(CPack)

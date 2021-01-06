# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/mnt/storage/pkgbuilds/liborcania/src/orcania-2.1.1;/mnt/storage/pkgbuilds/liborcania/src/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Potluck with different functions for different purposes that can be shared among programs")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/babelouest/orcania")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "mail@babelouest.org")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.19/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "orcania built using CMake")
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_INSTALL_CMAKE_PROJECTS "/mnt/storage/pkgbuilds/liborcania/src/build;orcania;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr")
set(CPACK_MODULE_PATH "/mnt/storage/pkgbuilds/liborcania/src/orcania-2.1.1/cmake-modules")
set(CPACK_NSIS_DISPLAY_NAME "liborcania 2.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "liborcania 2.1.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/mnt/storage/pkgbuilds/liborcania/src/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.19/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Potluck for C programs")
set(CPACK_PACKAGE_FILE_NAME "liborcania-dev_2.1.1")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "liborcania 2.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "liborcania 2.1.1")
set(CPACK_PACKAGE_NAME "liborcania")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "2.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake-3.19/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.19/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.19/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/mnt/storage/pkgbuilds/liborcania/src/build/;/.git/;.gitignore;~$")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/mnt/storage/pkgbuilds/liborcania/src/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "liborcania-dev_2.1.1")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/mnt/storage/pkgbuilds/liborcania/src/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
SET (CMAKE_VERBOSE_MAKEFILE off) 

ADD_DEFINITIONS(-DTARGET_IS_TM4C123_RA1)
# Secify the chip macro here (grep SW-TM4C project for that)
ADD_DEFINITIONS (-DPART_TM4C123GH6PM)

#ADD_DEFINITIONS (-DTARGET_IS_TM4C129_RA1)
# Secify the chip macro here (grep SW-TM4C project for that)
#ADD_DEFINITIONS (-DPART_TM4C1294NCPDT)

PROJECT (ltp4335)
#include (tm4c129.cmake)
include (tm4c123.cmake)

INCLUDE_DIRECTORIES("../src/")
AUX_SOURCE_DIRECTORY ("../src/" APP_SOURCES)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${APP_SOURCES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME}.elf ${TIVA_WARE_PATH}/usblib/gcc/libusb.a)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME}.elf ${TIVA_WARE_PATH}/driverlib/gcc/libdriver.a)

FIND_PROGRAM (OPENOCD_EXECUTABLE openocd)
#ADD_CUSTOM_TARGET("upload" DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${OPENOCD_EXECUTABLE} -f /home/iwasz/local/share/openocd/scripts/board/ek-tm4c1294xl.cfg -c 'program ${CMAKE_PROJECT_NAME}.elf verify reset')
ADD_CUSTOM_TARGET("upload" DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${OPENOCD_EXECUTABLE} -f /usr/share/openocd/scripts/board/ek-lm4f120xl.cfg -c 'program ${CMAKE_PROJECT_NAME}.elf verify reset')


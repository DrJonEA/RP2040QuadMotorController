if (DEFINED RP2350LCD096_PATH)
	message("Using Given RP2350LCD096_PATH '${RP2350LCD096_PATH}')")
else ()
	set(RP2350LCD096_PATH "${CMAKE_CURRENT_LIST_DIR}lib/")
    message("Using local RP2350LCD096_PATH '${RP2350LCD096_PATH}')")
endif ()

add_library(RP2350LCD096 STATIC)
target_sources(RP2350LCD096 PUBLIC
  ${RP2350LCD096_PATH}/LCD/LCD_0in96.c
  ${RP2350LCD096_PATH}/Config/DEV_Config.c
)


# Add include directory
target_include_directories(RP2350LCD096 PUBLIC 
	${RP2350LCD096_PATH}/LCD/
	${RP2350LCD096_PATH}/Config/
)


target_link_libraries(RP2350LCD096 PUBLIC 
	pico_stdlib
	hardware_pio 
	hardware_pwm 
	hardware_dma
	hardware_spi
	hardware_i2c
	hardware_gpio
	hardware_adc
	pico_multicore
)


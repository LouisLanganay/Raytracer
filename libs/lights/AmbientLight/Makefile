##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

include ../../../Makefile_colors.mk

LIB 		= lib_ambient_light.so

VPATH 		:= ./src
VPATH 		+= ../
VPATH 		+= ../../../src/Loader
VPATH 		+= ./
VPATH 		+= ../../../src/Vector
VPATH 		+= ../../../src/Point
VPATH 		+= ../../../src/Ray

vpath %.cpp $(VPATH)

SRC			:= AmbientLight.cpp
SRC 		+= ALight.cpp
SRC 		+= Point3D.cpp
SRC 		+= Vector3D.cpp
SRC 		+= Ray.cpp

CFLAGS 		= -Wall

BUILD_DIR 	= build
OBJ 		:= $(SRC:%.cpp=$(BUILD_DIR)/%.o)

DIE         = exit 1
ECHO        = echo -e

all: $(LIB)
	@ $(ECHO) "${_B_GREEN}[SUCCES]${_END} plugin compiled successfully !"

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(@D)
	@ g++ -c -o $@ $< -fPIC -g
	@ $(ECHO) "${_CYAN}[OK]${_END} -> g++    ${_U_WHITE}$<${_END}"

$(LIB): $(OBJ)
	@ ld -shared -ldl -o $(LIB) $(OBJ)
	@ $(ECHO) "${_B_GREEN}[SUCCES]${_END} library compiled successfully !"

clean:
	@ $(RM) *.gcda
	@ $(RM) *.gcno
	@ $(RM) *.gcov
	@ $(RM) vgcore.*
	@ rm -rf $(BUILD_DIR)
	@ rm -f unit_tests
	@ $(ECHO) "${_B_RED}[CLEAN]${_END} removed .gcda, .gcno, .gcov, vgcore.* and build/"

fclean: clean
	@ rm -f $(LIB)
	@ rm -f ../../$(LIB)
	@ rm -f $(LIB_BAR)
	@ rm -f $(EXEC)
	@ $(ECHO) "${_B_RED}[FCLEAN]${_END} removed lib, lib_bar and exec"

re: fclean all

.PHONY: all clean fclean re
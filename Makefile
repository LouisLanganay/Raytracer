##
## EPITECH PROJECT, 2024
## bs-rt
## File description:
## Makefile
##

include Makefile_colors.mk

NAME 		= raytracer
CC 			= g++

VPATH 		:= ./src
VPATH 		+= ./src/Loader
VPATH 		+= ./src/Factory
VPATH 		+= ./src/Vector
VPATH 		+= ./src/Parser
VPATH 		+= ./src/Scene
VPATH 		+= ./src/Camera
VPATH 		+= ./src/Point
VPATH 		+= ./src/Ray
VPATH 		+= ./src/Rectangle
VPATH 		+= ./src/Matrix
VPATH 		+= ./src/Interval

vpath %.cpp $(VPATH)

SRC 		:= Main.cpp
SRC 		+= LibLoader.cpp
SRC 		+= Parser.cpp
SRC 		+= Scene.cpp
SRC 		+= Camera.cpp
SRC 		+= Point3D.cpp
SRC 		+= Vector3D.cpp
SRC 		+= Ray.cpp
SRC 		+= Rectangle3D.cpp
SRC 		+= Matrix.cpp
SRC 		+= Interval.cpp

BUILD_DIR 	= build
OBJ 		:= $(SRC:%.c=$(BUILD_DIR)/%.o)

VPATH_DIRS  := $(sort $(dir $(wildcard $(addsuffix /, $(VPATH)))))
CFLAGS      := -std=c++20 -Wall -Wextra -iquote./includes -iquote./libs/lights
CFLAGS		+= -iquote./libs/materials -iquote./libs/primitives -g
CFLAGS      += $(foreach dir, $(VPATH_DIRS), -iquote$(dir))

LDFLAGS 	= -lconfig++

BUILD_DIR   = build
OBJ         := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

DIE         = exit 1
ECHO        = echo -e


%.cpp:
	@ $(ECHO) "${_B_RED}[ERROR]${_END} File ${_B_WHITE}$@${_END} not found."
	@ $(DIE)

all: $(NAME) plugins
	@ $(ECHO) "${_B_GREEN}[SUCCES]${_END} project compiled successfully !"

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ $(ECHO) "${_CYAN}[OK]$(_END) -> $(CC)    $(_U_WHITE)$<$(_END)"

$(NAME): $(OBJ)
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@ $(ECHO) "${_CYAN}[OK]$(_END) -> $(CC)    \
	$(_U_WHITE)$(NAME) $(CFLAGS) ${_END}"
	@ $(ECHO) "$(_B_PURPLE)[STATS]$(_END) -> \
	$(_U_WHITE)$(shell echo "$?" | wc -w) file(s) compiled${_END}."

plugins:
	@ make -s -C ./libs/lights/DirectionalLight
	@ make -s -C ./libs/lights/PointLight
	@ make -s -C ./libs/lights/AmbientLight
	@ make -s -C ./libs/primitives/Sphere
	@ make -s -C ./libs/render/PPM
	@ make -s -C ./libs/render/PNG
	@ make -s -C ./libs/materials/Flat
	@ make -s -C ./libs/materials/Mirror
	@ make -s -C ./libs/materials/Lambertian

debug: CFLAGS += -g

clean:
	@ $(RM) *.gcda
	@ $(RM) *.gcno
	@ $(RM) *.gcov
	@ $(RM) vgcore.*
	@ $(RM) coding-style-reports.log
	@ $(RM)	$(OBJ)
	@ make clean -s -C ./libs/lights/DirectionalLight
	@ make clean -s -C ./libs/lights/PointLight
	@ make clean -s -C ./libs/lights/AmbientLight
	@ make clean -s -C ./libs/primitives/Sphere
	@ make clean -s -C ./libs/render/PPM
	@ make clean -s -C ./libs/render/PNG
	@ make clean -s -C ./libs/materials/Flat
	@ make clean -s -C ./libs/materials/Mirror
	@ make clean -s -C ./libs/materials/Lambertian
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcda${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcno${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcov${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    vgcore.*${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    coding-style-reports.log${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(OBJ)${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/primitives/Shpere${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/lights/DirectionalLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/lights/PointLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/lights/AmbientLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/render/PPM${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/render/PNG${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/materials/Flat${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make clean -s -C ./libs/materials/Mirror${_END}"

fclean: clean
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM)	$(NAME)
	@ $(RM)	$(NAME)_tests
	@ $(RM) -r doc
	@ make fclean -s -C ./libs/lights/DirectionalLight
	@ make fclean -s -C ./libs/lights/PointLight
	@ make fclean -s -C ./libs/lights/AmbientLight
	@ make fclean -s -C ./libs/primitives/Sphere
	@ make fclean -s -C ./libs/render/PPM
	@ make fclean -s -C ./libs/render/PNG
	@ make fclean -s -C ./libs/materials/Flat
	@ make fclean -s -C ./libs/materials/Mirror
	@ make fclean -s -C ./libs/materials/Lambertian
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(BUILD_DIR)${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(NAME)${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(NAME)_tests${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    doc${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/lights/DirectionalLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/lights/PointLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/lights/AmbientLight${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/primitives/Sphere${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/render/PPM${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/render/PNG${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/materials/Flat${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> make fclean -s -C ./libs/materials/Mirror${_END}"

re: fclean all

.PHONY: all clean fclean re

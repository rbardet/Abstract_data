
INCLUDE_PATH := ../includes

CXXFLAGS := -Wall -Werror -Wextra -Wno-deprecated-copy

SRCS_DIR = srcs

FILES = srcs/vector.cpp

CONTAINERS = $(FILES:${SRCS_DIR}/%.cpp=%)

all: ${CONTAINERS}

${CONTAINERS}:
	c++ -fsyntax-only ${CXXFLAGS} -I ${INCLUDE_PATH} -D NAMESPACE=ft ${SRCS_DIR}/$@.cpp

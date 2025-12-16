NAME = containers

CC = c++
CFLAGS = -Wall -Wextra -Werror -pedantic -O3 -Wno-deprecated-copy -g -std=c++98

INCLUDES = -I includes

SOURCES = main.cpp \

OBJDIR = obj
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

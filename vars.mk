NAME = containers

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = -I includes

SOURCES = main.cpp \
	srcs/vector.cpp

OBJDIR = obj
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

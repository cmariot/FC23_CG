#NAME		=	//media/sf_VB_shared/codingame_sync_file
NAME		=	codingame_sync_file
BINARY		=	compiled

CXX			=	g++

CPPFLAGS	=	-MMD
CXXFLAGS	=	-Wall -Wextra #-Werror

#ADD YOUR SOURCES BELOW WITHOUT THE SOURCE PREFIX MAIN.C GIVEN AS EXAMPLE
SRCS		=	main.cpp \
				parsing.cpp \

#IF YOU HAVE HEADER FILES YOU ABSOLUTELY NEED TO ADD THEM IN THE INC_FILES VAR
INC_FILES	= main.hpp \
			  Creature.hpp \
			  Drone.hpp \
			  Player.hpp \


INC_PATH	=	includes/
INC			=	-I $(INC_PATH)


SRCS_PATH	=	./srcs/
OBJS_PATH	=	./obj/

OBJS		=	$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS		=	$(OBJS:.o=.d)


all: $(NAME)

$(NAME):	$(addprefix $(INC_PATH), $(INC_FILES)) $(addprefix $(SRCS_PATH), $(SRCS))
			@cat $^ | grep -v '#\s*include\s*"' > $(NAME)
			make $(BINARY)
			@echo "Created merged file"

$(BINARY): $(OBJS)
			$(CXX) $(CXXFLAGS) $^ -o $(BINARY) $(INC)


$(OBJS_PATH):
				mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.cpp
					@mkdir -p $(dir $@)
					$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(INC)


clean:
		rm -rf $(OBJS_PATH)

fclean:		clean
		rm -rf $(NAME)

re:	fclean
	make all


.PHONY: all clean fclean re test vtest

-include $(DEPS)

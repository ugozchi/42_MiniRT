# Compiler settings
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -I$(HEAD_DIR) -O3
LDFLAGS		=	-Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME		=	miniRT
LIBFT		=	libft.a
LIBMLX		=	libmlx.a

# Directories
SRCS_DIR	=	./sources/
HEAD_DIR	=	./include/
LIBFT_DIR	=	./libft/
LIBMLX_DIR	=	./minilibx-linux/
OBJ_DIR		=	$(SRCS_DIR)/.o

# Colours, symbols and utils
GREEN		=	\033[1;32m
LIGHT_GREEN	=	\033[1;92m
CYAN		=	\033[1;36m
LIGHT_CYAN	=	\033[1;96m
YELLOW		=	\033[1;33m
LIGHT_YELLOW=	\033[1;93m
RED			=	\033[1;31m
LIGHT_RED	=	\033[1;91m
ROSE		=	\033[38;5;216m
NC			=	\033[0m
BOLD		=	\033[1m
TICK		=	✓
INFO		=	ⓘ

# Source files (relative to SRCS_DIR)
SRC			=	parsing/parse_ambiant_light.c \
				parsing/parse_camera.c \
				parsing/parse_cylinder.c \
				parsing/parse_cylinder_utils.c \
				parsing/parse_light_utils.c \
				parsing/parse_light.c \
				parsing/parse_plane_utils.c \
				parsing/parse_plane.c \
				parsing/parse_sphere.c \
				parsing/parse_utils.c \
				init/init_scene.c \
				init/key_binding.c \
				init/window.c \
				exec/render_light/ambient_light.c \
				exec/render_light/light.c \
				exec/render_scene/intersect/intersect_cylinder.c \
				exec/render_scene/intersect/intersect_objects.c \
				exec/render_scene/intersect/intersect_plane.c \
				exec/render_scene/intersect/intersect_sphere.c \
				exec/render_scene/check_intersections.c \
				exec/render_scene/generate_rays.c \
				exec/render_scene/rays_utils.c \
				exec/render_scene/render.c \
				exec/render_scene/trace_rays.c \
				exec/render_scene/vector_utils.c \
				main.c


SRCS		=	$(addprefix ${SRCS_DIR}, ${SRC})		
SRC_NR		=	${words ${SRCS}}

OBJS		=	${patsubst ${SRCS_DIR}%, ${OBJ_DIR}/%, ${SRCS:.c=.o}}

%.o: %.c
				@mkdir -p $(dir $@)
				@printf "Compiling $(notdir $<)"
				@$(CC) $(CFLAGS) -c $< -o $@
				@printf "$(GREEN) $(TICK)\n$(NC)"


# Rules
all:			project_logo ${OBJ_DIR}
				@make -s ${LIBFT};
				@make -s ${LIBMLX};
				@make -s ${NAME};

${LIBFT}:
				@echo "${CYAN}\nCOMPILING $$(echo ${LIBFT} | tr '[:lower:]' '[:upper:]')${NC}"
				@if [ -d ${LIBFT_DIR} ]; \
				then git -C ${LIBFT_DIR} pull; \
				else git clone https://github.com/ugozchi/42_Libft.git ${LIBFT_DIR}; \
				fi
				make -C ${LIBFT_DIR}


${LIBMLX}:
				@echo "${CYAN}\nCOMPILING $$(echo ${LIBMLX} | tr '[:lower:]' '[:upper:]')\n${NC}"
				@if [ ! -d ${LIBMLX_DIR} ]; then \
					git clone https://github.com/42paris/minilibx-linux.git ${LIBMLX_DIR}; \
				fi
				@make -C ${LIBMLX_DIR}


${NAME}:		entry_message ${OBJS}
				@if [ -e ${NAME} ] && [ "$(shell find ${OBJ_DIR} -newer ${NAME} 2>/dev/null)" = "" ]; then \
					echo "${YELLOW}${INFO} Nothing to do${NC}"; \
				else \
					${CC} ${CFLAGS} ${OBJS} -I${HEAD_DIR} ${LIBFT_DIR}${LIBFT} ${LIBMLX_DIR}${LIBMLX} ${LDFLAGS} -o ${NAME}; \
					echo "${YELLOW}\nCompilation complete, ${NAME} executable at the root of the directory${NC}\n"; \
				fi

${OBJ_DIR}:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then mkdir -p "${OBJ_DIR}"; \
				fi

${OBJ_DIR}/%.o:	${SRCS_DIR}/%.c
				@mkdir -p ${dir $@}
				@printf "Compiling ${notdir $<}"; \
				${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@; \
				printf "${GREEN}"; \
				printf " ${TICK}\n"; \
				printf "${NC}"; 

clean:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "${YELLOW}${INFO} Repo already clean, all .o files are deleted${NC}"; \
				else \
					echo "${RED}Removing all .o files${NC}"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean: clean
				@if [ -d ${LIBFT_DIR} ]; then \
					echo "\n${CYAN}Running fclean for LIBFT${NC}"; \
					make -s fclean -C ${LIBFT_DIR}; \
					echo "${RED}Removing ${LIBFT_DIR}${NC}"; \
					rm -rf ${LIBFT_DIR}; \
				fi
				@if [ -d ${LIBMLX_DIR} ]; then \
					echo "\n${CYAN}Running clean for LIBMLX${NC}"; \
					make -s clean -C ${LIBMLX_DIR}; \
					echo "${RED}Removing ${LIBMLX_DIR}${NC}"; \
					rm -rf ${LIBMLX_DIR}; \
				fi
				@if [ ! -f "${NAME}" ]; then \
					echo "\n${YELLOW}No binary ${NAME} to remove${NC}"; \
				else \
					echo "\n${RED}Removing binary ${NAME}${NC}"; \
					rm -f ${NAME}; \
				fi


re:				fclean all

project_logo:
	@echo ""
	@echo "$(ROSE)   ███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗   $(NC)"
	@echo "$(ROSE)   ████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝   $(NC)"
	@echo "$(ROSE)   ██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║      $(NC)"
	@echo "$(ROSE)   ██║╚██╔╝██║██║██║╚██╗██║██║██╔██═╝    ██║      $(NC)"
	@echo "$(ROSE)   ██║ ╚═╝ ██║██║██║ ╚████║██║██║ ██╚╗   ██║      $(NC)"
	@echo "$(ROSE)   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝      $(NC)"
	@echo "		a 42 Project by RIOS Corentin & ZANCHI Ugo"

entry_message:
				@echo "${CYAN}\nCOMPILING $$(echo ${NAME} | tr '[:lower:]' '[:upper:]')\n${NC}${BOLD}Compiling necessary .o files out of $(SRC_NR) files${NC}"

.PHONY:			all clean fclean re project_logo entry_message

CC = cc

CFLAGS = -Wall -Wextra -Werror

TARGET = pipex

LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(TARGET)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(TARGET): pipex.c $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(TARGET) pipex.c -L$(LIBFT_DIR) -lft

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(LIBFT_LIB)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

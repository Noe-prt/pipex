CC = cc

CFLAGS = -Wall -Wextra -Werror -g

TARGET = pipex

LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(TARGET)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(TARGET): main.c $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(TARGET) main.c -L$(LIBFT_DIR) -lft

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(LIBFT_LIB)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

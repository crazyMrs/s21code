CC = gcc -Wall -Werror -Wextra
TARGET = s21_cat

$(TARGET): s21_cat.o
	$(CC) s21_cat.o -o $(TARGET)

s21_cat.o: 
	$(CC) -c s21_cat.c -o s21_cat.o

clean:
	rm $(TARGET) *.o



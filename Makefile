CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g 

# Archivos fuente
SRCS = main.c ordenacion_monticulos.c monticulo_minimos.c

# Archivos objeto generados a partir de los archivos fuente
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
TARGET = p2

# Regla principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Regla para cada archivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para compilar main.c sin reglas de dependencia
main.o: main.c

# Reglas de dependencia
main.o: ordenacion_monticulos.h monticulo_minimos.h
ordenacion_monticulos.o: ordenacion_monticulos.h monticulo_minimos.h
monticulo_minimos.o: monticulo_minimos.h


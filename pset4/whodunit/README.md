# Questions

## What's `stdint.h`?

### Es una librería que permite crear tipos de datos de un ancho exacto a través de los typedefs

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

### Que se puede tener una versión optimizada de los tipos de datos para ser más exacto en el uso de la misma

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

### BYTE: 1 byte, DWORD: 4 bytes, LONG: 4 bytes, WORD: 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

### 0x4d42

## What's the difference between `bfSize` and `biSize`?

### La diferencia es que biSize es el tamaño de la información del bitmap y bfSize es el tamaño de la cabecera del bitmap

## What does it mean if `biHeight` is negative?

### Si la altura es negativa seguramente es que el mapa de bits es un DIB de arriba hacia abajo y su origen es la esquina superior izquierda.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

### biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

### Porque ya no había memoria disponible

## Why is the third argument to `fread` always `1` in our code?

### Porque solo queremos leer 1 elemento de datos del tamaño especificado.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

### 3

## What does `fseek` do?

### Devuelve la posición actual del puntero de archivo.Salta un cierto número de bytes a partir de la posición de archivo especificada

## What is `SEEK_CUR`?

### Devuelve la posición actual del puntero de archivo.
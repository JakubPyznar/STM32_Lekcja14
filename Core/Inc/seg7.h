
#pragma once
#include <stdint.h>

// Funkcja pokazuje cyfre na wyswietlaczu
// value - liczba do wyswietlenia
// return - void
void seg7_show(uint32_t value);

// Funkcja zmiany aktywnego wyswietlacza
// return - void
void seg7_update(void);

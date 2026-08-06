#include <stdio.h>
/* Standardbibliothek für allgemeine Funktionen (exit) */
#include <stdlib.h>

/* Bibliothek für Zeichenfunktionen (toupper) */
#include <ctype.h>

/* Gibt die korrekte Verwendung des Programms aus. */
void usage(const char *progname)
{
    /* Gibt den Programmnamen und die erwartete Syntax aus. */
    printf("Usage: %s filename\n", progname);
}

/* Gibt eine Fehlermeldung aus und beendet das Programm. */
void err_and_out(const char *message)
{
    /* 
     * Gibt die übergebene Fehlermeldung zusammen mit der Systemfehlermeldung
     * aus.
     */
    perror(message);

    /* Beendet das Programm mit Fehlercode 1. */
    exit(1);
}

int main(int argc, char *argv[])
{
    /* Variable zum Speichern des aktuell gelesenen Zeichens. */
    int c;

    /* Zeiger auf die zu öffnende Datei. */
    FILE *f;

    /* Prüft, ob genau ein Dateiname als Argument übergeben wurde. */
    if (argc != 2) {
        /* Gibt die richtige Programmnutzung aus. */
        usage(argv[0]);

        /* Beendet das Programm mit Fehlercode 1. */
        return 1;
    }

    /* Öffnet die angegebene Datei im Lesemodus ("r"). */
    f = fopen(argv[1], "r");

    /* Prüft, ob die Datei erfolgreich geöffnet wurde. */
    if (f == NULL) {
        /* Gibt eine Fehlermeldung aus und beendet das Programm. */
        err_and_out("Could not open file");
    }

    /* Liest die Datei Zeichen für Zeichen bis zum Dateiende (EOF). */
    while ((c = fgetc(f)) != EOF) {
        /* 
         *  Wandelt das gelesene Zeichen in einen Großbuchstaben um
         *  und gibt es direkt auf der Konsole aus.
         */
        putchar(toupper(c));
    }
    return 0;
}
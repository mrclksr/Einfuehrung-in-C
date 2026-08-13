#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Erzeugt eine temporäre Datei basierend auf einem Namensschema.
 * 
 * @param buffer      Ein bereitgestellter Puffer, in dem der neue Dateiname gespeichert wird.
 * @param buffer_size Die Größe des bereitgestellten Puffers.
 * @param filename    Der Basis-Dateiname (z.B. "testfile").
 * @return            Ein FILE-Pointer auf die geöffnete Datei, oder NULL bei Fehler.
 */
FILE* create_temp_file(char *buffer, size_t buffer_size, const char *filename) {
    // 1. Das Template in den Puffer schreiben.
    // mkstemp benötigt zwingend das Suffix "XXXXXX".
    // snprintf stellt sicher, dass wir den Puffer nicht überschreiten.
    int written = snprintf(buffer, buffer_size, "%sXXXXXX", filename);

    // Fehlerprüfung: Wenn der Name abgeschnitten wurde oder ein Fehler auftrat
    if (written < 0 || (size_t)written >= buffer_size) {
        fprintf(stderr, "Fehler: Puffer zu klein für den Dateinamen.\n");
        return NULL;
    }

    // 2. mkstemp aufrufen. 
    // Dies erstellt die Datei mit zufälligem Namen und öffnet sie.
    // Der Puffer wird von mkstemp modifiziert!
    int fd = mkstemp(buffer);

    if (fd == -1) {
        perror("mkstemp fehlgeschlagen");
        return NULL;
    }

    // 3. Den Datei-Deskriptor (int) in einen FILE-Pointer umwandeln.
    // "w+" öffnet die Datei zum Lesen und Schreiben (erstellt sie, falls nicht vorhanden).
    FILE *fp = fdopen(fd, "w+");

    if (fp == NULL) {
        perror("fdopen fehlgeschlagen");
        close(fd); // Deskriptor schließen, falls fdopen fehlschlägt
        return NULL;
    }

    return fp;
}

int main() {
    // Der Puffer muss groß genug sein: Basisname + "XXXXXX" + Nullterminator
    char name_buffer[256];
    const char *base_name = "meine_datei_";

    FILE *file = create_temp_file(name_buffer, sizeof(name_buffer), base_name);

    if (file != NULL) {
        printf("Erfolgreich erstellt: %s\n", name_buffer);

        // Test: Etwas in die Datei schreiben
        fprintf(file, "Hallo, das ist eine temporäre Datei!\n");

        // Datei wieder zum Lesen zurücksetzen (optional)
        rewind(file);
        char line[100];
        if (fgets(line, sizeof(line), file)) {
            printf("Inhalt der Datei: %s", line);
        }

        // Datei schließen
        fclose(file);
        printf("Datei wurde geschlossen.\n");
    } else {
        printf("Fehler beim Erstellen der Datei.\n");
    }

    return 0;
}

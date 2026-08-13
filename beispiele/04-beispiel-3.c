// ========================================================================
// DYNAMISCHES SPEICHERVERGRÖSSERN MIT realloc()
// ========================================================================
// Dieses Programm zeigt, wie man einen dynamischen Array im Heap
// schrittweise vergrößert, ohne die bereits gespeicherten Daten zu verlieren.
// Es ist ein primitives Beispiel für eine "wachsende Liste" (wie std::vector
// in C++ oder list in Python).

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // Enthält size_t (standardmäßig oft schon eingebunden, 
                    // aber explizit zu includieren ist beste Praxis)

int main(void) {
    // ------------------------------------------------------------------
    // VARIABLENDEFINITION
    // ------------------------------------------------------------------
    int *data = NULL;        // Zeiger auf den dynamischen Speicherbereich
    size_t capacity = 0;     // Wie viel PLATZ (in Elementen) ist aktuell reserviert?
    size_t count = 0;        // Wie viele ELEMENTE sind tatsächlich belegt?
    size_t element_size = sizeof(int); // Größe eines einzelnen Elements in Bytes
    size_t new_capacity;     // Variable für die zukünftige Kapazität

    // size_t ist ein vorzeichenloser Integer-Typ, der speziell für 
    // Größen, Indizes und Speichermessungen gedacht ist. Er kann nie negativ werden,
    // was versehentliche Logikfehler verhindert.

    // ------------------------------------------------------------------
    // INITIALE SPEICHERZUTEILUNG
    // ------------------------------------------------------------------
    // Wir starten mit einer kleinen Kapazität (3 Integers).
    // malloc() reservert den Speicher, aber füllt ihn NICHT mit Nullen.
    capacity = 3;
    data = malloc(capacity * element_size);

    // WICHTIG: Immer auf Fehlschlag prüfen! malloc() kann NULL zurückgeben,
    // wenn der Speicher erschöpft ist oder der Request zu groß ist.
    if (data == NULL && capacity > 0) {
        fprintf(stderr, "Fehler: Initiale Speicherzuteilung fehlgeschlagen.\n");
        return EXIT_FAILURE; // Programm wird mit Fehlercode 1 beendet
    }

    printf("Initial reserviert: %zu Bytes (%zu Elemente)\n", 
           capacity * element_size, capacity);

    // ------------------------------------------------------------------
    // DATEN HINZUFÜGEN & DYNAMISCH VERGRÖSSERN
    // ------------------------------------------------------------------
    // Wir wollen 11 Werte (0 bis 10) speichern. Da unsere Startkapazität
    // nur 3 beträgt, muss der Speicher mehrmals vergrößert werden.
    for (int i = 0; i < 11; i++) {

        // Prüfen, ob der aktuelle Speicherplatz noch ausreicht
        if (count == capacity) {
            // Der Array ist voll. Wir vergrößern ihn um 50% (hier als Beispiel).
            // In der Praxis wird oft verdoppelt (capacity * 2), was amortisiert
            // effizienter ist (O(1) pro Einfügung im Durchschnitt).
            new_capacity = capacity + (capacity / 2);

            // realloc() kann den Speicherelement an eine NEUE Adresse 
            // verschieben, wenn der vorhandene Block nicht vergrößert 
            // werden kann. Daher darf man den alten Zeiger NICHT direkt 
            // überschreiben, bevor man den Erfolg prüft!
            
            int *temp = realloc(data, new_capacity * element_size);

            // Falls realloc() fehlschlägt, gibt es NULL zurück.
            // WICHTIG: Der ALTE Speicher (data) bleibt weiterhin gültig 
            // und muss später noch freigegeben werden! Man darf ihn 
            // nicht einfach free() aufrufen, sonst verliert man den 
            // Zugriff auf bereits gespeicherte Daten.
            if (temp == NULL) {
                fprintf(stderr, "Fehler: Reallokation bei Index %d fehlgeschlagen.\n", i);
                fprintf(stderr, "Hinweis: Der bereits allokierte Speicher ist noch gültig.\n");
                
                // Aufräumen, bevor das Programm abbricht
                free(data);
                return EXIT_FAILURE;
            }

            // Nur wenn temp != NULL ist, aktualisieren wir den Hauptzeiger.
            data = temp;
            capacity = new_capacity; // Kapazität auf den neuen Wert aktualisieren

            printf("[INFO] Speicher vergrößert auf %zu Elemente (%zu Bytes)\n", 
                   new_capacity, new_capacity * element_size);
        }

        // ------------------------------------------------------------------
        // DATEN SCHREIBEN & ZEIGER AKTUALISIEREN
        // ------------------------------------------------------------------
        // Jetzt ist Platz. Wir schreiben den Wert an die freie Position.
        data[count] = i;
        count++; // Nur die tatsächlich genutzte Anzahl hochzählen
    }

    // ------------------------------------------------------------------
    // AUSGABE DER WERTE
    // ------------------------------------------------------------------
    printf("\n%zu Werte erfolgreich gespeichert:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  data[%zu] = %d\n", i, data[i]);
    }

    // ------------------------------------------------------------------
    // SPEICHER FREIGEBEN (MEMORY CLEANUP)
    // ------------------------------------------------------------------
    // Am Ende jedes Programms sollte allokierten Heap-Speicher freigeben.
    // free(NULL) ist in C sicher und hat keine Auswirkung.
    free(data);
    data = NULL; // Gute Praxis: Zeiger nach dem Freigeben auf NULL setzen,
                 // um "dangling pointers" (verwaiste Zeiger) zu vermeiden.

    printf("\nSpeicher sicher freigegeben. Programm beendet.\n");
    return EXIT_SUCCESS;
}
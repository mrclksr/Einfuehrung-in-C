/*
 * DATEI: 02-beispiel-5.c
 * ZWECK: Dieses Programm generiert einen zufälligen Spitznamen, indem es 
 *        ein zufälliges Adjektiv mit einem zufälligen Tiernamen kombiniert.
 */

#include <stdio.h>  // Standard-Ein-/Ausgabe-Bibliothek (für printf)
#include <stdlib.h> // Standard-Bibliothek (für rand und srand)
#include <time.h>   // Zeit-Bibliothek (um den Zufallsgenerator zu beeinflussen)

int main() {
    // Ein Array von Zeigern auf Zeichenketten (Strings).
    // 'const' bedeutet, dass der Inhalt dieser Wörter im Programm nicht verändert werden darf.
    const char *adjectives[] = {
        "eager", "brave", "sleepy", "clever", "mighty", 
        "happy", "lazy", "swift", "calm", "wild"
    };

    // Ein weiteres Array mit Tiernamen.
    const char *animals[] = {
        "Squirrel", "Panda", "Tiger", "Owl", "Fox", 
        "Rabbit", "Koala", "Wolf", "Eagle", "Otter"
    };

    /* 
     * TRICK: Berechnung der Anzahl der Elemente in einem Array.
     * sizeof(adjectives) gibt die gesamte Speichergröße des Arrays in Bytes zurück.
     * sizeof(adjectives[0]) gibt die Größe eines einzelnen Elements (eines Zeigers) zurück.
     * Wenn man die Gesamtgröße durch die Größe eines Elements teilt, erhält man die Anzahl der Einträge.
     */
    int num_adjectives = sizeof(adjectives) / sizeof(adjectives[0]);
    int num_animals = sizeof(animals) / sizeof(animals[0]);


    /*
     * srand(time(NULL)) initialisiert den Zufallszahlengenerator.
     * Der Computer kann eigentlich keinen "echten" Zufall erzeugen, sondern nutzt eine Formel.
     * Wenn wir den Generator immer mit derselben Zahl starten würden, bekämen wir jedes Mal 
     * die gleiche "zufällige" Folge. 
     * time(NULL) liefert die aktuelle Systemzeit (als Sekunden seit 1970). 
     * Da sich die Zeit ständig ändert, ist der Startwert für unseren Zufall immer anders.
     */
    srand(time(NULL));

    /*
     * rand() erzeugt eine sehr große Zufallszahl.
     * Der Modulo-Operator (%) berechnet den Rest einer Division.
     * 'rand() % num_adjectives' sorgt dafür, dass das Ergebnis immer eine Zahl 
     * zwischen 0 und (num_adjectives - 1) ist. 
     * Das ist perfekt, um einen gültigen Index für unser Array zu erhalten.
     */
    int random_adj = rand() % num_adjectives;
    int random_ani = rand() % num_animals;

    /*
     * printf gibt den Text auf dem Bildschirm aus.
     * %s ist ein Platzhalter für einen String (eine Zeichenkette).
     * Hier werden zwei Strings hintereinander ausgegeben:
     * das Adjektiv am Index 'random_adj' und das Tier am Index 'random_ani'.
     * \n sorgt für einen Zeilenumbruch am Ende.
     */
    printf("Your new nickname is: %s%s\n", adjectives[random_adj], animals[random_ani]);

    // Das Programm beendet sich erfolgreich.
    return 0;
}

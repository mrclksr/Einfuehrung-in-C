#include <stdio.h>
/* Enthält die Funktion atoi(), die Text in eine Zahl umwandelt*/
#include <stdlib.h>

/*
 * Diese Funktion gibt dem Benutzer eine Hilfe aus.
 *
 * Der Parameter "progname" enthält den Namen des Programms
 * (z.B. "./summe"). Dieser wird automatisch von main()
 * über argv[0] übergeben.
 * 
 * Es ist Konvention, dass Argumente und Optionen, die
 * optional sind, in [] eingeschlossen werden.
 */
void usage(const char *progname)
{
    /*
     * Beispiel:
     * Usage: ./summe num1 [num2] [...]
     */
    printf("Usage: %s num1 [num2] [...]\n", progname);
}

/*
 * argc = Anzahl der Kommandozeilenargumente
 * argv = Array mit den einzelnen Argumenten
 *
 * Beispiel:
 *
 * Aufruf:
 * ./summe 10 20 30
 *
 * Dann gilt:
 *
 * argc = 4
 *
 * argv[0] = "./summe"
 * argv[1] = "10"
 * argv[2] = "20"
 * argv[3] = "30"
 */
int main(int argc, char *argv[])
{
    /*
     * Hier wird eine Ganzzahl namens "sum" angelegt.
     * Sie speichert später die Summe aller Zahlen.
     *
     * Anfangswert: 0
     */
    int sum = 0;

    /*
     * Prüfen, ob genügend Argumente übergeben wurden.
     *
     * argc ist mindestens 1, weil argv[0]
     * immer den Programmnamen enthält.
     *
     * Wenn argc kleiner als 2 ist,
     * wurden weniger als eine Zahle angegeben.
     *
     */
    if (argc < 2) {
        /* Hilfe anzeigen. */
        usage(argv[0]);
        /* Programm mit Fehlercode 1 beenden. */
        return 1;
    }

    /*
     * Schleife über alle übergebenen Zahlen.
     *
     * i beginnt bei 1, weil argv[0]
     * der Programmname ist.
     *
     * Die Schleife läuft solange,
     * bis alle Argumente verarbeitet wurden.
     */
    for (int i = 1; i < argc; i++) {

        /*
         * argv[i] ist ein Text (String).
         *
         * Beispiel:
         * argv[i] = "25"
         *
         * atoi() wandelt diesen Text
         * in eine Ganzzahl um.
         *
         * Ergebnis:
         * atoi("25") -> 25
         */
        sum += atoi(argv[i]);
    }

    /*
     * Nach der Schleife enthält "sum"
     * die Summe aller eingegebenen Zahlen.
     *
     * %d ist der Platzhalter für eine Ganzzahl.
     */
    printf("Sum: %d\n", sum);

    return (0);
}
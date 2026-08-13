//////////////////////////////////////////////////////////////////////////////
// Dieses Programm demonstriert die Verarbeitung von Kommandozeilenargumenten
// unter C. Wenn du die Datei kompiliert ausführst, kannst du ihr Befehle
// wie `-n Max -a 25 -v` mitgeben. Das Programm liest diese, speichert die
// Werte und gibt sie am Ende aus.
//
// WICHTIGE BEGRIFFE (Merken für später!):
// • argc (argument count)   : Integer, der zählt, wie viele Argumente übergeben wurden
// • argv (argument vector)  : Array von Strings, die die Argumente enthalten
//   → argv[0] ist immer der Programmname
//   → argv[1], argv[2], ... sind die eigentlichen Parameter
// • getopt()               : Eine POSIX-Funktion (Linux/macOS/WSL), die Argumente automatisch auswertet
// • optarg                 : Enthält den Wert hinter einer Option (z.B. der String nach -n)
// • atoi()                 : Wandelt einen String in eine Ganzzahl (int) um
// • stderr                 : Standard-Fehlerausgabestrom. Fehler werden hier hingeleitet,
//                            damit sie sich nicht mit der normalen Programm-Ausgabe (stdout) mischen.
// • EXIT_SUCCESS / EXIT_FAILURE : Standard-Rückgabewerte (0 = Erfolg, 1 = Fehler)

#include <stdio.h>  // Standardbibliothek für Ein-/Ausgabe (printf, fprintf, etc.)
#include <stdlib.h> // Allgemeine Funktionen (atoi, EXIT_SUCCESS, EXIT_FAILURE, malloc, etc.)
#include <string.h> // String-Funktionen (hier nicht direkt genutzt, aber oft in Projekten dabei)
#include <unistd.h> // POSIX-Kompatibilität. Enthält insbesondere getopt(), sleep(), etc.
//////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------
// MAIN-FUNKTION
// ------------------------------------------------------------------------
// int main(int argc, char *argv[])
// ist die Standardeinstiegsmethode für C-Programme.
// ------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    
    // ----------------------------------------------------------
    // STANDARDEINSTELLUNGEN (DEFAULTS) FESTLEGEN
    // ----------------------------------------------------------
    // Bevor wir die Benutzereingaben auslesen, definieren wir Werte, die
    // verwendet werden, falls der Benutzer nichts angibt.
    char *name = "Unknown";    // String-Zeiger: Zeigt auf den Text "Unknown"
    int age = 0;               // Integer: Falls kein Alter angegeben wird
    int verbose = 0;           // 0 = deaktiviert, 1 = aktiviert (Bool-Äquivalent)
    int opt;                   // Variable: Speichert das aktuelle "Flag" von getopt()

    // ----------------------------------------------------------
    // OPTIONEN PARSEN MIT getopt()
    // ----------------------------------------------------------
    // while ((opt = getopt(argc, argv, "n:a:vh")) != -1)
    //
    // getopt() durchläuft argv[] von links nach rechts.
    // Der String "n:a:vh" definiert die erwarteten Optionen:
    //   "n:"  → -n erwartet einen Wert (z.B. -n Max)
    //   "a:"  → -a erwartet einen Wert (z.B. -a 25)
    //   "v"   → -v ist ein Flag (kein Wert nötig, z.B. nur -v)
    //   "h"   → -h ist ein Flag (z.B. nur -h)
    //
    // WICHTIG: Ein ":" nach dem Buchstaben bedeutet, dass eine Option
    //          einen Wert erfordert. Ohne ":" ist sie ein reines Flag.
    //
    // optarg ist eine globale Variable von getopt, die automatisch den
    // hinter der Option stehenden String enthält (falls nötig).
    //
    // getopt() gibt den Buchstaben der aktuellen Option zurück.
    // Sobald alle Optionen durchgelaufen sind, gibt es -1 zurück.
    while ((opt = getopt(argc, argv, "n:a:vh")) != -1) {
        // ------------------------------------------------------
        // AUSWERTUNG DER EINZELNEN OPTIONEN (switch/case)
        // ------------------------------------------------------
        switch (opt) {
            // --------------------------------------------------
            case 'n':  // Option: -n <Name>
                // optarg enthält den String direkt hinter -n
                name = optarg;  // Überschreibe den Default-Namen
                
                // Wenn Verbose-Modus aktiv ist, gib eine Debug-Meldung aus
                // [V] steht für "Verbose", um solche Meldungen leicht zu erkennen
                if (verbose) printf("[V] Name set to '%s'\n", name);
                break; // Verlässt die switch-Block, springt zurück zur while-Bedingung
            // --------------------------------------------------
            case 'a':  // Option: -a <Alter>
                // atoi() wandelt den String (optarg) in eine Ganzzahl um
                // Achtung: atoi() ist einfach und macht keine robuste Fehlerprüfung.
                // Für Produktionscode wäre strtol() besser.
                age = atoi(optarg);
                
                // Logische Validierung: Ein negatives Alter macht keinen Sinn
                if (age < 0) {
                    // fprintf(stderr, ...) sendet die Nachricht an die Fehlerausgabe,
                    // damit sie sich nicht mit normalem Programm-Output mischt.
                    fprintf(stderr, "Error: Age cannot be negative\n");
                    return EXIT_FAILURE; // Beende das Programm sofort mit Fehlerstatus (Code 1)
                }
                
                if (verbose) printf("[V] Age set to %d\n", age);
                break;

            // --------------------------------------------------
            case 'v':  // Option: -v (Verbose/Debug-Modus)
                verbose = 1; // Aktiviere den Modus
                printf("Verbose mode enabled.\n");
                break;

            // --------------------------------------------------
            case 'h':  // Option: -h (Hilfe anzeigen)
                // argv[0] ist der Name, unter dem das Programm aufgerufen wurde
                printf("Usage: %s [OPTIONS]\n", argv[0]); 
                printf("Options:\n");
                printf("  -n <name>   Person's name (default: Unknown)\n");
                printf("  -a <age>    Person's age (default: 0)\n");
                printf("  -v          Enable verbose/debug output\n");
                printf("  -h          Show this help message\n");
                
                // Eine Hilfedarstellung ist eine "beendende Aktion".
                // Kein weiterer Programmcode soll nach der Hilfe laufen.
                return EXIT_SUCCESS; // Beende erfolgreich (Code 0)

            // --------------------------------------------------
            case '?':  // Ungültige oder unbekannte Option
                // getopt() gibt '?' zurück, wenn:
                // • Der Benutzer eine Option eingibt, die wir nicht kennen (z.B. -z)
                // • Eine Option, die einen Wert erwartet, keinen Wert hat (z.B. -n ohne Argument)
                // Fehlermeldungen von getopt() werden automatisch auf stderr ausgegeben.
                return EXIT_FAILURE;

            // --------------------------------------------------
            default:   // Sollte hier niemals eintreten
                // Dient als Sicherheitsnetz. Falls etwas Unerwartetes passiert,
                // wird das Programm sauber beendet.
                fprintf(stderr, "Unexpected error during option parsing.\n");
                return EXIT_FAILURE;
        } // Ende von switch
    } // Ende von while (getopt-Laufzeit)

    // ----------------------------------------------------------
    // AUSGABE DER GEPARSERTE WERTE
    // ----------------------------------------------------------
    printf("\n--- Parsed Values ---\n");
    printf("Name  : %s\n", name);
    printf("Age   : %d\n", age);
    
    // Bedingter Operator (Ternary Operator):
    // (bedingung) ? wert_fuer_wahr : wert_fuer_falsch
    // verbose ist 0 oder 1, also testen wir, ob er ungleich 0 ist.
    printf("Verbose: %s\n", verbose ? "true" : "false");

    // ----------------------------------------------------------
    // PROGRAMM BEENDEN
    // ----------------------------------------------------------
    return EXIT_SUCCESS; // 0 = Erfolgreiche Ausführung (wird an das Betriebssystem zurückgegeben)
} // Ende von main

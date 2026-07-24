/* 
 * Programm: Passwort-Prüfer
 * Zweck: Dieses Programm fragt den Benutzer nach einem Kennwort 
 *        und vergleicht es mit einem fest hinterlegten Wert.
 */

#include <stdio.h>  // Bibliothek für Ein- und Ausgaben (z.B. printf, fgets)
#include <string.h> // Bibliothek für String-Operationen (z.B. strlen, strcmp)

// Ein konstantes Zeichenfeld (String), das das richtige Passwort enthält.
// 'const' bedeutet, dass dieser Wert im Programmverlauf nicht mehr geändert werden kann.
const char secret[] = "cdemy";

int main()
{
    // Ein Array (Puffer), um die Eingabe des Benutzers zu speichern.
    // 128 Bytes Platz bieten genug Raum für ein längeres Wort.
    char eingabe[128];

    // Den Benutzer auffordern, etwas einzugeben
    printf("Wie lautet das Kennwort? ");

    /* 
     * fgets liest eine Zeile Text ein.
     * Parameter 1: 'eingabe' -> Wohin der Text geschrieben wird.
     * Parameter 2: 'sizeof(eingabe)' -> Wie viel Platz wir haben (verhindert Überläufe/Sicherheitslücken).
     * Parameter 3: 'stdin' -> Die Standard-Eingabe (Tastatur).
     * Wenn fgets fehlschlägt (z.B. durch einen Lesefehler), gibt es NULL zurück.
     */
    if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
        printf("Ein Fehler ist aufgetreten\n");
        return (1); // Beendet das Programm mit dem Fehlercode 1
    }

    // Wir ermitteln die Länge der eingegebenen Zeichenkette.
    int len = strlen(eingabe);

    /* 
     * WICHTIG: fgets liest das "Enter"-Zeichen (\n) am Ende der Eingabe mit ein!
     * Wenn der User "test" + Enter drückt, speichert das Programm "test\n".
     * Da unser Passwort "cdemy" kein "\n" am Ende hat, würde der Vergleich scheitern.
     * Dieser Block prüft, ob das letzte Zeichen ein '\n' ist, und ersetzt es durch 
     * das Null-Zeichen '\0' (das Ende eines Strings in C).
     */
    if (len > 0 && eingabe[len - 1] == '\n') {
        eingabe[len - 1] = '\0';
    }

    /* 
     * strcmp vergleicht zwei Strings.
     * Wenn die Strings identisch sind, gibt die Funktion 0 zurück.
     */
    if (strcmp(eingabe, secret) == 0) {
        printf("Treffer!\n");
    } else {
        printf("Das war wohl nichts\n");
        return (1); // Beendet das Programm mit Fehlercode 1, da Passwort falsch
    }

    return (0); // Programm erfolgreich beendet
}

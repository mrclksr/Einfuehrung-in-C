/*
 * Binde die Standard-Eingabe/Ausgabe-Bibliothek ein. Diese wird für printf(),
 * fgets(), puts() und andere Ein-/Ausgabefunktionen benötigt.
 */
#include <stdio.h>

/*
 * Binde die String-Bibliothek ein. Diese wird für Funktionen wie strlen(),
 * strcmp(), strncpy(), strcspn() benötigt.
 */
#include <string.h>

int main() {

  /*
   * Deklariere ein zweidimensionales Array 'strings', das bis zu 128 Strings
   * speichern kann. Jeder String darf maximal 63 Zeichen lang sein (plus 1
   * Byte für das abschließende '\0'). Das entspricht einem "Tabelle" mit
   * 128 Zeilen und je 64 Spalten (Bytes).
   */
  char strings[128][64];

  /*
   * Deklariere ein Array 'input' mit Platz für 64 Zeichen.
   * Darin wird die aktuelle Benutzereingabe zwischengespeichert.
   */
  char input[64];

  /*
   * Deklariere und initialisiere die Variable 'string_counter' mit 0.
   * Diese zählt, wie viele Strings der Benutzer bereits eingegeben hat.
   */
  int string_counter = 0;

  /*
   * Starte eine do-while-Schleife.
   * Der Schleifenrumpf wird mindestens einmal ausgeführt, bevor die
   * Bedingung geprüft wird.
   */
  do {
    printf("Text eingeben (\"ende\" zum beenden): ");

    /*
     * Lies eine Zeile von der Standardeingabe (Tastatur) in das Array 'input'.
     * 'sizeof(input)' sorgt dafür, dass maximal 63 Zeichen gelesen werden
     * (plus '\0').
     * Falls fgets() NULL zurückgibt (z.B. bei Fehler oder Strg+D), wird die
     * Schleife abgebrochen.
     */
    if (fgets(input, sizeof(input), stdin) == NULL) {
      /*
       * I/O-Error oder ^D eingegeben.
       * 'break' verlässt die do-while-Schleife sofort.
       */
      break;
    }
    /*
     * Ermittle die Position des ersten Zeilenumbruchs ('\n') oder des
     * String-Endes ('\0'). strcspn() gibt den Index des ersten Zeichens aus
     * dem String "\n" zurück, das in 'input' gefunden wird.
     */
    size_t n = strcspn(input, "\n");

    /*
     * Überschreibe das Zeichen an Position 'n' mit '\0' (String-Terminator).
     * Damit wird ein eventuell vorhandener Zeilenumbruch entfernt und der
     * String sauber terminiert.
     */
    input[n] = '\0';

    /*
     * Vergleiche den eingegebenen String mit "ende".
     * strcmp() liefert 0, wenn beide Strings identisch sind.
     */
    if (strcmp(input, "ende") == 0) {
      /*
       * Falls der Benutzer "ende" eingegeben hat, verlasse die
       * Eingabeschleife.
       */
      break;
    }

    /*
     * Kopiere maximal 63 Zeichen aus 'input' in das aktuelle Element
     * von 'strings'. 'string_counter' gibt an, in welche Zeile (welchen
     * String) kopiert wird. Das letzte Byte bleibt für '\0' reserviert,
     * daher 63 statt 64.
     */
    strncpy(strings[string_counter], input, 63);

    /* Erhöhe den Zähler für die Anzahl der gespeicherten Strings um 1. */
    string_counter++;

    /*
     * Wiederhole die Schleife, solange weniger als 128 Strings eingegeben
     * wurden. Dadurch wird verhindert, dass das Array 'strings' überläuft.
     */
  } while (string_counter < 128);

  /*
   * Starte eine for-Schleife, um alle eingegebenen Strings nacheinander zu
   * verarbeiten. 'i' läuft von 0 bis string_counter-1 (also über alle ge-
   * speicherten Strings).
   */
  for (int i = 0; i < string_counter; i++) {
    /*
     * Deklariere ein lokales Array 'buf' mit Platz für 64 Zeichen.
     * Darin wird der umgekehrte String zwischengespeichert.
     */
    char buf[64];

    /*
     * Ermittle die Länge des aktuellen Strings (ohne '\0') und speichere
     * sie in 'len'.
     */
    size_t len = strlen(strings[i]);

    /*
     * Starte eine innere for-Schleife, die über jedes Zeichen des aktuellen
     * Strings läuft. 'j' ist der Index im neuen (umgedrehten) String.
     */
    for (int j = 0; j < len; j++) {
      /*
       * Kopiere das Zeichen von hinten nach vorne:
       * strings[i][len - j - 1] ist das Zeichen von hinten (beginnend beim
       * letzten).
       * buf[j] ist die aktuelle Position im neuen String (von vorne beginnend).
       * Beispiel: Bei "Hallo" (len=5) wird bei j=0: buf[0] = strings[i][4] =
       * 'o'.
       */
      buf[j] = strings[i][len - j - 1];
    }

    /*
     * Setze am Ende des neuen Strings den Terminator '\0', damit es ein
     * gültiger C-String ist.
     */
    buf[len] = '\0';

    /*
     * Gib den umgedrehten String gefolgt von einem Zeilenumbruch auf dem
     * Bildschirm aus.
     */
    puts(buf);
  }
  return 0;
}
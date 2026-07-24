/* Bindet die Standard-Ein-/Ausgabebibliothek ein (für printf, fgets usw.) */
#include <stdio.h>

/* Bindet Funktionen zur Stringverarbeitung ein (z. B. strlen) */
#include <string.h>

int main() {
  /* Legt ein Zeichenarray (String) mit Platz für 128 Zeichen an */
  char input[128];
  /* Zähler für gefundene Vokale, wird mit 0 initialisiert */
  int vowels = 0;

  printf("Text eingeben: ");

  /*
   * Liest eine Zeile vom Benutzer ein:
   *  - input: Speicherort für die Eingabe
   *  - sizeof(input): maximale Anzahl der zu lesenden Zeichen (Schutz
   *    vor Überlauf)
   *  - stdin: Eingabequelle (Tastatur)
   * Wenn NULL zurückgegeben wird, ist ein Fehler oder EOF aufgetreten
   */
  if (fgets(input, sizeof(input), stdin) == NULL) {
    /* I/O-Error oder ^D. Programm wird mit Fehlercode 1 beendet */
    return (1);
  }

  /* Bestimmt die Länge des eingegebenen Strings (ohne '\0') */
  size_t len = strlen(input);

  /* Schleife durchläuft jedes Zeichen im String */
  for (int i = 0; i < len; i++) {
    /* Prüft das aktuelle Zeichen input[i] */
    switch (input[i]) {
    case 'a': /* Falls das Zeichen ein 'a' ist */
    case 'e': /* oder 'e' */
    case 'i': /* oder 'i' */
    case 'o': /* oder 'o' */
    case 'u': /* oder 'u' */
    case 'A': /* etc.     */
    case 'E':
    case 'I':
    case 'O':
    case 'U':
      vowels++; /* Zähler für Vokale wird erhöht */
      break;    /* Beendet den switch-Block für diesen Durchlauf */
    }
  }

  /* Gibt die Anzahl der gefundenen Vokale aus */
  printf("%d Vokale gefunden\n", vowels);

  return (0);
}
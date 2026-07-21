/*
 * Bindet die Standard-Eingabe/Ausgabe-Bibliothek ein.
 * Diese Bibliothek brauchen wir, damit wir z. B. printf() verwenden können.
 */
#include <stdio.h>

int main() {
  /*
   * Variable für die Summe über alle Zahlen in der Matrix.
   * Wir starten mit 0, weil noch keine Werte addiert wurden.
   */
  int sum = 0;

  /*
   * Hier wird eine 2D-Matrix (Tabelle) mit 4 Zeilen und 4 Spalten erstellt.
   * 2D-Array bedeutet: Array von Arrays.
   * Man kann es sich wie eine kleine Tabelle vorstellen.
   */
  int matrix[4][4] = {
      {1, 2, 2, 3}, /* Zeile 1 */
      {3, 5, 2, 1}, /* Zeile 2 */
      {7, 3, 4, 8}, /* Zeile 3 */
      {6, 1, 6, 9}  /* Zeile 4 */
  };

  /*
   * Äußere Schleife: läuft durch alle Zeilen der Matrix.
   * i ist der Zeilen-Index.
   */
  for (int i = 0; i < 4; i++) {
    /*
     * Innere Schleife: läuft durch alle Spalten einer Zeile.
     * j ist der Spalten-Index.
     */
    for (int j = 0; j < 4; j++) {
      /*
       * Addiere den aktuellen Wert aus der Matrix zur Gesamtsumme hinzu.
       * matrix[i][j] bedeutet:
       *  - i = Zeile
       *  - j = Spalte
       * Beispiel: matrix[0][0] ist der erste Wert: 1
       */
      sum += matrix[i][j];
    }
  }
  printf("Summe: %d\n", sum);

  return (0);
}
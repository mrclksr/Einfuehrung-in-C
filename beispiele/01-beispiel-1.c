/*
 * Binde stdio.h für Standard-I/O-Funktionen wie printf()
 * und scanf() ein.
 */
#include <stdio.h>

/*
 * Wir definieren main() ohne Parameter, da wir die Befehls-
 * zeile nicht nutzen.
 */
int main() {
  int emotion, retval;

  /* Gib ein Menü aus */
  printf("Emoji Selector\n");
  printf("==============\n");
  printf("Please choose an emotion/action\n");
  printf("1. Grinning\n");
  printf("2. Grinning with smiling eyes\n");
  printf("3. Tears of joy\n");
  printf("4. Smiling with heart eyes\n");
  printf("5. Wry smile\n");
  printf("6. Crying\n");
  printf("7. Pouting\n");
  printf("Your choice: ");

  /*
   * Wir speichern den Rückgabewert von scanf() in retval,
   * sodass wir auf ungültige Eingaben und Fehler reagieren
   * können.
   */
  retval = scanf("%d", &emotion);

  /*
   * Wir benutzen hier eine Programmiertechnik, die man
   * early return (auch crash early) nennt.
   * Wir prüfen erst auf etwaige Fehler. Wenn ein Fehler
   * erkannt wird, beenden wir das Programm. Das macht den
   * Code besser lesbar, da wir den Fehlertest-Teil aus dem
   * Weg haben und wir uns somit nur auf die Programmlogik
   * konzentrieren können, ohne Fehlerprüfungen dazwischen.
   */
  if (retval == 0) {
    /*
     * scanf() konnte uns keine Ganzzahl aus der Benutzer-
     * eingabe machen, weil etwa Buchstaben oder Sonder-
     * zeichen eingegeben wurden.
     */
    printf("Error: Invalid input. Only numbers are allowed\n");
    /*
     * Mit return verlassen wir eine Funktion. Wenn main()
     * verlassen wird, endet das Programm. Wir geben 1 zurück,
     * um dem Aufrufer zu signalisieren, dass unser Programm
     * nicht erfolgreich war. Bei der Wahl des Rückgabewerts
     * sind wir frei. Es gibt aber die Konvention 0 bei Erfolg
     * und einen Wert ungleich 0 bei einem Fehler zurückzugeben.
     */
    return (1);
  }
  /*
   * EOF = End Of File. Das ist eine Konstante aus stdio.h mit
   * der Standard-I/O-Funktionen signalisieren, dass das Ende
   * einer Datei erreicht wurde.
   */
  if (retval == EOF) {
    printf("Error: Input error occurred\n");
    /* Gib -1 zurück, um einen I/O-Fehler zu signalisieren. */
    return (-1);
  }
  /*
   * Wenn wir hier sind, haben wir eine ganze Zahl in emotion
   * gespeichert, die der/die User/in eingegeben hat.
   */
  if (emotion == 1) {
    printf("😺\n");
  } else if (emotion == 2) {
    printf("😸\n");
  } else if (emotion == 3) {
    printf("😹\n");
  } else if (emotion == 4) {
    printf("😻\n");
  } else if (emotion == 5) {
    printf("😼\n");
  } else if (emotion == 6) {
    printf("😿\n");
  } else if (emotion == 7) {
    printf("😾\n");
  } else {
    printf("Invalid choice\n");
    return (1);
  }
  return (0);
}

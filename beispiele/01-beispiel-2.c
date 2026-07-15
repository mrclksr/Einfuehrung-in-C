#include <stdio.h>

/*
 * Statt direkt mit den Zahlen zu arbeiten, nutzen wir
 * Konstanten. Das hat drei Vorteile:
 *
 * 1. Es macht unseren Code expressiver.
 * 2. Wir können leichter die Emojis den Zahlen zuordnen und
 *    reduzieren die Wahrscheinlichkeit für Tippfehler. Schreiben
 *    wir eine Konstante falsch, gibt es einen Compilerfehler.
 * 3. Sollten wir die Zahlen ändern wollen, müssen wir nur die Werte
 *    der Konstanten ändern. Der Rest des Codes bleibt unberührt.
 *
 * Wir hätten die Konstanten auch in main() definieren können statt
 * sie global zu deklarieren. Konstanten werden häufig global angelegt,
 * da sie so programmweit genutzt werden können. Sollen Werte geändert
 * werden, muss man nicht den ganzen Code durchsuchen.
 */
const int grinning = 1;
const int smiling_eyes = 2;
const int tears_of_joy = 3;
const int heart_eyes = 4;
const int wry_smile = 5;
const int crying = 6;
const int pouting = 7;

int main() {

  int emotion, retval;

  /*
   * Statt für jede Zeile printf() aufzurufen, fassen wir alle Zeilen
   * in einem Aufruf zusammen. Der Compiler macht darauf eine lange
   * Zeichenkette. Die Leerzeichen ausserhalb der "" werden ignoriert.
   */
  printf("Emoji Selector\n"
         "==============\n"
         "Please choose an emotion/action\n"
         "%d. Grinning\n"
         "%d. Grinning with smiling eyes\n"
         "%d. Tears of joy\n"
         "%d. Smiling with heart eyes\n"
         "%d. Wry smile\n"
         "%d. Crying\n"
         "%d. Pouting\n"
         "Your choice: ",
         grinning, smiling_eyes, tears_of_joy, heart_eyes, wry_smile, crying,
         pouting);

  retval = scanf("%d", &emotion);

  if (retval == 0) {
    printf("Error: Invalid input. Only numbers are allowed\n");
    return (1);
  }
  if (retval == EOF) {
    printf("Error: Input error occurred\n");
    return (-1);
  }
  if (emotion == grinning) {
    printf("😺\n");
  } else if (emotion == smiling_eyes) {
    printf("😸\n");
  } else if (emotion == tears_of_joy) {
    printf("😹\n");
  } else if (emotion == heart_eyes) {
    printf("😻\n");
  } else if (emotion == wry_smile) {
    printf("😼\n");
  } else if (emotion == crying) {
    printf("😿\n");
  } else if (emotion == pouting) {
    printf("😾\n");
  } else {
    printf("Invalid choice\n");
    return (1);
  }
  return (0);
}

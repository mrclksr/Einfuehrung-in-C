#include <stdio.h>

/*
 * Konstanten für unser Menü
 */
const int in_to_cm = 1;
const int cm_to_in = 2;

/* Umrechnungsfaktor für inch nach cm */
const float in_to_cm_factor = 2.54;

int main() {
  int choice;
  /* float für Kommazahlen */
  float value, result;

  printf("%d. inch to cm\n"
         "%d. cm to inch\n"
         "Your choice: ",
         in_to_cm, cm_to_in);

  /*
   * Wir machen hier eine weniger ausführliche Fehlerprüfung. Statt den
   * Rückgabewert von scanf() zwischenzuspeichern, prüfen wir den Wert
   * direkt. Da wir einen Formatstring-Platzhalter (%d) angegeben haben,
   * müsste uns scanf() in Erfolgsfall 1 zurückgeben. Des weiteren nutzen
   * wir hier die lazy evaluation:
   * Wenn der Rückgabewert von scanf() != 1 ist, wird gar nicht weiter
   * geprüft. choice enthielte in diesem Fall ohnehin keine Information,
   * sondern nur zufällige Daten.
   * Wenn der Rückgabewert von scanf() == 1 ist, wird geprüft, ob choice
   * weder in_to_cm noch cm_to_in ist, also eine ungültige Wahl.
   */
  if (scanf("%d", &choice) != 1 || choice != in_to_cm && choice != cm_to_in) {
    printf("Invalid choice\n");
    return (1);
  }
  if (choice == in_to_cm) {
    printf("Enter value in inch: ");
    if (scanf("%f", &value) != 1) {
      printf("Invalid value\n");
      return (1);
    }
    result = value * in_to_cm_factor;
    printf("%f in = %f cm\n", value, result);
  } else if (choice == cm_to_in) {
    printf("Enter value in cm: ");
    if (scanf("%f", &value) != 1) {
      printf("Invalid value\n");
      return (1);
    }
    result = value / in_to_cm_factor;
    printf("%f cm = %f in\n", value, result);
  }
  return (0);
}
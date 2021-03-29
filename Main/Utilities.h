
void flashStatusLED() {

  static long currentTime = millis();
  static long lastTime;
  static int state;
  int interval = 500;

  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;
    state = !state;
    digitalWrite(pinStatusLED, state);
  }
}

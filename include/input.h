#ifndef INPUT_H
#define INPUT_H


#define K(X) X = KEY_##X
enum Key {
  K(A),
  K(B),
  K(SELECT),
  K(START),
  K(RIGHT),
  K(LEFT),
  K(UP),
  K(DOWN),
  K(R),
  K(L),
  K(X),
  K(Y),
  K(TOUCH),
  K(LID),
};

namespace Input {
  touchPosition tp;
  // should be called at the beginning of each frame
  void update() {
    scanKeys();
    touchRead(&tp);
  }
  touchPosition get_tp() {
    return tp;
  }
  bool key_down(Key key) {
    return keysHeld() & key;
  }
  bool key_released(Key key) {
    return keysUp() & key;
  }
  bool key_pressed(Key key) {
    return keysDown() & key;
  }
  bool key_up(Key key) {
    return !key_down(key);
  }
};

//////////////////////////
// Example:
// while (true) {
//  Input::update();
//  if (Input::key_pressed(Key::SELECT)) exit(1);
// }
//////////////////////////

#endif

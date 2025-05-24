#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// FIXME - does GameManager need to be passed to GameState? seems backwards

struct GameManager;
struct MenuState;
struct MiniGame0State;
struct GameState {
  virtual GameState* update(GameManager *mgr) = 0;
  virtual void onEnter(GameManager *mgr) = 0;
  virtual void onExit(GameManager *mgr) = 0;

  // Storing all states locally - I DONT like dynamic memory allocation!
  static MenuState menu_state;
  static MiniGame0State minigame0_state;
};

struct MiniGame0State : public GameState {
  virtual GameState* update(GameManager *mgr);
  virtual void onEnter(GameManager *mgr);
  virtual void onExit(GameManager *mgr);
};

struct MenuState : public GameState {
  virtual GameState* update(GameManager *mgr);
  virtual void onEnter(GameManager *mgr);
  virtual void onExit(GameManager *mgr);
};

struct Entity {
  virtual void update() = 0;
  virtual void init() = 0;
  virtual void deinit() = 0;

  int posx;
  int posy;
};

struct WeirdBox : public Entity {
  void update();
  void init();
  void deinit();
  bool hot;
  int boxw;
  int boxh;

  enum WeirdBoxState {
    NOT_CLICKED,
    CLICKED,
  };
  WeirdBoxState wbs;
};


#include <vector>
struct GameManager {
  GameState *gstate = &GameState::menu_state;
  void init();
  void deinit();
  void updateAll();
  int current_points; // for HUD
  std::vector<Entity*> entities;
};



#endif

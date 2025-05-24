#include "core_engine.h"
#include "game_manager.h"

//--------------------------------------------
// Mini Game 0 State (matching right?)
MiniGame0State GameState::minigame0_state= {};

GameState* MiniGame0State::update(GameManager* mgr) {
  if (CoreEngine::is_top_screen_active()) {
    CoreEngine::default_font.print_centered("Minigame0", SCREEN_WIDTH/2, 32);
  }

  if (Input::key_pressed(Key::B)) {
    Audio::play_sfx(SFX_HELLO);
    return (GameState*)&GameState::menu_state; 
  } 

  return nullptr;
};

void MiniGame0State::onEnter(GameManager *mgr) {
  auto wb = new WeirdBox();
  wb->boxw = 100;
  wb->boxh = 100;
  wb->posx = 0;
  wb->posy = SCREEN_HEIGHT/2 - wb->boxh/2;

  mgr->entities.push_back(wb);
};

void MiniGame0State::onExit(GameManager *mgr) {
  mgr->entities.clear();

};


//--------------------------------------------
// Menu State (matching right?)
MenuState GameState::menu_state = {};

GameState* MenuState::update(GameManager *mgr) {
  if (CoreEngine::is_top_screen_active()) {
    CoreEngine::default_font.print_centered("Menu", SCREEN_WIDTH/2, 32);
  }

  if (Input::key_pressed(Key::B)) {
    Audio::play_sfx(SFX_HELLO);
    return (GameState*)&GameState::minigame0_state; 
  }
  return nullptr;
};

void MenuState::onEnter(GameManager *mgr) {

};

void MenuState::onExit(GameManager *mgr) {

};

//--------------------------------------------
// Entity stuff

void WeirdBox::update() {
  auto tp = Input::get_tp();
  bool inside = (posx <= tp.px) && (posy <= tp.py) && (posx + boxw >= tp.px) && (posy + boxh >= tp.py);

  if (inside) {
    wbs = CLICKED;
  }

  if (Input::key_released(Key::TOUCH)) {
    wbs = NOT_CLICKED;
  }

  if (CoreEngine::is_bottom_screen_active()) {
    glBoxFilled (posx, posy, posx+boxw, posy+boxh, RGB15((wbs == CLICKED) ? 50 : 100,50,120));

    // If clicked make the line thingy
    if (wbs == CLICKED) {
      int startx = posx + boxw;
      int starty = posy + boxh/2;
      glLine(startx, starty, tp.px, tp.py, RGB15(255,255,255));
    }

  }

}
void WeirdBox::init() {

}
void WeirdBox::deinit() {

}

//--------------------------------------------
// Game Manager

void GameManager::init() {

}

void GameManager::deinit() {

}

void GameManager::updateAll() {
  // game state stuff
  auto newState = gstate->update(this);
  if (newState) {
    gstate->onExit(this);
    gstate = newState;
    gstate->onEnter(this);
  }
  // entity update
  for (auto& e : entities) {
    e->update();
  }
}



#include "gamelogic/elements/towers/tower_constructors.h"

char archer_symbol() {
  return 'A';
}

char canon_symbol() {
  return 'C';
}

char mage_symbol() {
  return 'M';
}

const TowerType CANON_TOWER = {
  .towerSymbol = 'C',
  .life = 100,
  .level = 1,
  .range = 300,
  .cost = 50,
  .firingRate = 10,
  .damage = 100};

const TowerType ARCHER_TOWER = {
  .towerSymbol = 'A',
  .life = 100,
  .level = 1,
  .range = 300,
  .cost = 50,
  .firingRate = 5,
  .damage = 75};

const TowerType MAGE_TOWER = {
  .towerSymbol = 'M',
  .life = 100,
  .level = 1,
  .range = 300,
  .cost = 50,
  .firingRate = 20,
  .damage = 150};

void create_archer_tower(Tower *tower, float x, float y) {
  tower_init(tower, &ARCHER_TOWER, x, y);
}

void create_canon_tower(Tower *tower, float x, float y) {
  tower_init(tower, &CANON_TOWER, x, y);
}

void create_mage_tower(Tower *tower, float x, float y) {
  tower_init(tower, &MAGE_TOWER, x, y);
}

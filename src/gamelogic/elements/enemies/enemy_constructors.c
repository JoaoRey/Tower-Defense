#include "enemy_constructors.h"

char orc_symbol() {
  return 'O';
}

char skeleton_symbol() {
  return 'S';
}

char golem_symbol() {
  return 'G';
}

const EnemyType ORC = {orc_symbol, 6, 1800};

const EnemyType SKELETON = {skeleton_symbol, 4, 700};

const EnemyType GOLEM = {golem_symbol, 2, 3200};

void create_orc(Enemy *enemy, int x, int y, int id) {
  enemy_init(enemy, &ORC, x, y, id);
}

void create_skeleton(Enemy *enemy, int x, int y, int id) {
  enemy_init(enemy, &SKELETON, x, y, id);
}

void create_golem(Enemy *enemy, int x, int y, int id) {
  enemy_init(enemy, &GOLEM, x, y, id);
}

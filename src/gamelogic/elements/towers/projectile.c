#include "gamelogic/elements/towers/projectile.h"
#include <math.h>
#include <time.h>

const long MAX_LIFETIME = 500;

void projectile_init(Projectile *projectile, int x1, int y1, float x, float y, int target_id, float speed, int damage) {
  projectile->damage = damage;
  projectile->speed = speed;
  projectile->xVelocity = 1;
  projectile->yVelocity = 1;
  projectile->active = 1;
  projectile->target_id = target_id;
  projectile->alive = 1;
  projectile->x = x1;
  projectile->y = y1;
}

int get_target(Projectile *projectile) {
  return projectile->target_id;
}

void projectile_update(Projectile *projectile) {
  projectile->x += projectile->xVelocity * projectile->speed;
  projectile->y += projectile->yVelocity * projectile->speed;
}

int projectile_is_alive(Projectile *projectile) {
  return projectile->alive;
}

int projectile_check_collision(Projectile *projectile, float x, float y, float x2, float y2) {
  float tolerance = 15;
  return fabs(x - x2) < tolerance && fabs(y - y2) < tolerance;
}

int projectile_is_active(Projectile *projectile) {
  return projectile->active;
}

void projectile_set_active(Projectile *projectile, int active) {
  projectile->active = active;
}

int projectile_get_damage(Projectile *projectile) {
  return projectile->damage;
}

Projectile *create_projectile(int x1, int y1, float x, float y, int target, float speed, int damage) {
  Projectile *projectile = (Projectile *) malloc(sizeof(Projectile));
  projectile_init(projectile, x1, y1, x, y, target, speed, damage);
  return projectile;
}

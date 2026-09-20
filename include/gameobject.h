#include <cglm/cglm.h>

struct GameObject{
    mat4 trans_mat;
    float rot;
    unsigned int mesh_id;
    unsigned int tex_id;
};

struct GameObject* create_gameobject(float x, float y, float rot, unsigned int mesh_id, unsigned int tex_id);

void set_gameobject_pos(struct GameObject* go, float x, float y);
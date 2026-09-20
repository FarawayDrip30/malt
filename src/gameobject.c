#include <cglm/cglm.h>

#include "gameobject.h"


struct GameObject* create_gameobject(float x, float y, float rot, unsigned int mesh_id, unsigned int tex_id){
    struct GameObject* go = (struct GameObject*) malloc(sizeof(struct GameObject));
    glm_mat4_identity(go->trans_mat);
    set_gameobject_pos(go, x, y);
    go->rot = rot;
    go->mesh_id = mesh_id;
    go->tex_id = tex_id;
    return go;
}

void set_gameobject_pos(struct GameObject* go, float x, float y){
    go->trans_mat[3][0] = x;
    go->trans_mat[3][1] = y;
}
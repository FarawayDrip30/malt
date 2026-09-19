#include <cglm/cglm.h>

#include "gameobject.h"


struct GameObject* create_gameobject(){
    struct GameObject* go = (struct GameObject*) malloc(sizeof(struct GameObject));
    glm_mat4_identity(go->trans_mat);
    return go;
}

void set_gameobject_pos(struct GameObject* go, float x, float y){
    go->trans_mat[3][0] = x;
    go->trans_mat[3][1] = y;
}
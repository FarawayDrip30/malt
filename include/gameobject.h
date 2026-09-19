struct GameObject{
    mat4 trans_mat;
    float rot;
    unsigned int mesh_id;
    unsigned int tex_id;
};

struct GameObject* create_gameobject();

void set_gameobject_pos(struct GameObject* go, float x, float y);
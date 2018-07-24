#ifndef CORIUM_CRAB_H
#define CORIUM_CRAB_H

class Crab : public Entity {
public:
Anims anims;

void think()
{
        if (closestEnemy != NULL) {
                if (vecDiff(phys.pos, closestEnemy->phys.pos) <= chaseRange)
                        chase(closestEnemy);
                if (vecDiff(phys.pos, closestEnemy->phys.pos) <= attackRange)
                        attack(closestEnemy);
        }
}

void chase(Entity* another)
{
        phys.v += 0.01f*normalize(vecFrom(phys.pos, another->phys.pos));
}

void attack(Entity* another)
{

}

void tick()
{
        //think();

        anims.anims[0].interpolation = 0;
        anims.anims[0].spd = 0.2f;
        //anims.phys = phys;
        anims.tick();

        update(); // object?
}

void load()
{
        anims.clearAnims();
        anims.loadTemplate("gfx/models/anim/crab/crab_0.obj", "gfx/entity.png");
        anims.addAnim("gfx/models/anim/crab/crab_", 3, 0.1f, {1, 0, 2, 0});
}

void draw(Renderer* renderer)
{
        anims.draw(renderer);
}

Crab() : Entity()
{

}
};

#endif // CORIUM_CRAB_H

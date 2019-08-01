#include "player.h"

Player::Player(int _id, int _team):
     selectedNav(0), id(_id), team(_team), radius(25)
{
    pos = new Position(0,0,0);
    pos->setTeam(team);
    navAlg = new StraightLine(pos, pos);
}

void Player::draw()
{
    if(team==blue){
        body->setX(int(pos->getX()));
        body->setY(int(pos->getY()));
    }else{
        body->setX(-int(pos->getX()));
        body->setY(-int(pos->getY()));
    }

}


//----- Getters and Setters -----//
void Player::setPosition(Position newPos)
{

    pos->setX(newPos.getX());
    pos->setY(newPos.getY());
    pos->setAngle(newPos.getAngle());
    draw();
}

int Player::getId() const
{
    return id;
}

void Player::setId(int value)
{
    id = value;
}

int Player::getTeam() const
{
    return team;
}

void Player::setTeam(int value)
{
    team = value;
}

int Player::getRadius() const
{
    return radius;
}

void Player::setRadius(int value)
{
    radius = value;
}

Position *Player::getPos() const
{
    return pos;
}

void Player::setPos(Position *value)
{
    pos = value;
}

NavigationAlgorithm *Player::getNavAlg() const
{
    return navAlg;
}

void Player::setNavAlg(NavigationAlgorithm *value)
{
    navAlg->clean();
    value->setEnd(navAlg->getEnd());
    value->setStart(navAlg->getStart());
    value->setObstacles(navAlg->getObstacles());
    navAlg = value;
}

int Player::getSelectedNav() const
{
    return selectedNav;
}

void Player::setSelectedNav(int value)
{
    selectedNav = value;
}


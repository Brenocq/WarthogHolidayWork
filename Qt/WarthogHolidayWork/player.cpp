#include "player.h"

Player::Player(int _id, int _team):
    id(_id), team(_team), radius(25)
{
    pos = new Position(0,0,0);
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


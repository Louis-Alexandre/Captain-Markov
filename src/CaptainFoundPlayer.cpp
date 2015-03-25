#include "CaptainFoundPlayer.h"


CaptainFoundPlayer::CaptainFoundPlayer()
{

}


bool CaptainFoundPlayer::check()
{
	return abs(_captain->getPosition().x - _matelot->getPosition().x) <= 1  && abs(_captain->getPosition().y - _matelot->getPosition().y) <= 1;
}

std::shared_ptr< Entity > CaptainFoundPlayer::getCaptain() const
{
	return this->_captain;
}

void CaptainFoundPlayer::setCaptain(std::shared_ptr< Entity > captain)
{
	this->_captain = captain;
}

std::shared_ptr< Entity > CaptainFoundPlayer::getMatelot() const
{
	return _matelot;
}

void CaptainFoundPlayer::setMatelot(std::shared_ptr< Entity > matelot)
{
	this->_matelot = matelot;
}


std::shared_ptr< Map > CaptainFoundPlayer::getMap() const
{
	return _mapRef.lock();
}

void CaptainFoundPlayer::setMap(std::weak_ptr< Map > map)
{
	_mapRef = map;
}


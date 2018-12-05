#include "Tile.h"


Tile::Tile(int type) {
	_type = type;
}

void Tile::setType(int type) {
	_type = type;
}

int Tile::getType() const {
	return _type;
}

bool Tile::isGround() {
	return Tiles::Ground::FIRST_GROUND <= _type && _type < Tiles::INVALID_GROUND;
}

bool Tile::isGround(int type) {
	return Tiles::Ground::FIRST_GROUND <= type && type < Tiles::INVALID_GROUND;
}

QPixmap Tile::getIcon(int mapType) const {
	QString mapTypeStr = "";
	switch (mapType) {
	case 0:
		mapTypeStr = "overworld";
		break;
	case 1:
		mapTypeStr = "underground";
		break;
	}
	QPixmap icon;
	QString path = "";
	switch (_type) {
	case Tiles::Types::NONE:
		break;
		// GroundType
	case Tiles::Ground::GND:
		path = QString(":/tiles/$/res/$/ground_gnd.png").replace("$", mapTypeStr);break;
	case Tiles::Ground::UP:
		path = QString(":/tiles/$/res/$/ground_up.png").replace("$",mapTypeStr);break;
	case Tiles::Ground::LEFT:
		path = QString(":/tiles/$/res/$/ground_left.png").replace("$", mapTypeStr);break;
	case Tiles::Ground::RIGHT:
		path = QString(":/tiles/$/res/$/ground_right.png").replace("$", mapTypeStr);break;
	case Tiles::Ground::DOWN:
		path = QString(":/tiles/$/res/$/ground_down.png").replace("$", mapTypeStr);break;

		// PropType
	case Tiles::Props::SIGN:
		path = ":/props/res/prop_sign.png";break;
	case Tiles::Props::BUSH:
		path = ":/props/res/prop_bush.png";break;

		// ObjectType
	case Tiles::Objects::COIN:
		path = ":/objects/res/object_coin.png"; break;
	case Tiles::Objects::FLAG:
		path = ":/objects/res/object_flag.png"; break;
	}
	icon = QPixmap(path);
	if (!icon.isNull())
		return icon.scaled(QSize(20, 20));
	else
		return icon;
}


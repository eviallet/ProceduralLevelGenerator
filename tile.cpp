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

bool Tile::isGround(int type) {
	return Tiles::Ground::FIRST_GROUND <= type && type < Tiles::INVALID_GROUND;
}

QPixmap Tile::getIcon() const {
	QPixmap icon;
	switch (_type) {
	case Tiles::Types::NONE:
		break;
	case Tiles::Ground::FLAT:
		icon = QPixmap(":/tiles/res/ground_flat.png");
		break;
	case Tiles::Ground::CAVE_GND:
		icon = QPixmap(":/tiles/res/ground_cave_gnd.png");
		break;
	case Tiles::Ground::CAVE_GND_LEFT:
		icon = QPixmap(":/tiles/res/ground_cave_gnd_left.png");
		break;
	case Tiles::Ground::CAVE_GND_RIGHT:
		icon = QPixmap(":/tiles/res/ground_cave_gnd_right.png");
		break;
	case Tiles::Ground::CAVE_GND_UP:
		icon = QPixmap(":/tiles/res/ground_cave_gnd_up.png");
		break;
	case Tiles::Ground::CAVE_GND_DOWN:
		icon = QPixmap(":/tiles/res/ground_cave_gnd_down.png");
		break;
	case Tiles::Props::FLAG:
		icon = QPixmap(":/props/res/flag.png");
		break;
	case Tiles::Props::SIGN:
		icon = QPixmap(":/props/res/sign.png");
		break;
	}
	return icon.scaled(QSize(20, 20));
}


#include "tile.h"


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

bool Tile::isStandable() {
	return _type == Tiles::Ground::UP || _type == Tiles::Terrain::PLATFORM || Tiles::Terrain::PLATFORM_UP_RIGHT || Tiles::Terrain::PLATFORM_UP_LEFT;
}

#ifdef QT
QPixmap Tile::getIcon(int mapType) const {
	QString mapTypeStr = "";
	int rotationDir = -1;
	const int HORIZ = 0;
	const int VERT = 1;
	const int BOTH = 2;
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
	case Tiles::NONE:
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
		path = QString(":/tiles/$/res/$/ground_down.png").replace("$", mapTypeStr); break;
	case Tiles::Ground::UP_LEFT:
		path = QString(":/tiles/$/res/$/ground_up_left.png").replace("$", mapTypeStr); break;
	case Tiles::Ground::UP_RIGHT:
		path = QString(":/tiles/$/res/$/ground_up_right.png").replace("$", mapTypeStr); break;

		// PropType
	case Tiles::Props::SIGN:
		path = ":/props/res/prop_sign.png";break;
	case Tiles::Props::BUSH:
		path = ":/props/res/prop_bush.png";break;

		// BlockType
	case Tiles::Blocks::BRICK:
		path = ":/blocks/res/block_block.png";break;
	case Tiles::Blocks::QUESTION:
		path = ":/blocks/res/block_qm.png";break;

		// ObjectType
	case Tiles::Objects::COIN:
		path = ":/objects/res/object_coin.png";break;
	case Tiles::Objects::FLAG:
		path = ":/objects/res/object_flag.png";break;
		
		// TerrainType
	case Tiles::Terrain::PLATFORM:
		path = QString(":/tiles/$/res/$/ground_above_up.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::PLATFORM_GND:
		path = QString(":/tiles/$/res/$/ground_gnd.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::PLATFORM_LEFT:
		path = QString(":/tiles/$/res/$/ground_above_left.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::PLATFORM_RIGHT:
		path = QString(":/tiles/$/res/$/ground_above_right.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::PLATFORM_UP_LEFT:
		path = QString(":/tiles/$/res/$/ground_above_up_left.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::PLATFORM_UP_RIGHT:
		path = QString(":/tiles/$/res/$/ground_above_up_right.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::SLOPE_DOWN_LEFT_1:
		path = QString(":/tiles/$/res/$/slope_down_left_1.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::SLOPE_DOWN_LEFT_1_GND:
		path = QString(":/tiles/$/res/$/slope_down_left_1_gnd.png").replace("$", mapTypeStr); break;
	case Tiles::Terrain::SLOPE_DOWN_RIGHT_1:
		path = QString(":/tiles/$/res/$/slope_down_left_1.png").replace("$", mapTypeStr);
		rotationDir = HORIZ; break;
	case Tiles::Terrain::SLOPE_DOWN_RIGHT_1_GND:
		path = QString(":/tiles/$/res/$/slope_down_left_1_gnd.png").replace("$", mapTypeStr);
		rotationDir = HORIZ; break;

		// EnemyType
	case Tiles::Enemies::GOOMBA:
		path = QString(":/enemies/res/enemies/goomba.png"); break;
	case Tiles::Enemies::BOBOMB:
		path = QString(":/enemies/res/enemies/bobomb.png"); break;
	case Tiles::Enemies::BOO:
		path = QString(":/enemies/res/enemies/boo.png"); break;
	case Tiles::Enemies::DINO:
		path = QString(":/enemies/res/enemies/dino.png"); break;
	case Tiles::Enemies::DINO_FIRE:
		path = QString(":/enemies/res/enemies/dino_fire.png"); break;
	case Tiles::Enemies::KAMEC:
		path = QString(":/enemies/res/enemies/kamec.png"); break;
	case Tiles::Enemies::KOOPA_CAPE:
		path = QString(":/enemies/res/enemies/koopa_cape.png"); break;
	case Tiles::Enemies::MOLE:
		path = QString(":/enemies/res/enemies/mole.png"); break;
	case Tiles::Enemies::QUATERBACK:
		path = QString(":/enemies/res/enemies/quaterback.png"); break;
	case Tiles::Enemies::FLYING_ENEMIES:
	case Tiles::Enemies::GOOMBA_FLYING:
		path = QString(":/enemies/res/enemies/goomba_flying.png"); break;
	case Tiles::Enemies::KOOPA_GREEN_FLYING:
		path = QString(":/enemies/res/enemies/koopa_green_flying.png"); break;
	case Tiles::Enemies::KOOPA_RED_FLYING:
		path = QString(":/enemies/res/enemies/koopa_red_flying.png"); break;
	case Tiles::Enemies::BOBOMB_PARACHUTE:
		path = QString(":/enemies/res/enemies/bobomp_parachute.png"); break;
	case Tiles::Enemies::BILL_BALL:
		path = QString(":/enemies/res/enemies/bill_ball.png"); break;
	}
	
	icon = QPixmap(path);
	if (rotationDir != -1) {
		switch (rotationDir) {
		case HORIZ:
			icon = QPixmap::fromImage(icon.toImage().mirrored(true, false)); break;
		case VERT:
			icon = QPixmap::fromImage(icon.toImage().mirrored(false, true)); break;
		case BOTH:
			icon = QPixmap::fromImage(icon.toImage().mirrored(true, true)); break;
		}
	}

	if (!icon.isNull())
		return icon.scaled(QSize(20, 20));
	else
		return icon;
}
#endif


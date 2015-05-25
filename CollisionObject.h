//CollisionObject.h
#pragma once

//�����蔻��I�u�W�F�N�g���L�q����񋓑�
enum GAME_COLLISION_OBJ_ID
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,

	OBJECT_ALLNUM,
	OBJECT_UNDEFINED = 0xFFFFFFFF,
};

//�����蔻��I�u�W�F�N�g���N���X
class CollisionObject
{
protected:
	float x, y, r;
	GAME_COLLISION_OBJ_ID id;

public:
	CollisionObject();

	GAME_COLLISION_OBJ_ID GetObjectID();

	float GetPosX();
	float GetPosY();
	float GetRadius();

	//�����̃I�u�W�F�N�g�ƐڐG���Ă��邩���肷��
	virtual bool IsCollision(CollisionObject* Obj);
};
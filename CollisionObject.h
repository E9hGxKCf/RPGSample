//CollisionObject.h
#pragma once

//当たり判定オブジェクトを記述する列挙体
enum GAME_COLLISION_OBJ_ID
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,

	OBJECT_ALLNUM,
	OBJECT_UNDEFINED = 0xFFFFFFFF,
};

//当たり判定オブジェクト基底クラス
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

	//引数のオブジェクトと接触しているか判定する
	virtual bool IsCollision(CollisionObject* Obj);
};
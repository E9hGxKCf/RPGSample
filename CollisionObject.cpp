#include "CollisionObject.h"

#include <math.h>

CollisionObject::CollisionObject()
{
	x = y = r = 0;
	id = OBJECT_UNDEFINED;
}

GAME_COLLISION_OBJ_ID CollisionObject::GetObjectID()
{
	return id;
}

float CollisionObject::GetPosX()
{
	return x;
}

float CollisionObject::GetPosY()
{
	return y;
}

float CollisionObject::GetRadius()
{
	return r;
}

bool CollisionObject::IsCollision(CollisionObject* Obj)
{
	if (Obj->GetObjectID() == id)
		return false;

	//�������v�Z
	float Dist_x = Obj->GetPosX() - this->x;
	float Dist_y = Obj->GetPosY() - this->y;
	float Dist = sqrt(Dist_x*Dist_x + Dist_y*Dist_y);

	//�����Ƒ���̑̂̑傫���̘a���������Z����Γ�����
	if (Dist <= this->r + Obj->GetRadius())
		return true;

	return false;
}
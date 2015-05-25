#include "CollisionCheck.h"
#include "CollisionObject.h"

std::shared_ptr<GameTaskManager> CreateCollisionCheck()
{
	return std::make_shared<CollisionCheck>();
}

GAMETASK_CODE CollisionCheck::Update()
{
	GAMETASK_CODE code = GameTaskManager::Update();

	for (auto it1 : TaskList)
	{
		CollisionObject* Obj1 = dynamic_cast<CollisionObject*>(it1.get());
		if (!Obj1)
			continue;

		for (auto it2 : TaskList)
		{
			CollisionObject* Obj2 = dynamic_cast<CollisionObject*>(it2.get());
			if (!Obj2)
				continue;

			if (Obj1->IsCollision(Obj2))
				code = TASK_NEXTSCENE;
		}
	}

	return code;
}
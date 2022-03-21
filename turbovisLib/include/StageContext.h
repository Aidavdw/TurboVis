#pragma once
#include <Stage.h>

namespace TurboVis
{
	class StageContext
	{
	public:

		StageContext(const int type)
		{
			SetType(type);
		};

		std::unique_ptr<Stage> stage;

		void SetType(const int type);

	};
}

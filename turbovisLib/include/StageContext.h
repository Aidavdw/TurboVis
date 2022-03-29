// TurboVis, a turbomachine visualisation tool by Aida van de Wetering
// Licensed under GNU General Public License v2.0

#pragma once
#include <memory>
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

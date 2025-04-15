#pragma once

namespace Tmpl8
{
	// External variables

	// Constants
	extern int cam_offset_x;
	extern int cam_offset_y;

	class Camera
	{
	public:
		void setCamPos(int x, int y);
		void camShake();
	};
}; 

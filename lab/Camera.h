#ifndef _CAMERA_H_
#define _CAMERA_H_

#define M_PI 3.1415

/*
Generic camera class by Nghia Ho
*/

class Camera
{
private:
	float xPos, yPos, zPos; // Position
	float xDirectionVec, yDirectionVec, zDirectionVec; // Direction vector of where we are looking at
	float yawAngle, pitchAngle; // Various rotation angles
	float xDirectionVecStrafe, zDirectionVecStrafe; // Always 90 degree to direction vector

private:
	Camera();
	~Camera();
	Camera(Camera const&);

// singleton
public:
	static Camera & getInstance()
	{
		static Camera instance;
		return instance;
	}

public:
	void init();
	void refresh();
	void setPos(float x, float y, float z);
	void getPos(float &x, float &y, float &z);
	void getDirectionVector(float &x, float &y, float &z);
	void setYaw(float angle);
	void setPitch(float angle);

	// Navigation
	void move(float incr);
	void strafe(float incr);
	void fly(float incr);
	void rotateYaw(float angle);
	void rotatePitch(float angle);

};

#endif

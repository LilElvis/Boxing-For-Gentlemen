//#include "Controller.h"
//
//int Controller::getPort()
//{
//	return controllerID;
//}
//
//XINPUT_GAMEPAD *Controller::getState()
//{
//	return &state.Gamepad;
//}
//
//bool Controller::checkConnection()
//{
//	int cID = -1;
//
//	for (DWORD i = 0; i < XUSER_MAX_COUNT && cID == -1; i++)
//	{
//		XINPUT_STATE state;
//		ZeroMemory(&state, sizeof(XINPUT_STATE));
//
//		if (XInputGetState(i, &state) == ERROR_SUCCESS)
//			cID = i;
//	}
//	
//	controllerID = cID;
//	return cID != -1;
//}
//
//bool Controller::update()
//{
//	if (controllerID == -1)
//		checkConnection();
//
//	if (controllerID != -1)
//	{
//		ZeroMemory(&state, sizeof(XINPUT_STATE));
//		if (XInputGetState(controllerID, &state) != ERROR_SUCCESS)
//		{
//			controllerID = -1;
//			return false;
//		}
//
//		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
//		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
//
//		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
//		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));
//
//		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
//		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);
//
//		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
//		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);
//
//		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normRX)));
//		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normRY)));
//
//		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
//		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);
//
//		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
//		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;
//
//		return true;
//	}
//	return false;
//}
//
//bool Controller::isPressed(WORD button)
//{
//	return (state.Gamepad.wButtons & button) != 0;
//}
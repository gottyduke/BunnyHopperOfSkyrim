#pragma once


class Controller
{
public:
	static Controller* GetSingleton();

	void OnJumping();
	void OnFalling();
	void OnLanding();
	void OnGround();
	void OnDelete();
	void HaltProcess();

	void ResetCounter() noexcept { stopCounter = 0; }

	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller() = default;
	~Controller() = default;

	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;

private:
	
	unsigned stopCounter = static_cast<unsigned>(-1);
};

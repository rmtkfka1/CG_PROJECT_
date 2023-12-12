#pragma once

class Shader;
class Event;
class Model;
class Light2;
class ENDING
{

public:

	ENDING(Model &model);
	~ENDING();

	void Init();
	void Update(Event *computer, Light2* light);
	void Render(Shader *shader);
	float dt{};
	float ft{};
	bool _coding = false;
private:



	Model* _model = nullptr;



};


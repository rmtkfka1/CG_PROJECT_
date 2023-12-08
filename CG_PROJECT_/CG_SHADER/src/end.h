#pragma once

class Shader;
class Event;
class Model;
class ENDING
{

public:

	ENDING(Model &model);
	~ENDING();

	void Init();
	void Update(Event *computer);
	void Render(Shader *shader);

	bool _coding = false;
private:


	float dt{};
	Model* _model = nullptr;


};


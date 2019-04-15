#pragma once
class ID3Demo
{
public:
	ID3Demo();
	~ID3Demo();



	void Draw();

	void OnKeyReleased(int key);
	void OnKeyPressed(int key);

	void OnMousePressed(int x, int y, int button);
	void OnMouseClick(int x, int y, int button);

	void Init();
	void Update();


};


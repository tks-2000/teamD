#pragma once
class SpriteRender : public IGameObject
{
public:
	SpriteRender();
	~SpriteRender();
	bool Start();
	void Update();
	void Init(const char* spriteFilePath, int width, int height);
	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetRotation(Quaternion& qRot) { m_qRot = qRot; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetPivot(Vector2 pivot) { m_pivot = pivot; }
	void SetColor(Vector4& color) { m_sprite.ColorUpdate(color); }
	void Render(RenderContext& rc) { m_sprite.Draw(rc); }

private:
	Sprite m_sprite;
	SpriteInitData m_spriteInitData;

	Vector3 m_position = Vector3::Zero;
	Quaternion m_qRot = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
	Vector2 m_pivot = { 0.5f,0.5f };
};


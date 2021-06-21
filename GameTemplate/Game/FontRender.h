#pragma once
class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();
	bool Start();
	void Update();

	/// @brief �\������e�L�X�g��ݒ�
	/// @param text �\��������������
	void SetText(const wchar_t* text);
	/// @brief �t�H���g��\��������W��ݒ�
	/// @param pos �t�H���g�ɐݒ肷����W
	void SetPosition(const Vector2 pos) { m_position = pos; }
	/// @brief �t�H���g�̉�]��ݒ�
	/// @param rotation �t�H���g�ɐݒ肷���]�p�x
	void SetRotation(float rotation) { m_rotation = rotation; }
	/// @brief �t�H���g�̊g�嗦��ݒ�
	/// @param scale �t�H���g�ɐݒ肷��g��{��
	void SetScale(float scale) { m_scale = scale; }
	/// @brief �t�H���g�̃J���[��ݒ�
	/// @param color �t�H���g�ɐݒ肷��J���[
	void SetColor(const Vector4 color) { m_color = color; }
	/// @brief �t�H���g�̒��S��ݒ�
	/// @param pivot �t�H���g�ɐݒ肷�钆�S�ʒu
	void SetPivot(const Vector2 pivot) { m_pivot = pivot; }
	
	void Render(RenderContext& rc);

private:
	/// @brief �t�H���g
	Font m_font;
	/// @brief �e�L�X�g
	std::wstring m_text;
	const wchar_t* m_texUnsafe = nullptr;
	/// @brief �t�H���g�̍��W
	Vector2 m_position = Vector2::Zero;
	/// @brief �t�H���g�̃J���[
	Vector4 m_color = Vector4::White;
	/// @brief �t�H���g�̉�]
	float m_rotation = 0.0f;
	/// @brief �t�H���g�̊g�嗦
	float m_scale = 1.0f;
	/// @brief �t�H���g�̒��S
	Vector2 m_pivot;
};


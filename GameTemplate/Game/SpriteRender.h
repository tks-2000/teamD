#pragma once
class SpriteRender : public IGameObject
{
public:
	SpriteRender();
	~SpriteRender();
	bool Start();
	void Update();
	/// @brief �X�v���C�g�̏�����
	/// @param spriteFilePath �摜��dds�t�@�C���p�X
	/// @param width �摜�̉���
	/// @param height �摜�̏c��
	void Init(const char* spriteFilePath, int width, int height);
	/// @brief �X�v���C�g�̍��W��ݒ�
	/// @param pos �X�v���C�g�ɐݒ肷����W
	void SetPosition(Vector3 pos) { m_position = pos; }
	/// @brief �X�v���C�g�̉�]��ݒ�
	/// @param qRot �X�v���C�g�ɐݒ肷��N�H�[�^�j�I��
	void SetRotation(Quaternion qRot) { m_qRot = qRot; }
	/// @brief �X�v���C�g�̊g�嗦��ݒ�
	/// @param scale �X�v���C�g�ɐݒ肷��g��{��
	void SetScale(Vector3 scale) { m_scale = scale; }
	/// @brief �X�v���C�g�̒��S��ݒ�
	/// @param pivot �X�v���C�g�ɐݒ肷�钆�S�ʒu
	void SetPivot(Vector2 pivot) { m_pivot = pivot; }
	/// @brief �X�v���C�g�ɏ�Z����J���[��ݒ�
	/// @param color �X�v���C�g�ɏ�Z����J���[
	void SetColor(Vector4 color) { m_sprite.ColorUpdate(color); }

	void Render(RenderContext& rc) { m_sprite.Draw(rc); }

private:
	/// @brief �X�v���C�g
	Sprite m_sprite;
	/// @brief �X�v���C�g�̏������f�[�^
	SpriteInitData m_spriteInitData;

	/// @brief �X�v���C�g�̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �X�v���C�g�̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �X�v���C�g�̊g�嗦
	Vector3 m_scale = Vector3::One;
	/// @brief �X�v���C�g�̒��S
	Vector2 m_pivot = { 0.5f,0.5f };
};


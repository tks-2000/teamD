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
	void SetPosition(const Vector3& pos) { m_position = pos; }
	/// @brief �X�v���C�g�̍��W�����
	/// @return �X�v���C�g�̍��W
	Vector3 GetPosition() { return m_position; }
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
	void SetColor(Vector4 color) { m_color = color; }
	/// @brief �t�F�[�h�̏���
	void Fade();
	/// @brief �X�v���C�g�̃t�F�[�h�C�����J�n
	/// @param rate �t�F�[�h�̃��[�g
	void FadeIn(float rate) { m_fadeInFlag = true; m_fadeOutFlag = false; m_fadeRate = rate; }
	/// @brief �X�v���C�g�̃t�F�[�h�A�E�g���J�n
	/// @param rate �t�F�[�h�̃��[�g
	void FadeOut(float rate) { m_fadeOutFlag = true; m_fadeInFlag = false; m_fadeRate = rate; }
	/// @brief �X�v���C�g�̕s�����x�����
	/// @return �J���[�̃A���t�@�l
	float GetOpacity() { return m_color.w; }
	/// @brief �X�v���C�g���s������?
	/// @return true�Ȃ�s���� false�Ȃ瓧����������
	bool IsOpacity();
	/// @brief �X�v���C�g���������H
	/// @return true�Ȃ瓧�� false�Ȃ�s������������
	bool IsTransparent();
	/// @brief �摜���ړ�������
	/// @param targetPos �ړ���������W
	/// @param velocity �ړ������鑬�x
	void MoveStart(Vector3 targetPos,float velocity);

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
	/// @brief �X�v���C�g�̃J���[
	Vector4 m_color = Vector4::White;

	/// @brief �ڕW�n�_�̍��W
	Vector3 m_targetPos = Vector3::Zero;
	/// @brief �ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �ړ��v�Z�O�̎����̍��W
	Vector3 m_previousPos = Vector3::Zero;

	/// @brief �t�F�[�h�C���t���O
	bool m_fadeInFlag = false;
	/// @brief �t�F�[�h�A�E�g�t���O
	bool m_fadeOutFlag = false;
	/// @brief �t�F�[�h�̃��[�g
	float m_fadeRate = 0.0f;

	/// @brief �ړ��t���O
	bool m_moveFlag = false;

	/// @brief �ړ��̏���
	void Move();
};


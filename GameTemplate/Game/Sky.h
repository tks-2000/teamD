#pragma once
class SkinModelRender;

class Sky : public IGameObject
{
public:
	Sky();

	~Sky();

	bool Start();

	void Update();
	/// @brief �X�P�[���Z�b�^�[(Vector3��)�A�f�t�H���g1000
	void SetScaleV(Vector3 Sca = { 1000.0f, 1000.0f, 1000.0f });
	/// @brief �X�P�[���Z�b�^�[(float��)�A�f�t�H���g1000
	void SetScaleF(float Sca = 1000.0f);
	
private:
	/// @brief �A�N�e�B�u�t���O
	bool m_Start = true;
	/// @brief �w�i�̍��W�X�e�[�W�������ɂȂ�悤�ݒ肷�ׂ�
	Vector3 Position = Vector3::Zero;
	/// @brief �X�P�[���A�X�e�[�W�̑傫���Ƒ��k
	Vector3 Scale = Vector3::Zero;
	/// @brief �X�L�������_�[
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief ���f���̉�]
	Quaternion m_rotation = Quaternion::Identity;
	/// @brief ���f���̉�]�p
	float ang = 0;
};


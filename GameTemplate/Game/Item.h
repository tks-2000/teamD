#pragma once

class SkinModelRender;
class GameDirector;
class Se;
class Objects;
class Player;
class Effect;
class PlayerReinforcement;


enum enItemType {
	enAttackUp,
	enGuardUp,
	enVelocityUp,
	enItemNum
};

class Item : public IGameObject
{
public:
	Item();
	~Item();
	bool Start();
	void Update();

	void SetPosition(const Vector3& pos) { m_position = pos; }
	void SetNumber(int num) { m_myNo = num; }

	/// @brief �A�C�e���̍��W���擾
	/// @return �A�C�e���̍��W�̎Q��
	const Vector3& GetPosition() const { return m_position; }

	void PlayerDistanceCalculation();

	//���݃G�t�F�N�g�̍Đ�
	void PlayBeingEffect();



	void SetItem(enItemType itemType) { m_itemState = itemType; ItemModelNewGO(); m_newGoFlag = true; }

private:

	bool m_setUp = false;
	bool m_getData = false;
	Vector3 m_position = Vector3::Zero;
	float m_posHeight = 0.0f;
	Vector3 m_toPos[PLAYER_NUM] = { Vector3::Zero ,Vector3::Zero ,Vector3::Zero ,Vector3::Zero };
	float m_distance[PLAYER_NUM] = { 0.0f };
	Quaternion m_qRot = Quaternion::Identity;
	float m_angle = 0.0f;
	SkinModelRender* m_skinModelRender = nullptr;
	int m_myNo = 4;
	Player* m_player[PLAYER_NUM] = { nullptr };

	PlayerReinforcement* m_plReinforcement[PLAYER_NUM] = { nullptr };

	GameDirector* m_gameDirector = nullptr;
	Se* m_se = nullptr;
	Objects* m_objects = nullptr;
	enItemType m_itemState = enAttackUp;
	bool m_newGoFlag = false;

	bool m_moveChange = false;

	/// @brief �A�C�e���̎���ɏo���G�t�F�N�g
	Effect m_itemBeingEffect;
	/// @brief �G�t�F�N�g�Đ��p�J�E���^�[
	int m_itemBeingCounter = 0;
	/// @brief �G�t�F�N�g�Đ����t���O
	bool m_isValidEffectPlay = false;

	void ItemModelNewGO();

};


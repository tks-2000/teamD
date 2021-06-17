#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "effect/Effect.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////


	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	EffectEngine::CreateInstance();

	NewGO<Game>(0, "game");
	
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	/*Effect effect;
	effect.Init(u"Assets/effect/kick.efk");*/

	/*Effect effect_01;
	effect_01.Init(u"Assets/effect/balltrack.efk");
	Vector3 efcPos = Vector3::Zero;
	Quaternion efcRot = Quaternion::Identity;*/

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{

		

		//if (g_pad[0]->IsTrigger(enButtonA)) {
		//	//�Đ��J�n�B
		//	effect.Play();
		//}

		//effect.SetScale({ 10.0f,10.0f,10.0f });
		//effect.SetPosition({ 0.0f,100.0f,0.0f });

		//effect.Update();

		//if (g_pad[0]->IsPress(enButtonRB1)) {
		//	//�Đ��J�n�B
		//	effect_01.Play();
		//}

		//float x = g_pad[0]->GetRStickXF();
		//float z = g_pad[0]->GetRStickYF();
		
		/*Vector3 efcDirectionX = { x,1.0f,1.0f };
		efcDirectionX.Normalize();
		Vector3 efcDirectionZ = { 1.0f,1.0f,z };
		efcDirectionZ.Normalize();

		float efcAngle = Dot(efcDirectionX, efcDirectionZ);
		efcRot.SetRotation(Vector3::AxisY, efcAngle);*/

		/*efcPos.x += x * 30.0f;
		efcPos.y = 100.0f;
		efcPos.z += z * 30.0f;


		effect_01.SetRotation(efcRot);
		effect_01.SetScale({ 15.0f,15.0f,1.0f });
		effect_01.SetPosition(efcPos);


		effect_01.Update();*/

		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		EffectEngine::GetInstance()->Draw();
		
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}


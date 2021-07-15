#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Title.h"
#include "effect/Effect.h"
#include "../../MiniEngine/time/Stopwatch.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////


	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();

	EffectEngine::CreateInstance();

	Stopwatch stopwatch;

	//NewGO<Title>(0, TITLE_NAME);
	NewGO<GameDirector>(0, GAME_DIRECTOR_NAME);
	
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	/*Effect effect;
	effect.Init(u"Assets/effect/kick.efk");*/

	/*Effect effect_01;
	effect_01.Init(u"Assets/effect/balltrack.efk");
	Vector3 efcPos = Vector3::Zero;
	Quaternion efcRot = Quaternion::Identity;*/

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{

		stopwatch.Start();

		//if (g_pad[0]->IsTrigger(enButtonA)) {
		//	//再生開始。
		//	effect.Play();
		//}

		//effect.SetScale({ 10.0f,10.0f,10.0f });
		//effect.SetPosition({ 0.0f,100.0f,0.0f });

		//effect.Update();

		//if (g_pad[0]->IsPress(enButtonRB1)) {
		//	//再生開始。
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

		//レンダリング開始。
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		EffectEngine::GetInstance()->Draw();
		

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();

		int restTime = 0;
		do {
			stopwatch.Stop();
			restTime = 16 - (int)stopwatch.GetElapsedMillisecond();

		}while(restTime > 0);
		stopwatch.Stop();
		g_gameTime->PushFrameDeltaTime((float)stopwatch.GetElapsed());
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	CSoundEngine::DeleteInstance();
	return 0;
}


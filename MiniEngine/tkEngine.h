#pragma once

#include "HID/GamePad.h"
#include "TResourceBank.h"
#include "TResourceBank2.h"
#include "tkFile/TkmFile.h"
#include "Shader.h"
#include <MiniEngine.h>

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TkEngine();
	/// <summary>
	/// フレームの開始時に呼ばれる処理。
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// フレームの終了時に呼ばれる処理。
	/// </summary>
	void EndFrame();
	/// <summary>
	/// ゲームエンジンの初期化。
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);




	TkmFile* GetTkmFileFromBank(const char* filePath)
	{
		return m_tkmFileBank.Get(filePath);
	}

	void RegistTkmFileToBank(const char* filePath, TkmFile* tkmFile)
	{
		m_tkmFileBank.Regist(filePath, tkmFile);
	}

	Shader* GetShaderFromBank(const char* filePath, const char* entryPointFuncName)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		return m_shaderBank.Get(programName.c_str());
	}

	void RegistShaderToBank(const char* filePath, const char* entryPointFuncName, Shader* shader)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		m_shaderBank.Regist(programName.c_str(), shader);
	}

private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//グラフィックエンジン。
	TResourceBank2<TkmFile> m_tkmFileBank;
	TResourceBank2<Shader> m_shaderBank;
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//ゲームパッド。
	GameTime m_gameTime;							//ゲームタイム。
	
};

extern TkEngine* g_engine;	//TKエンジン。
extern GameTime* g_gameTime;
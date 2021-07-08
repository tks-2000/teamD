#pragma once

#include "HID/GamePad.h"
#include "TResourceBank.h"
#include "tkFile/TkmFile.h"
#include "Shader.h"
#include <MiniEngine.h>

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TkEngine();
	/// <summary>
	/// �t���[���̊J�n���ɌĂ΂�鏈���B
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// �t���[���̏I�����ɌĂ΂�鏈���B
	/// </summary>
	void EndFrame();
	/// <summary>
	/// �Q�[���G���W���̏������B
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
	GraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
	TResourceBank<TkmFile> m_tkmFileBank;
	TResourceBank<Shader> m_shaderBank;
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
	GameTime m_gameTime;							//�Q�[���^�C���B
	
};

extern TkEngine* g_engine;	//TK�G���W���B
extern GameTime* g_gameTime;
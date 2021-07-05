#pragma once
class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();
	bool Start();
	void Update();

	/// @brief 表示するテキストを設定
	/// @param text 表示したい文字列
	void SetText(const wchar_t* text);
	/// @brief フォントを表示する座標を設定
	/// @param pos フォントに設定する座標
	void SetPosition(const Vector2 pos) { m_position = pos; }
	/// @brief フォントの回転を設定
	/// @param rotation フォントに設定する回転角度
	void SetRotation(float rotation) { m_rotation = rotation; }
	/// @brief フォントの拡大率を設定
	/// @param scale フォントに設定する拡大倍率
	void SetScale(float scale) { m_scale = scale; }
	/// @brief フォントのカラーを設定
	/// @param color フォントに設定するカラー
	void SetColor(const Vector4 color) { m_color = color; }
	/// @brief フォントの中心を設定
	/// @param pivot フォントに設定する中心位置
	void SetPivot(const Vector2 pivot) { m_pivot = pivot; }
	/// @brief フェードの処理
	void Fade();
	/// @brief フォントのフェードインを開始
	/// @param rate フェードのレート
	void FadeIn(float rate) { m_fadeInFlag = true; m_fadeOutFlag = false; m_fadeRate = rate; }
	/// @brief フォントのフェードアウトを開始
	/// @param rate フェードのレート
	void FadeOut(float rate) { m_fadeOutFlag = true; m_fadeInFlag = false; m_fadeRate = rate; }
	/// @brief フォントの不透明度を入手
	/// @return カラーのアルファ値
	float GetOpacity() { return m_color.w; }
	/// @brief フォントが不透明か?
	/// @return 不透明ならtrue 透明か半透明ならfalse
	bool IsOpacity();
	/// @brief フォントが透明か？
	/// @return 透明ならtrue 不透明か半透明ならfalse
	bool IsTransparent();
	/// @brief フォントを移動させる
	/// @param targetPos 移動させたい座標
	/// @param velocity 移動する速度
	void MoveStart(const Vector2& targetPos, float velocity);

	void Render(RenderContext& rc);

private:
	/// @brief フォント
	Font m_font;
	/// @brief テキスト
	std::wstring m_text;
	const wchar_t* m_texUnsafe = nullptr;
	/// @brief フォントの座標
	Vector2 m_position = Vector2::Zero;
	/// @brief フォントのカラー
	Vector4 m_color = Vector4::White;
	/// @brief フォントの回転
	float m_rotation = 0.0f;
	/// @brief フォントの拡大率
	float m_scale = 1.0f;
	/// @brief フォントの中心
	Vector2 m_pivot = { 1.0f,1.0f };

	/// @brief 移動する目標の座標
	Vector2 m_targetPos = Vector2::Zero;
	/// @brief 移動速度
	Vector2 m_moveSpeed = Vector2::Zero;
	/// @brief 移動処理をする前の座標
	Vector2 m_previousPos = Vector2::Zero;

	bool m_fadeInFlag = false;

	bool m_fadeOutFlag = false;

	float m_fadeRate = 0.0f;

	/// @brief 移動フラグ
	bool m_moveFlag = false;

	void Move();
};


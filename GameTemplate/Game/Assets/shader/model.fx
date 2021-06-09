/*!
 * @brief	シンプルなモデルシェーダー。
 */
////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos 	: TEXCOORD1;
};

//ディレクションライト
struct DirectionLight
{
	float3 direction;	//方向
	float3 color;		//カラー
};

//ポイントライト
struct PointLight
{
	float3 position;	//位置
	float3 color;		//カラー
	float Range;		//影響範囲

};

//スポットライト
struct SpotLight
{
	float3 position;	//位置
	float3 color;		//カラー
	float Range;		//射出範囲
	float3 direction;	//射出方向
	float angle;		//射出角度
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer LightCb : register(b1)
{
	DirectionLight directionLight;	//ディレクションライト
	PointLight pointLight;			//ポイントライト
	SpotLight spotLight;			//スポットライト
	float3 eyePos;					//視点の位置
	float3 ambientLight;			//環境光
};

////////////////////////////////////////////////
//関数宣言
////////////////////////////////////////////////
float3 CalculateLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalculatePhoneSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float CalculateImpactRate(float3 ligPos, float ligRange, float3 worldPos);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	
	psIn.normal = mul(mWorld, vsIn.normal); // 法線を回転させる。
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	float3 diffDirection = CalculateLambertDiffuse(
		directionLight.direction,
		directionLight.color,
		psIn.normal
	);

	float3 specDirection = CalculatePhoneSpecular(
		directionLight.direction,
		directionLight.color,
		psIn.worldPos,
		psIn.normal
	);

	//サーフェイスに入射するポイントライトの光の向きを計算する。
	float3 ligDir = psIn.worldPos - pointLight.position;
	//正規化する。
	ligDir = normalize(ligDir);

	//減衰なしのランバート拡散反射光を計算する。
	float3 diffPoint =  CalculateLambertDiffuse(
		ligDir,
		pointLight.color,
		psIn.normal
	);

	//減衰なしのフォン鏡面反射光を計算する。
	float3 specPoint = CalculatePhoneSpecular(
		ligDir,
		pointLight.color,
		psIn.worldPos,
		psIn.normal
	);

	//距離による影響率を計算する。
	float pAffect = CalculateImpactRate(pointLight.position,pointLight.Range,psIn.worldPos);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
	diffPoint *= pAffect;
	specPoint *= pAffect;

	//スポットライト用
	//サーフェイスに入射するポイントライトの光の向きを計算する。
	float3 sLigDir = psIn.worldPos - spotLight.position;
	//正規化する。
	sLigDir = normalize(sLigDir);

	//減衰なしのランバート拡散反射光を計算する。
	float3 diffSpot =  CalculateLambertDiffuse(
		sLigDir,
		spotLight.color,
		psIn.normal
	);

	//減衰なしのフォン鏡面反射光を計算する。
	float3 specSpot = CalculatePhoneSpecular(
		sLigDir,
		spotLight.color,
		psIn.worldPos,
		psIn.normal
	);

	//距離による影響率を計算する。
	float sAffect = CalculateImpactRate(spotLight.position,spotLight.Range,psIn.worldPos);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
	diffSpot *= sAffect;
	specSpot *= sAffect;

	//入射光と射出方向の角度を求める。
	//dot()を利用して内積を求める。
	float sAngle = dot(sLigDir,spotLight.direction);
	//dot()で求めた値をacosに渡して角度を求める。
	sAngle = acos(sAngle);

	//角度による影響率を求める。
	//角度に比例して小さくなっていく影響率を計算する。
	float aAffect = 1.0f - 1.0f / spotLight.angle * sAngle;
	//影響力がマイナスにならないように補正をかける。
	aAffect = max(0.0f,aAffect);
	//影響の仕方を指数関数的にする。
	aAffect = pow(aAffect,0.5f);

	diffSpot *= aAffect;
	specSpot *= aAffect;

	
	//二つの反射光を合算して最終的な反射光を求める。
	float3 diffuseLig = diffPoint + diffDirection + diffSpot;
	float3 specularLig = specPoint + specDirection + specSpot;

	//拡散反射光・鏡面反射光・環境光を加算して最終的な光を求める。
	float3 lig = diffuseLig + specularLig + ambientLight;

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//テクスチャカラーに求めた光を乗算して最終出力カラーを求める。
	albedoColor.xyz *= lig;

	return albedoColor;
}

float3 CalculateLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する。
	float t = dot(normal,lightDirection);

	//内積の結果に-1を乗算する。
	t *= -1.0f;

	//内積の結果が0以下なら0にする。
	t = max(0.0f, t);

	//拡散反射光を求める。
	return lightColor * t;
}

float3 CalculatePhoneSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
//反射ベクトルを求める。
	float3 refVec = reflect(lightDirection,normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める。
	float3 toEye = eyePos - worldPos;
	//正規化する。
	toEye = normalize(toEye);

	//鏡面反射の強さを求める。
	//dot関数を利用してrefVecとtoEyeの内積を求める。
	float t = dot(refVec,toEye);
	//内積の結果はマイナスになるので、マイナスの場合は0にする。
	t = max(0.0f, t);

	//鏡面反射の強さを絞る。
	t = pow(t,2.0f);

	//鏡面反射光を求める。
	return directionLight.color * t;
}

float CalculateImpactRate(float3 ligPos, float ligRange, float3 worldPos)
{
	//距離による影響率を計算する。
	//ポイントライトとの距離を計算する。
	float3 lDistance = length(worldPos - ligPos);

	//影響率は距離に比例して小さくなっていく。
	float lAffect = 1.0f - 1.0f / ligRange * lDistance;

	//影響力がマイナスにならないように補正をかける。
	lAffect = max(0.0, lAffect);

	//影響を指数関数的にする。
	lAffect = pow(lAffect,3.0f);
	return lAffect;
}
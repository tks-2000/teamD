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

struct DirectionLight
{
	float3 direction;
	float3 color;
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

cbuffer DirectionLightCb : register(b1)
{
	DirectionLight directionLight;
	float3 eyePos;			//視点の位置
	float3 ambientLight;
};

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
	psIn.worldPos = vsIn.pos;
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
	//ピクセルの法線とライトの方向の内積を計算する。
	float t = dot( psIn.normal,directionLight.direction);

	//内積の結果に-1を乗算する。
	t *= -1.0f;

	//内積の結果が0以下なら0にする。
	if(t < 0.0f){
		t = 0.0f;
	}

	//拡散反射光を求める。
	float3 diffuseLig  = directionLight.color * t;

	//反射ベクトルを求める。
	float3 refVec = reflect(directionLight.direction,psIn.normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める。
	float3 toEye = eyePos - psIn.worldPos;
	//正規化する。
	toEye = normalize(toEye);

	//鏡面反射の強さを求める。
	//dot関数を利用してrefVecとtoEyeの内積を求める。
	t = dot(refVec,toEye);
	//内積の結果はマイナスになるので、マイナスの場合は0にする。
	if(t < 0.0f){
		t = 0.0f;
	}

	//鏡面反射の強さを絞る。
	t = pow(t,5.0f);

	//鏡面反射光を求める。
	float3 specularLig = directionLight.color * t;

	//拡散反射光・鏡面反射光・環境光を加算して最終的な光を求める。
	float3 lig = diffuseLig + specularLig + ambientLight;

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//テクスチャカラーに求めた光を乗算して最終出力カラーを求める。
	albedoColor.xyz *= lig;

	return albedoColor;
}

#pragma once





struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;

	D3DXVECTOR3 Tangent;
	D3DXVECTOR3 Binormal;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2];
};

// �}�e���A���\����
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture* Texture;
};
// �`��T�u�Z�b�g�\����
struct DX11_SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;

	D3DXMATRIX	ViewMatrix;
	D3DXMATRIX	ProjectionMatrix;
};

//�t�H�O�p
struct CAMERA
{
	D3DXVECTOR4 Position;
	D3DXVECTOR4 FogParam;
	D3DXCOLOR   FogColor;
	D3DXCOLOR   GroundFogColor;
};

struct PARAMETER
{
	//�f�B�]���u����
	float dissolveThreshold;
	float disolveRange;
	float dummy[2];
	//HP�o�[
	D3DXVECTOR4 hitpoint;
	D3DXCOLOR lostColor; //��������HP�o�[
	D3DXCOLOR basecolor; //HP�o�[�̐F
	D3DXCOLOR dissColor; //�ꎞ�\��HP�o�[�̐F

	D3DXVECTOR4 stamina;
	D3DXCOLOR	staminabasecolor; //�X�^�~�i�Q�[�W�̐F

	D3DXCOLOR	collidercollor; //�R���C�_�[�̐F
};



class CVertexBuffer;
class CIndexBuffer;
class CTexture;



class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState*		m_BlendState;
	static ID3D11BlendState*		m_BlendStateATC;

	//�f�v�X�V���h�E
	static ID3D11DepthStencilView* m_DepthShadowDepthStencilView;
	static ID3D11ShaderResourceView* m_DepthShadowShaderResourceView;
	static ID3D11Buffer* m_CameraBuffer;
	static ID3D11Buffer* m_ParameterBuffer;

	//���}�b�s���O
	static ID3D11Texture2D* m_ReflectTexture;
	static ID3D11RenderTargetView* m_ReflectRenderTargetView;
	static ID3D11DepthStencilView* m_ReflectDepthStencilView;
	static ID3D11Texture2D* m_CubeReflectTexture;
	static ID3D11ShaderResourceView* m_CubeReflectShaderResourceView;

	//���X�^���C�U
	static ID3D11RasterizerState* m_rsbuck;
	static ID3D11RasterizerState* m_rsnone;

public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	//�f�v�X�V���h�E
	static void SetParameter(PARAMETER param);

	//�t�H�O
	static void SetCameraPosition(CAMERA camera);

	//���}�b�s���O
	static void BeginCube(void);
	//static void SetDefaultViewport(void);
	static void SetReflectViewport(void);

	static ID3D11Texture2D* GetReflectTexture(void) { return m_ReflectTexture; }
	static ID3D11Texture2D* GetCubeReflectTexture(void) { return m_CubeReflectTexture; }
	static ID3D11ShaderResourceView** GetCubeReflectShaderResourceView(void) {return &m_CubeReflectShaderResourceView;}


	static ID3D11ShaderResourceView* GetDepthShadowTexture()
	{
		return m_DepthShadowShaderResourceView;
	}

	static void BeginDepth()
	{
		m_DeviceContext->OMSetRenderTargets(0, NULL, m_DepthShadowDepthStencilView);
		m_DeviceContext->ClearDepthStencilView(m_DepthShadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	static void SetDefaultViewport(void);
	static void SetDepthViewport(void);
	static void SetRssetEnable(bool enable);
};

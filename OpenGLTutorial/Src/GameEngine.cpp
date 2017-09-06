/**
*	@file	GameEngine.cpp
*/
#include "GameEngine.h"
#include "GLFWEW.h"
#include "Audio.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

///頂点データ型
struct Vertex
{
	glm::vec3 position;	///<座標
	glm::vec4 color; ///<色
	glm::vec2 texCoord;
};


///頂点データ
const Vertex vertices[] = {
	/*
	{ { 1.0f,0.0f,1.0f,1.0f } ,{ -0.5f,-0.5f,0.5f } },
	{ { 0.0f,1.0f,0.0f,1.0f } ,{ 0.5f,-0.5f,0.5f } },
	{ { 1.0f,0.0f,0.0f,1.0f } ,{ -0.5f,0.5f,0.5f } },
	//{ { 0.5f,-0.5f,0.5f },{ 0.0f,1.0f,0.0f,1.0f } },
	//{ { -0.5f,0.5f,0.5f },{ 1.0f,0.0f,0.0f,1.0f } },
	{ { 1.0f,1.0f,1.0f,1.0f } ,{ 0.5f,0.5f,0.5f } },
	*/
	/*
	{ { -0.5f,-0.3f,0.5f }, { 0.0f,0.0f,1.0f,1.0f }  },
	{ { 0.3f,-0.3f,0.5f } ,	{ 0.0f,1.0f,0.0f,1.0f } },
	{ { 0.3f,0.5f,0.5f }  ,	{ 0.0f,0.0f,1.0f,1.0f } },
	{ { -0.5f,0.5f,0.5f } ,	{ 1.0f,0.0f,0.0f,1.0f } },

	{  { -0.3f, 0.3f,0.1f },{ 0.0f,0.0f,1.0f,1.0f } },
	{  { -0.3f,-0.5f,0.1f },{ 0.0f,1.0f,1.0f,1.0f } },
	{  {  0.5f,-0.5f,0.1f },{ 0.0f,0.0f,1.0f,1.0f } },
	{  {  0.5f,-0.5f,0.1f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  {  0.5f, 0.3f,0.1f },{ 1.0f,1.0f,0.0f,1.0f } },
	{  { -0.3f, 0.3f,0.1f },{ 1.0f,0.0f,0.0f,1.0f } },

	//6角
	{  { -0.3f, 0.3f,0.3f },{ 0.0f,0.0f,1.0f,1.0f } },
	{  { -0.3f,-0.5f,0.3f },{ 0.0f,1.0f,1.0f,1.0f } },
	{  {  0.5f,-0.5f,0.3f },{ 0.0f,0.0f,1.0f,1.0f } },
	{  {  0.5f,-0.5f,0.3f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  {  0.5f, 0.3f,0.3f },{ 1.0f,1.0f,0.0f,1.0f } },
	{  { -0.3f, 0.3f,0.3f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  { -0.3f, 0.3f,0.3f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  { -0.3f, -0.5f,0.3f} ,{ 0.0f,0.0f,1.0f,1.0f } },
	{  { -0.7f, -0.15f,0.3f},{ 1.0f,1.0f,0.0f,1.0f }  },
	{  { 0.5f, 0.3f,0.3f } ,{ 1.0f,1.0f,0.0f,1.0f }},
	{  { 0.5f,-0.5f,0.3f } ,{ 1.0f,0.0f,0.0f,1.0f }},
	{  {  0.8f, 0.0f,0.3f },{ 1.0f,0.0f,0.0f,1.0f } },

	//8角
	{  { 0.0f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,0.5f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.3f,0.4f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.3f,0.4f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.5f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.5f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.3f,-0.4f,0.0f} ,{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,0.0f,0.0f },{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.3f,-0.4f,0.0f},{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,-0.5f,0.0f},{ 0.5f,0.5f,0.5f,1.0f } },
	{  { 0.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  { 0.0f,-0.5f,0.0f} ,{ 1.0f,0.0f,0.0f,1.0f } },
	{  { -0.3f,-0.4f,0.0f},{ 1.0f,0.0f,0.0f,1.0f }  },
	{  { 0.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f } },
	{  { -0.3f,-0.4f,0.0f},{ 1.0f,0.0f,0.0f,1.0f } },
	{ { -0.5f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f }  },
	{  { 0.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f } },
	{ { -0.5f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f }  },
	{ { -0.3f,0.4f,0.0f} ,{ 1.0f,0.0f,0.0f,1.0f }  },
	{  { 0.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f,1.0f } },
	{ { -0.3f,0.4f,0.0f} ,{ 1.0f,0.0f,0.0f,1.0f }  },
	{  { 0.0f,0.5f,0.0f },{ 1.0f,0.0f,0.0f,1.0f } },
	*/

	{ { -0.5f,-0.3f,0.7f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,0.0f } },
	{ { 0.3f,-0.3f,0.7f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,0.0f } },
	{ { 0.3f, 0.5f,0.7f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,1.0f } },
	{ { -0.5f, 0.5f,0.7f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,1.0f } },

	{ { -0.3f, 0.3f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,1.0f } },
	{ { -0.3f,-0.5f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,0.0f } },
	{ { 0.5f,-0.5f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,0.0f } },
	{ { 0.5f,-0.5f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,0.0f } },
	{ { 0.5f, 0.3f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,1.0f } },
	{ { -0.3f, 0.3f,0.1f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,1.0f } },

	{ { -1.0f,-1.0f,0.5f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,0.0f } },
	{ { 1.0f,-1.0f,0.5f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,0.0f } },
	{ { 1.0f, 1.0f,0.5f },{ 1.0f,1.0f,1.0f,1.0f },{ 1.0f,1.0f } },
	{ { -1.0f, 1.0f,0.5f },{ 1.0f,1.0f,1.0f,1.0f },{ 0.0f,1.0f } },

};

///インデックスデータ
const GLuint indices[] = {
	/*
	0,1,2,2,3,0,
	4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,20,21,
	22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45
	*/
	0,1,2,2,3,0,
	4,5,6,7,8,9,
	10,11,12,12,13,10,
};



/**
*部分描画データ
*/
struct RenderingPart
{
	GLsizei size;	///<描画するインデックス数
	GLvoid* offset;	///<描画開始インデックスのバイトオフセット
};

/**
*RenderingPartを作成する
*
*@param	size 描画するインデックス数
*@param offset 描画開始インデックスのオフセット(インデックス単位)
*
*@return 作成した部分描画オブジェクト
*/
constexpr RenderingPart MakeRenderingPart(GLsizei size, GLsizei offset)
{
	return{ size,reinterpret_cast<GLvoid*>(offset * sizeof(GLuint)) };
}

/**
*部分描画データリスト
*/
static const RenderingPart renderingParts[] = {
	MakeRenderingPart(12,0),
	MakeRenderingPart(6,12),
};


/**
*Vertex Buffer Objectを作成する
*
*@param	size 頂点データのサイズ
*@param	data 頂点データへのポインタ
*
*@return	作成したVBO.
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

/**
*Index Buffer Objectを作成する
*
*@param	size インデックスデータのサイズ
*@param	data インデックスデータへのポインタ
*
*@return	作成したIBO.
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return ibo;
}

/**
*頂点アトリビュートを設定する
*
*@param	index	頂点アトリビュートのインデックス
*@paran	cls		頂点データ型名
*@param	mbr	頂点アトリビュートに設定するclsのメンバ変数名
*/
#define SetVertexAttribPointer(index,cls,mbr)SetVertexAttribPointerI(\
		index,	\
		sizeof(cls::mbr) / sizeof(float), \
		sizeof(cls), \
		reinterpret_cast<GLvoid*>(offsetof(cls,mbr)))

void SetVertexAttribPointerI(GLuint index, GLint size, GLsizei stride, const GLvoid* pointer)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

/**
*Vertex Array Objectを作成する
*
*@param vbo VAOに関連付けられるVBO
*@param ibo VAOに関連付けられるIBO	<-new!
*
*@return	作成したVBO.
*/
GLuint CreateVAO(GLuint vbo, const GLuint ibo)
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	SetVertexAttribPointer(0, Vertex, position);
	SetVertexAttribPointer(1, Vertex, color);
	SetVertexAttribPointer(2, Vertex, texCoord);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindVertexArray(0);
	return vao;
}



/**
*ゲームエンジンのインスタンスを取得する
*
*@return ゲームエンジンのインスタンス
*/
GameEngine& GameEngine::Instance()
{
	static GameEngine instance;
	return instance;
}

/**
*ゲームエンジンを取得
*
*@param	w	ウィンドウの描画範囲の幅(ピクセル)
*@param	h	ウィンドウの描画範囲の高さ(ピクセル)
*@param	title	ウィンドウタイトル(UTF-8の0終端文字列)
*
*@retval	true	初期化成功
*@retval	false	初期化失敗
*
*Run関数を呼び出す前に、一度だけ呼び出しておく必要がある
*一度初期化に成功すると、以後の呼び出しでは何もせずにtrueを返す
*/
bool GameEngine::Init(int w, int h, const char* title)
{
	if (isInitialized)
	{
		return true;
	}
	if (!GLFWEW::Window::Instance().Init(w, h, title))
	{
		return false;
	}

	//---ここに初期化処理を追加する---
	vbo = CreateVBO(sizeof(vertices), vertices);
	ibo = CreateIBO(sizeof(indices), indices);
	vao = CreateVAO(vbo, ibo);
	//const GLuint ubo = CreateUBO(sizeof(VertexData));
	
	uboLight = UniformBuffer::Create(sizeof(Uniform::LightData), 1, "LightData");
	uboPostEffect = UniformBuffer::Create(sizeof(Uniform::PostEffectData), 2, "PostEffectData");
	//const GLuint shaderProgram = CreateShaderProgram(vsCode, fsCode);
	//シェーダ作成コード
	//const GLuint shaderProgram = Shader::CreateProgramFromFile("Res/Tutorial.vert", "Res/Tutorial.Frag");
	progTutorial = Shader::Program::Create("Res/Tutorial.vert", "Res/Tutorial.Frag");
	progColorFilter = Shader::Program::Create("Res/Colorfilter.vert", "Res/ColorFilter.Frag");

	offscreen = OffscreenBuffer::Create(800, 600);
	if (!vbo || !ibo || !vao || !uboLight || !uboPostEffect || !progTutorial || !progColorFilter || !offscreen) //new!
	{
		std::cerr << "ERROR: GameEngine の初期化に失敗" << std::endl;
		return false;
	}
	progTutorial->UniformBlockBinding("VertexData", 0);
	progTutorial->UniformBlockBinding("LightData", 1);
	progColorFilter->UniformBlockBinding("PostEffectData", 2);

	meshBuffer = Mesh::Buffer::Create(10 * 1024, 30 * 1024);
	if (!meshBuffer)
	{
		std::cerr << "ERROR: GameEngine の初期化に失敗" << std::endl;
		return false;
	}
	//meshBuffer->LoadMeshFromFile("Res/Toroid.fbx");

	entityBuffer = Entity::Buffer::Create(1024,sizeof(Uniform::VertexData), 0, "VertexData");
	if (!entityBuffer)
	{
		std::cerr << "ERROR: GameEngine の初期化に失敗" << std::endl;
		return false;
	}
	rand.seed(std::random_device()());

	fontRenderer.Init(1024, glm::vec2(800, 600));

	isInitialized = true;
	return true;
}

/**
*	ゲームを実行する
*/
void GameEngine::Run()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	double prevTime = glfwGetTime();
	while(!window.ShowldClose())
	{
		const double curTime = glfwGetTime();
		const double delta = curTime - prevTime;
		prevTime = curTime;
		window.UpdateGamePad();
		Update(glm::min(0.25,delta));
		Render();
		window.SwapBuffers();
	}
}

/**
*状態更新関数を設定する
*
*@param	func	設定する更新関数
*/
void GameEngine::UpdateFunc(const UpdateFuncType& func)
{
	updateFunc = func;
}

/**
*状態更新関数を取得する
*
*@return	設定されている更新関数
*/
const GameEngine::UpdateFuncType& GameEngine::UpdateFunc() const
{
	return updateFunc;
}

/**
*テクスチャを読み込む
*
*@param	filename	テクスチャファイル名
*
*@retval true	読み込み
*@retval false	読み込み失敗
*/
bool GameEngine::LoadTextureFromFile(const char* filename)
{
	const auto itr = textureBuffer.find(filename);
	if (itr != textureBuffer.end())
	{
		return true;
	}
	TexturePtr texture = Texture::LoadFromFile(filename);
	if (!texture)
	{
		return false;
	}
	textureBuffer.insert(std::make_pair(std::string(filename), texture));
	return true;
}

/**
*メッシュを読み込む
*
*@param filename	メッシュファイル名
*
*@retval true	読み込み成功 
*@retval false	読み込み失敗
*/
bool GameEngine::LoadMeshFromFile(const char* filename)
{
	return meshBuffer->LoadMeshFromFile(filename);
}

/**
*エンティティを追加する
*
*@param	groupId		エンティティのグループID
*@param	pos	エンティティの座標
*@param	meshName	エンティティの表示に使用するメッシュ名
*@param	texName		エンティティの表示に使うテクスチャファイル名
*@param	func		エンティティの状態を更新する関数
*
*@return 追加したエンティティへのポインタ
*		これ以上エンティティを追加できない場合はnullptrが返される
*		回転や拡大率はこのポインタ経由で設定する
*		なお、このポインタをアプリケーション側で保持する必要はない
*/
Entity::Entity* GameEngine::AddEntity(int groupId, const glm::vec3& pos, const char* meshName,
	const char* texName, Entity::Entity::UpdateFuncType func,bool hasLight)
{
	const Mesh::MeshPtr& mesh = meshBuffer->GetMesh(meshName);
	const TexturePtr& tex = textureBuffer.find(texName)->second;
	return entityBuffer->AddEntity(groupId, pos, mesh, tex, progTutorial, func);
}

/**
*エンティティを削除する
*
*@param	削除するエンティティのポインタ
*/
void GameEngine::RemoveEntity(Entity::Entity* e)
{
	entityBuffer->RemoveEntity(e);
}
/**
*ライトを設定する
*
*@param	indes	設定するライトのインデックス
*@param	light	ライトデータ
*/
void GameEngine::Light(int index, const Uniform::PointLight& light)
{
	if (index < 0 || index >= Uniform::maxLightCount)
	{
		std::cerr << "WARNING: ' " << index << " ' は不正なライトインデックスです" << std::endl;
		return;
	}
	lightData.light[index] = light;
}

/**
*ライトを取得する
*
*@param	index	取得するライトのインデックス
*
*@return ライトデータ
*/
const Uniform::PointLight& GameEngine::Light(int index) const
{
	if (index < 0 || index >= Uniform::maxLightCount)
	{
		std::cerr << "WARNING: ' " << index << " ' は不正なライトインデックスです" << std::endl;
		static const Uniform::PointLight dummy;
		return dummy;
	}
	return lightData.light[index];
}

/**
*環境光を設定する
*
*@param color	環境光の明るさ
*/
void GameEngine::AmbientLight(const glm::vec4& color)
{
	lightData.ambientColor = color;
}

/**
*環境光を取得する
*
*@return 環境光の明るさ
*/
const glm::vec4& GameEngine::AmbientLight() const
{
	return lightData.ambientColor;
}


/**
*視点の位置と姿勢を設定する
*
*@param	cam	設定するカメラデータ
*/
void GameEngine::Camera(const CameraData& cam)
{
	camera = cam;
}

/**
*視点の位置と姿勢を取得する
*
*@return カメラデータ
*/
const GameEngine::CameraData& GameEngine::Camera() const
{
	return camera;
}

/**
*乱数オブジェクトを取得する
*
*@return 乱数オブジェクト
*/
std::mt19937& GameEngine::Rand()
{
	return rand;
}

/**
*	ゲームパッドの状態を取得する
*/
const GamePad& GameEngine::GetGamePad() const
{
	return GLFWEW::Window::Instance().GetGamePad();
}

/**
*衝突解決ハンドラを設定する
*
*@param	gid0	衝突対象のグループID
*@param	gid1	衝突対象のグループID
*@param	handler	衝突解決ハンドラ
*
*衝突が発生し衝突解決ハンドラが呼び出されるとき、より小さいグループIDを持つエンティティから先に渡される
*ここれ指定したグループIDの順序とは無関係であることに注意すること
*ex)
*	CollisionHandler(10,1,Func)
*	というコードでハンドラを登録したとする　衝突が発生すると
*	Func(グループID = 1 のエンティティ、グループID = 10 のエンティティ)
*	のように呼び出される
*/
void GameEngine::CollisionHandler(int gid0, int gid1, Entity::CollisionHandlerType handler)
{
	entityBuffer->CollisionHandler(gid0, gid1, handler);
}

/**
*衝突解決ハンドラを取得する

*
*@param	gid0	衝突対象のグループID
*@param	gid1	衝突対象のグループID
*
*@return 衝突対象ハンドラ
*/
const Entity::CollisionHandlerType& GameEngine::CollisionHandler(
	int gid0, int gid1) const
{
	return entityBuffer->CollisionHandler(gid0, gid1);
}

/**
*	衝突解決ハンドラのリストをクリアする
*/
void GameEngine::ClearCollsionHandlerList()
{
	entityBuffer->ClearCollisionHandlerList();
}

/**
*@copydoc	Audio::Initialize
*/
bool GameEngine::InitAudio(const char* acfPath, const char* acbPath, const char* awbPath, const char* dspBusName)
{
	return Audio::Initialize(acfPath, acbPath, awbPath, dspBusName);
}


/**
*@copydoc	Audio::Play
*/
void GameEngine::PlayAudio(int playerId, int cueId)
{
	Audio::Play(playerId, cueId);
}

/**
*@copydoc	Audio::Stop
*/
void GameEngine::StopAudio(int playerId)
{
	Audio::Stop(playerId);
}


/**
*	デストラクタ
*/
GameEngine::~GameEngine()
{
	//---ここに終了処理を追加する---

	updateFunc = nullptr;

	Audio::Destroy();

	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
	}
	if (ibo)
	{
		glDeleteBuffers(1, &ibo);
	}
	if (vbo)
	{
		glDeleteBuffers(1, &vbo);
	}
}

/**
*ゲームの状態を更新する
*
*@param delta	前回の更新からの経過時間(秒)
*/
void GameEngine::Update(double delta)
{
	fontRenderer.MapBuffer();
	if (updateFunc)
	{
		updateFunc(delta);
	}
	//---ここに更新処理を追加する---
	const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 200.0f);

	const glm::mat4x4 matView = glm::lookAt(camera.position, camera.target, camera.up);
	entityBuffer->Update(delta, matView, matProj);

	fontRenderer.UnmapBuffer();

}

/**
*	ゲームの状態を描画する
*/
void GameEngine::Render() const
{
	//---ここに描画処理を追加する---		
	glBindFramebuffer(GL_FRAMEBUFFER, offscreen->GetFramebuffer());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, 800, 600);
	glScissor(0, 0, 800, 600);
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	uboLight->BufferSubData(&lightData);
	entityBuffer->Draw(meshBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glBindVertexArray(vao);
	progColorFilter->UseProgram();
	Uniform::PostEffectData postEffect;
	uboPostEffect->BufferSubData(&postEffect);
	progColorFilter->BindTexture(GL_TEXTURE0, GL_TEXTURE_2D, offscreen->GetTexture());
	//progColorFilter->BindTexture(GL_TEXTURE0, GL_TEXTURE_2D, textureBuffer.find("Res/Sparrow.bmp")->second->Id());
	glDrawElements(GL_TRIANGLES, renderingParts[1].size,
		GL_UNSIGNED_INT, renderingParts[1].offset);

	fontRenderer.Draw();
}


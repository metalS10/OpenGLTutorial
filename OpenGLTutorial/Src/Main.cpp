/**
*	@file Main.cpp
*/

#include "GameEngine.h"
#include "C:/Users/tatsu/Desktop/OpenGLTutorial/OpenGLTutorial/Res/Audio/SampleSound_acf.h"
#include "C:/Users/tatsu/Desktop/OpenGLTutorial/OpenGLTutorial/Res/Audio/SampleCueSheet.h"

#include <glm/gtc/matrix_transform.hpp>


//エンティティの衝突グループID
enum EntityGroupId
{
	EntityGroupId_Player,
	EntityGroupId_PlayerShot,
	EntityGroupId_Enemy,
	EntityGroupId_EnemyShot,
	EntityGroupId_Others,
};

//衝突形状リスト
static const Entity::CollisionData collsionDataList[] =
{
	{ glm::vec3(-1.0f,-1.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f) },
	{ glm::vec3(-0.5f,-0.5f,-1.0f),glm::vec3(0.5f,0.5f,1.0f) },
	{ glm::vec3(-1.0f,-1.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f) },
	{ glm::vec3(-0.25f,-0.25f,-1.0f),glm::vec3(0.25f,0.25f,0.25f) },
};

///3Dベクター型
struct Vector3
{
	float x, y, z;
};

///RGBAカラー型
struct Color
{
	float r, g, b, a;
};

//コメント

///頂点シェーダ
static const char* vsCode =
"#version 410\n"
"layout(location = 0) in vec3 vPosition;"
"layout(location = 1) in vec4 vColor;"
"layout(location = 2) in vec2 vTexCoord;"
"layout(location = 0) out vec4 outColor;"
"layout(location = 1) out vec2 outTexCoord;"

"uniform mat4x4 matMVP;"	//new!
"void main(){"
" outColor = vColor;"
" outTexCoord = vTexCoord; "
" gl_Position = matMVP * vec4(vPosition,1.0);"	//new!
"}";

///フラグメントシェーダ
static const char* fsCode =
"#version 410\n"
"layout(location = 0) in vec4 inColor;"
"layout(location = 1) in vec2 inTexCoord;"
"uniform sampler2D colorSampler;"
"out vec4 fragColor;"
"void main(){"
" fragColor = inColor * texture(colorSampler,inTexCoord);"
"}";













/**
*敵の円盤の状態を更新する
*/
struct UpdateToroid
{
	//Delete
	//explicit UpdateToroid(Entity::BufferPtr buffer) : entityBuffer(buffer){}
	void operator() (Entity::Entity& entity, double delta)
	{
		//範囲外に出たら削除する
		const glm::vec3 pos = entity.Position();
		if (std::abs(pos.x) > 40.0f || std::abs(pos.z) > 40.0f)
		{
			GameEngine::Instance().RemoveEntity(&entity);
			return;
		}

		//円盤を回転させる
		float rot = glm::angle(entity.Rotation());
		rot += glm::radians(15.0f) * static_cast<float>(delta);
		if (rot > glm::pi<float>() * 2.0f)
		{
			rot -= glm::pi<float>() * 2.0f;
		}
		entity.Rotation(glm::angleAxis(rot, glm::vec3(0, 1, 0)));

	}

	//Entity::BufferPtr entityBuffer;
};

/**
*	自機の弾の更新
*/
struct UpdatePlayerShot
{
	void operator() (Entity::Entity& entity, double delta)
	{
		const glm::vec3 pos = entity.Position();
		if (std::abs(pos.x) > 40 || pos.z < -4 || pos.z > 40)
		{
			entity.Destroy();
			return;
		}
	}
};

/**
*	爆発の更新
*/
struct UpdateBlast
{
	void operator()(Entity::Entity& entity, double delta)
	{
		timer += delta;
		if (timer >= 0.5)
		{
			entity.Destroy();
			return;
		}
		//変化量
		const float variation = static_cast<float>(timer * 4);
		//徐々に拡大する
		entity.Scale(glm::vec3(static_cast<float>(1 + variation)));

		//時間経過で色と透明度を変化させる
		static const glm::vec4 color[] =
		{
			glm::vec4(1.0f,1.0f,0.75f,1),
			glm::vec4(1.0f,0.5f,0.1f,1),
			glm::vec4(0.25f,0.1f,0.1f,0),
		};

		const glm::vec4 col0 = color[static_cast<int>(variation)];
		const glm::vec4 col1 = color[static_cast<int>(variation) + 1];
		const glm::vec4 newColor = glm::mix(col0, col1, std::fmod(variation, 1));
		entity.Color(newColor);

		//Y軸回転させる
		glm::vec3 euler = glm::eulerAngles(entity.Rotation());
		euler.y += glm::radians(60.0f) * static_cast<float>(delta);
		entity.Rotation(glm::quat(euler));

	}
	double timer = 0;
};


/**
*	時期の更新
*/
struct UpdatePlayer
{
	void operator() (Entity::Entity& entity, double delta)
	{
		GameEngine& game = GameEngine::Instance();
		const GamePad gamepad = game.GetGamePad();
		glm::vec3 vec;
		float rotz = 0;
		if (gamepad.buttons & GamePad::DPAD_LEFT)
		{
			vec.x = 1;
			rotz = -glm::radians(30.0f);
		}
		else if (gamepad.buttons & GamePad::DPAD_RIGHT)
		{
			vec.x = -1;
			rotz = glm::radians(30.0f);
		}
		if (gamepad.buttons & GamePad::DPAD_UP)
		{
			vec.z = 1;
		}
		else if (gamepad.buttons & GamePad::DPAD_DOWN)
		{
			vec.z = -1;
		}
		if (vec.x || vec.z)
		{
			//速さ
			vec = glm::normalize(vec) * 10.0f;
		}
		entity.Velocity(vec);
		entity.Rotation(glm::quat(glm::vec3(0, 0, rotz)));
		glm::vec3 pos = entity.Position();
		pos = glm::min(glm::vec3(11, 100, 20), glm::max(pos, glm::vec3(-11, -100, 1)));
		entity.Position(pos);


		if (gamepad.buttons & GamePad::A)
		{
			shotInterval -= delta;
			if (shotInterval <= 0)
			{
				glm::vec3 pos = entity.Position();
				pos.x -= 0.3f;
				for (int i = 0;i < 2; ++i)
				{
					if (Entity::Entity* p = game.AddEntity(EntityGroupId_PlayerShot, pos,
						"NormalShot", "Res/Player.bmp", UpdatePlayerShot()))
					{
						p->Velocity(glm::vec3(0, 0, 80));
						p->Collision(collsionDataList[EntityGroupId_PlayerShot]);
					}
					pos.x += 0.6f;
				}
				shotInterval = 0.25;

				game.PlayAudio(0, CRI_SAMPLECUESHEET_PLAYERSHOT);
			}
		}
		else
		{
			shotInterval = 0;
		}


	}
private:
	double shotInterval = 0;
};


/**
*ゲームの状態を更新する
*
*@param	entityBuffer	敵エンティティ追加先のエンティティバッファ
*@param	meshBuffer		敵エンティティのメッシュを管理しているメッシュバッファ
*@param	tex				敵エンティティ用のテクスチャ
*@param	prog			敵エンティティ用のシェーダープログラム
*/
struct Update
{
	void operator() (double delta)
	{
		GameEngine& game = GameEngine::Instance();

		if (!pPlayer)
		{
			pPlayer = game.AddEntity(EntityGroupId_Player, glm::vec3(0, 0, 2), "Aircraft", "Res/Player.bmp", UpdatePlayer());
			pPlayer->Collision(collsionDataList[EntityGroupId_Player]);
		}

		game.Camera({ glm::vec4(0,20,-8,1),glm::vec3(0,0,12),glm::vec3(0,0,1) });
		game.AmbientLight(glm::vec4(0.05f, 0.1f, 0.2f, 1));
		game.Light(0, { glm::vec4(40,100,10,1),glm::vec4(12000,12000,12000,1) });
		std::uniform_int_distribution<> distributerX(-12, 12);
		std::uniform_int_distribution<> distributerZ(40, 44);

		interval -= delta;
		if (interval <= 0)
		{
			const std::uniform_real_distribution<> rndInterval(1, 1);
			const std::uniform_int_distribution<> rndAddingCount(1, 5);
			for (int i = rndAddingCount(game.Rand());i > 0; --i)
			{
				const glm::vec3 pos(distributerX(game.Rand()), 0, distributerZ(game.Rand()));
				if (Entity::Entity* p = game.AddEntity(EntityGroupId_Enemy, pos, "Toroid", "Res/Toroid.bmp", UpdateToroid()))
				{
					p->Velocity(glm::vec3(pos.x < 0 ? 1.0f : -0.1f, 0, -10));
					p->Collision(collsionDataList[EntityGroupId_Enemy]);
				}
			}
			interval = rndInterval(game.Rand());
		}

		char str[16];
		snprintf(str, 16, "%08d", game.Score());
		game.FontScale(glm::vec2(2));
		game.FontColor(glm::vec4(1));
		game.AddString(glm::vec2(-0.2f, 0.9f), str);

	}
	double interval = 0;
	Entity::Entity* pPlayer = nullptr;
};


/**
*	自機の弾と敵の衝突処理
*/
void PlayerShotAndEntityCollisionHandler(Entity::Entity& lhs, Entity::Entity& rhs)
{
	GameEngine& game = GameEngine::Instance();
	if (Entity::Entity* p = game.AddEntity(EntityGroupId_Others, rhs.Position(),
		"Blast", "Res/Toroid.bmp", UpdateBlast()))
	{
		const std::uniform_real_distribution<float> rotRange(0.0f, glm::pi<float>() * 2);
		p->Rotation(glm::quat(glm::vec3(0, rotRange(game.Rand()), 0)));
		game.Score(game.Score() + 100);
	}
	game.PlayAudio(1, CRI_SAMPLECUESHEET_BOMB);
	lhs.Destroy();
	rhs.Destroy();
}


/**
*Uniform Block Objectを作成する
*
*@param	size Uniform Blockのサイズ
*@param data Uniform Blockに転送するデータへのポインタ
*
*@return 作成したUBO
*/
GLuint CreateUBO(GLsizeiptr size, const GLvoid* data = nullptr)
{
	GLuint ubo;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	return ubo;
}


///エントリーポイント
int main()
{
	GameEngine& game = GameEngine::Instance();
	if (!game.Init(800, 600, "OpenGL Tutorial"))
	{
		return 1;
	}
	if (!game.InitAudio("Res/Audio/SampleSound.acf", "Res/Audio/SampleCueSheet.acb", nullptr, CRI_SAMPLESOUND_ACF_DSPSETTING_DSPBUSSETTING_0))
	{
		return 1;
	}

	//TexturePtr tex = Texture::LoadFromFile("Res/Sparrow.bmp");
	game.LoadTextureFromFile("Res/Toroid.bmp");
	game.LoadTextureFromFile("Res/Player.bmp");
	//game.LoadTextureFromFile("Res/Sparrow.bmp");

	game.LoadMeshFromFile("Res/Toroid.fbx");
	game.LoadMeshFromFile("Res/Player.fbx");
	game.LoadMeshFromFile("Res/Blast.fbx");

	game.LoadFontFromFile("Res/font/UniNeue.fnt");

	game.CollisionHandler(EntityGroupId_PlayerShot, EntityGroupId_Enemy,
		&PlayerShotAndEntityCollisionHandler);

	game.UpdateFunc(Update());
	game.Run();

	return 0;
}

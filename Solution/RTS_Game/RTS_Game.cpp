#include "stdafx.h"

#include <AssetContainer.h>
#include <Camera.h>
#include <DeferredRenderer.h>
#include <Engine.h>
#include "RTS_Game.h"
#include <MathHelper.h>
#include "PostMaster.h"
#include "RenderMessage.h"
#include <RendererProxy.h>
#include <XMLReader.h>

#include "RenderComponent.h"
#include "TranslationComponent.h"
#include "InputComponent.h"
#include "AABBComponent.h"

#include <Entity/Include/TypeID.h>

#include <Entity/Include/ComponentFilter.h>
#include "RenderProcessor.h"
#include "ManualMovementProcessor.h"
#include "SelectionProcessor.h"
#include "HighlightingProcessor.h"
#include "AABBProcessor.h"
#include "MovementProcessor.h"

#include <ProfilerInclude.h>

RTS_Game::RTS_Game()
{
}


RTS_Game::~RTS_Game()
{
	PostMaster::GetInstance()->UnSubscribe(this, eMessageType::RENDER);
	PostMaster::GetInstance()->Destroy();
}

void RTS_Game::Init(Magma::Engine& aEngine)
{
	myCamera = &aEngine.GetCamera();
	myCamera->Move({ 4.f, 10.f, -5.f });
	myCamera->RotateX(PI * 0.25f);


	myRendererProxy = &aEngine.GetRendererProxy();

	LoadLevel(aEngine.GetAssetContainer());

	myWorld.AddProcessor<RenderProcessor>();
	myWorld.AddProcessor<ManualMovementProcessor>();

	SelectionProcessor* selectionProcessor = new SelectionProcessor(myWorld, *myCamera);
	myWorld.AddProcessor(selectionProcessor);

	myWorld.AddProcessor<HighlightingProcessor>();
	myWorld.AddProcessor<AABBProcessor>();
	myWorld.AddProcessor<MovementProcessor>();

	PostMaster::GetInstance()->Subscribe(this, eMessageType::RENDER);
}

bool RTS_Game::Update(float aDelta)
{
	PROFILE_START("Update Camera");
	UpdateCamera(aDelta);
	PROFILE_END();

	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	PROFILE_START("Update World");
	myWorld.Update(aDelta);
	PROFILE_END();

	return true;
}

void RTS_Game::OnResize(float /*aWidth*/, float /*aHeight*/)
{
}

void RTS_Game::ReceiveMessage(const RenderMessage& aMessage)
{
	myRendererProxy->RenderModel(aMessage.myModelID, aMessage.myEffectID, aMessage.myOrientation, aMessage.myColor, aMessage.myScale);
}

void RTS_Game::UpdateCamera(float aDelta)
{
	myCamera->Update();

	float speed = 10.f * aDelta;
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();
	CU::Vector3<float> dir;

	if (input->KeyIsPressed(DIK_NUMPAD8))
	{
		dir.z = 1.f;
	}
	else if (input->KeyIsPressed(DIK_NUMPAD2))
	{
		dir.z = -1.f;
	}

	if (input->KeyIsPressed(DIK_NUMPAD4))
	{
		dir.x = -1.f;
	}
	else if (input->KeyIsPressed(DIK_NUMPAD6))
	{
		dir.x = 1.f;
	}

	if (input->KeyIsPressed(DIK_NUMPAD7))
	{
		dir.y = 1.f;
	}
	else if (input->KeyIsPressed(DIK_NUMPAD9))
	{
		dir.y = -1.f;
	}

	CU::Normalize(dir);
	myCamera->Move(dir * speed);

	if (input->KeyIsPressed(DIK_UP))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundX(-PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_DOWN))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundX(PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_LEFT))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundY(-PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_RIGHT))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundY(PI * 0.5f * aDelta));
	}
}

void RTS_Game::LoadLevel(Magma::AssetContainer& aAssetContainer)
{
	/*
	XMLReader reader;
	reader.OpenDocument("Data/Resource/Level/Level_01.xml");
	for (tinyxml2::XMLElement* cube = reader.ForceFindFirstChild("Cube"); cube != nullptr; cube = reader.FindNextElement(cube, "Cube"))
	{
		CU::Vector3<float> position;
		CU::Vector3<float> rotation;
		CU::Vector3<float> scale;

		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Position"), "x", "y", "z", position);
		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Scale"), "x", "y", "z", scale);
		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Rotation"), "x", "y", "z", rotation);

		rotation.x = CU::Math::DegreeToRad(rotation.x);
		rotation.y = CU::Math::DegreeToRad(rotation.y);
		rotation.z = CU::Math::DegreeToRad(rotation.z);


		Magma::Entity entity = myWorld.CreateEntity();
		myWorld.AddComponent<TranslationComponent>(entity);
		myWorld.AddComponent<RenderComponent>(entity);
		TranslationComponent& comp = myWorld.GetComponent<TranslationComponent>(entity);
		comp.myScale = scale;
		
		comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundZ(rotation.z);
		comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundX(rotation.x);
		comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundY(rotation.y);

		comp.myOrientation.SetPos(position);

		RenderComponent& renderComp = myWorld.GetComponent<RenderComponent>(entity);
		//renderComp.myModelID = aAssetContainer.LoadModel("Data/Resource/Model/Sphere/Sphere.fbx", "Data/Resource/Shader/S_effect_cube.fx");
		//renderComp.myModelID = aAssetContainer.LoadModel("Data/Resource/Model/blenderbox.fbx", "Data/Resource/Shader/S_effect_cube.fx");
		//renderComp.myEffectID = aAssetContainer.LoadEffect("Data/Resource/Shader/S_effect_cube.fx");

		const char* cubeShader = "Data/Resource/Shader/S_effect_simple_cube.fx";
		renderComp.myModelID = aAssetContainer.LoadCube(cubeShader);
		renderComp.myEffectID = aAssetContainer.LoadEffect(cubeShader);

		lastEntity = entity;
	}
	reader.CloseDocument();
	*/

	int gridSize = 20;
	for (int z = 0; z < gridSize; ++z)
	{
		for (int x = 0; x < gridSize; ++x)
		{
			CreateCube(aAssetContainer, CU::Vector3<float>(x, 0.f, z));
		}
	}

}

Magma::Entity RTS_Game::CreateCube(Magma::AssetContainer& aAssetContainer, const CU::Vector3<float>& aPosition)
{
	CU::Vector3<float> position = aPosition;
	CU::Vector3<float> rotation;
	CU::Vector3<float> scale(1.f, 1.f, 1.f);

	rotation.x = CU::Math::DegreeToRad(rotation.x);
	rotation.y = CU::Math::DegreeToRad(rotation.y);
	rotation.z = CU::Math::DegreeToRad(rotation.z);


	Magma::Entity entity = myWorld.CreateEntity();
	myWorld.AddComponent<TranslationComponent>(entity);
	myWorld.AddComponent<RenderComponent>(entity);
	myWorld.AddComponent<AABBComponent>(entity);

	TranslationComponent& comp = myWorld.GetComponent<TranslationComponent>(entity);
	comp.myScale = scale;

	comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundZ(rotation.z);
	comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundX(rotation.x);
	comp.myOrientation = comp.myOrientation * CU::Matrix44f::CreateRotateAroundY(rotation.y);

	comp.myOrientation.SetPos(position);

	RenderComponent& renderComp = myWorld.GetComponent<RenderComponent>(entity);

	const char* cubeShader = "Data/Resource/Shader/S_effect_simple_cube.fx";
	renderComp.myModelID = aAssetContainer.LoadCube(cubeShader);
	renderComp.myEffectID = aAssetContainer.LoadEffect(cubeShader);
	renderComp.myColor = CU::Math::RandomVector(CU::Vector4f(0.f), CU::Vector4f(1.f));
	renderComp.myColor.w = 1.f;
	renderComp.myOriginalColor = renderComp.myColor;

	AABBComponent& aabbComp = myWorld.GetComponent<AABBComponent>(entity);
	aabbComp.myAABB = CU::Intersection::AABB(position, scale);
	//aabbComp.myAABB.Transform(comp.myOrientation);

	return entity;
}
